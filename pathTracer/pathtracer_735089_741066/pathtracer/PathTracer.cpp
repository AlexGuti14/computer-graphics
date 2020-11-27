#include <chrono> 
#include <thread> 
#include <list>
#include "Punto.cpp"
#include "Rgb.cpp"
#include "Esfera.cpp"
#include "Plano.cpp"
#include "Camara.cpp"
#include "Luz.cpp"
#include "Matrix4.cpp"
#include "Listas.cpp"
#include "Interseccion.cpp"
#include "Imagen.cpp"

using namespace std::chrono; 

//Implementacion del algoritmo PathTracer
class PathTracer{
public:

  //Atributos
  Listas lista;
  Camara camara;
  float numRayos;
  float front;
  Imagen imagen;

  //Constructor
  PathTracer(Listas& l, Camara& c, float& paths, float& f, Imagen& i){
    lista=l;
    camara=c;
    numRayos=paths;
    front=f;
    imagen=i;
  }
  
  //Informa del progreso del algoritmo durante su ejecucion
  void progreso(int numPixel, int total, bool& fin) {
    auto percentCompleted = static_cast<int>(numPixel / static_cast<float>(total) * 100.0f);
    cout << "Progress: [";
    for (int i = 0; i < round(percentCompleted / 2); ++i) {
        cout << "=";
    }
    if (total == numPixel){ 
      cout << "] 100%\n";
      fin=true;
    }
    else{
      cout << "> " << percentCompleted << "%\r" << flush;
    } 
  }

  //Lanza rayo de sombra para comprobar si a P le llega luz desde la fuente de luz
  bool rayoSombra(Punto P, Punto luz, Esfera esferaFinal){
    //Direccion entre la fuente de luz y el punto en el que se quiere sabe el color (P)
    Direccion wi=normalize(luz-P);
    bool corta=false;
    Punto P2;
    float t1=INFINITY;

    Esfera siguiente;
    list<Esfera>::iterator it=lista.listaEsferas.begin();
    //Se recorren todas las esferas para ver si hay alguna que corte el rayo de Sombra
    while(it != lista.listaEsferas.end() && !corta){
      siguiente=*it;
      //No interesea comprobar la propia esfera intersectada por el rayo primario
      if(!siguiente.iguales(esferaFinal)){
        t1=INFINITY;
        if(siguiente.intersectan(P,wi,t1)){
          P2=P+wi*t1;
          //Si la distancia entre P y P2(interseccion del rayo de sombra) es menor a la
          //distancia entre P y la fuente de luz, quiere decir que la figura esta en medio
          if(module(P-P2)<module(P-luz)){
            //Impide que la luz llegue a P
            corta=true;
          }
        }
      }
      ++it;
    }

    return corta;
  }

  //Comprueba si el rayo lanzado intersecta alguna figura de la escena 
  //Si intersecta mas de una se tiene en cuenta el punto de corte mas cercano al plano de pixeles
  Interseccion intersectaFigura(Direccion dirRayo, Punto posPixel){
    float t0=INFINITY;
    bool hayCorte=false;
    bool esEsfera=false;
    Esfera esferaFinal;
    float t1=INFINITY;
    //Se comprueba la interseccion con alguna esfera 
    for(Esfera &p : lista.listaEsferas){
      t1=INFINITY;
      if(p.intersectan(posPixel,dirRayo,t1)){
        hayCorte=true;
        if(t1<t0){
          t0=t1;
          esferaFinal=p;
          esEsfera=true;
        }
      }
    }
    //Se comprueba la interseccion con algun plano 
    Punto P;
    Plano planoFinal;
    for(Plano &p : lista.listaPlanos){
      t1=INFINITY;
      if(p.intersectan(posPixel,dirRayo,t1)){
        hayCorte=true;
        if(t1<t0){
          P=posPixel+dirRayo*t1;
          if(p.estaDentro(P)){
            t0=t1;
            planoFinal=p;
            esEsfera=false;
          }
        }
      }
    }
    return Interseccion(esferaFinal,planoFinal,esEsfera,hayCorte,t0);
  }

  //Parte del calculo de la luz indirecta tras realizar las simplificaciones oportunas debido a las probabilidades
  Rgb simplificacionIndirecta(Direccion rayoNuevo, Direccion dirRayo, Direccion normal, Rgb kd, Rgb ks, float pkd, float pks,float alfa){

    //Kd
    Rgb difuso=kd/pkd;

    //Ks
    Direccion wi = rayoNuevo;
    Direccion wo = dirRayo*-1;
    Direccion wr=Brdf().reflection(wi,normal);
    Rgb especular= (ks*(alfa + 2) * pow(fabs(dot(wr, wo)), alfa)) / 2;
    
    return difuso+especular;
  }

  //Calculo de la luz indirecta
  Rgb LuzIndirecta(Direccion dirRayo, Interseccion t, Direccion normal, Rgb kd, Rgb ks, Rgb ksp, Rgb kr, float ior, float alfa) {
    Direccion direccionNueva;
    float random;
    float bias=1e-4;

    //Relacion entre coeficientes y ruleta rusa 
    float pkd=kd.max();
    float pks=ks.max();
    float pksp=ksp.max();
    float pkr=kr.max();

    //Normalizar probabilidades si superan el 0.9 (debe haber siempre un 10% de probabilidad de absorcion)
    float total=(pkd+pks+pksp+pkr);
    if(total>0.9){
      pkd=pkd*0.9/total;
      pks=pks*0.9/total;
      pksp=pksp*0.9/total;
      pkr=pkr*0.9/total;
    }

    random=Brdf().posAleatoria(0.0f,1.0f);

    //RULETA RUSA

    //Rebote como lambertiano (reflexion en direccion aleatoria)
    if(random<pkd + pks){
      direccionNueva=Brdf().direccionAleatoria(normal,t.getPoint());
      return trazarCamino(t.getPoint(),direccionNueva)*simplificacionIndirecta(direccionNueva,dirRayo,normal,kd,ks,pkd,pks,alfa);
    }
    //Rebote como espejo(reflexion)
    else if((pkd+pks)<random && random<(pkd+pks+pksp)){
      direccionNueva=Brdf().reflection(dirRayo,normal);
      return (ksp/pksp)*trazarCamino(t.getPoint()+normal*bias,direccionNueva);
    }
    //Rebote como transparente(refraccion)
    else if((pkd+pks+pksp)<random && random<(pkd+pks+pksp+pkr)){
      direccionNueva=Brdf().refraction(dirRayo,normal,ior); 
      return (kr/pkr)*trazarCamino(t.getPoint()-normal*bias,direccionNueva);    
    }
    //Siempre 10% de probabilidad de absorción
    else{
      return Rgb(0,0,0);
    }
    
  }

  //Calculo de la luz directa
  Rgb LuzDirecta(Luz siguiente, Direccion dirRayo, Interseccion t, Direccion normal, Rgb kd, Rgb ks, float alfa){
    Punto posLuz=siguiente.pos;
    Rgb p=siguiente.pot*siguiente.rgb;
    
    Esfera esfera=t.getEsfera();
   
    //Si !corte (el rayo de sombra no corta ninguna figura) se computa el color en P 
    if((!kd.cero() || !ks.cero()) && !rayoSombra(t.getPoint(),posLuz,esfera)){
      //Kd
      Rgb difuso=kd/M_PI;

      //Ks 
      Direccion wi=normalize(posLuz-t.getPoint());
      Direccion wo = dirRayo*-1;
      Direccion wr = Brdf().reflection(wi,normal);
      Rgb especular= ks*((alfa + 2) / (2 * M_PI)) * pow(fabs(dot(wr, wo)), alfa);

      //Li
      Rgb Li(p.r/pow(module(posLuz-t.getPoint()),2),p.g/pow(module(posLuz-t.getPoint()),2),p.b/pow(module(posLuz-t.getPoint()),2));

      //Termino del coseno
      float cos=Brdf().max(float(0),dot(normalize(normal),wi));

      return Li*(difuso+especular)*cos;

    }
    
    return Rgb(0,0,0);
  }

  //Indica de qué color hay que pintar el punto de interseccion de acuerdo a la figura intersectada
  Rgb trazarCamino(Punto posPixel, Direccion dirRayo){
    Direccion normal;
    Rgb emite,kd,ks,ksp,kr,colorDirecta,colorIndirecta;
    float brdf,ior,alfa;

    //Si el rayo corta alguna figura de la escena...
    Interseccion t = intersectaFigura(dirRayo,posPixel);
    if(t.getCorte()){
      //Punto mas cercano que corta el rayo
      t.setPoint(posPixel+dirRayo*t.getT());
      t.getInfo(dirRayo,normal,kd,ks,ksp,kr,ior,alfa,emite);
      //Si el objeto intersectado emite se devuelve su potencia
      if(!emite.cero()){
        return emite;
      }
      //Si no emite, se procede a calcular la luz directa e indirecta 
      else{
        //Se recorren las fuentes de luz porque color en P depende de la suma de las contribuciones de cada luz
        for (Luz &l : lista.listaLuces){
          //LUZ DIRECTA (NEXT EVENT ESTIMATION)
          colorDirecta=colorDirecta + LuzDirecta(l,dirRayo,t,normal,kd,ks,alfa);
        }
        //LUZ INDIRECTA
        colorIndirecta=LuzIndirecta(dirRayo,t,normal,kd,ks,ksp,kr,ior,alfa);

        return colorDirecta+colorIndirecta;
        //return colorDirecta;
      }
    }
    //Color si el rayo no choca con nada
    else{
        return Rgb(0,0,0);
    }
  }

  //Recorre w pixeles hacia la derecha y desde j1 hasta j2 en el eje vertical
  void recorrerEscena(int w, int j1, int j2){
    //Por cada pixel, lanzar un rayo y ver la luz que le llega
    float x1,y1;
    bool fin=false;
    for(int y=j2-1;y>=j1;y--){
      for(int x=0;x<w;x++){
        for(int w=0;w<numRayos;w++){
          //Se genera pos aleatoria a traves de la cual lanzar el rayo por el pixel actual
          x1=Brdf().posAleatoria(0.0f,1.0f);
          y1=Brdf().posAleatoria(0.0f,1.0f);
          //Trazado del rayo desde la camara a traves del pixel
          Punto posPixel(x+x1,y-y1,front);
          Direccion dirRayo(posPixel-camara.o);
          //Comprobar si el rayo intersecta una esfera 
          imagen(y,x) = imagen(y,x) + trazarCamino(posPixel,normalize(dirRayo));

        }
        imagen(y,x)={imagen(y,x).r/numRayos,imagen(y,x).g/numRayos,imagen(y,x).b/numRayos};     

        //Mostrar progreso de ejecucion (de uno de los threads)
        if (j1 == 0 && !fin) {
            progreso(imagen.getW() * (j2-y) + x, imagen.getW()  * (j2 - j1),fin);
        }
        
      }
    }
  }

  //Reparte la pantalla de pixeles a procesar entre threads para acelerar la ejecucion (paralelizacion)
  void renderImageMultithread(){

    auto start = high_resolution_clock::now(); 

    //Numero de threads
    int numThreads = std::thread::hardware_concurrency() - 1;

    if (numThreads == 0) {
        exit(0);
    }
    if (numThreads > 8) {
        numThreads = 7;
    }

    int linesPorT = imagen.getH() / numThreads;

    vector<thread> threads(static_cast<unsigned long>(numThreads));
    //Division de la pantalla de pixeles segun el numero de threads disponibles
    for (int i = 0; i < numThreads; i++) {
        int start = i*linesPorT;
        int end = start + linesPorT;
        if (i != numThreads - 1){
            threads[i] = thread(&PathTracer::recorrerEscena,this,imagen.getW(),start,end);
        } else {
            threads[i] = thread(&PathTracer::recorrerEscena,this,imagen.getW(),start,imagen.getH());
        }
    }

    for (auto &thread : threads) {
        thread.join();
    }

    imagen.write();

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 

    //Coste temporal de la ejecucion del programa
    cout << "Tiempo de ejecucion: " << (duration.count()/1000000)/60 << " min" << endl; 

  }
  
};