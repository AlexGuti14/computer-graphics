#include <iostream>
#include <random>

using namespace std;

class Brdf{
public:
   
    //Constructor
    Brdf(){
        
    }

    //Si x<lower -> x=lower  /  Si x>upper -> x=upper
    float clamp(float x, float upper, float lower){
        return min(upper, max(x, lower));
    }

    //Devuelve el maximo valor entre a y b
    float max(float a, float b){
        return a>b ? a : b;
    }

    //Calculo de la direccion en la que es reflejado un rayo al chocar con una superficie especular perfecta
    Direccion reflection(Direccion dirRayo, Direccion normal){
        return normalize(dirRayo-(normal*dot(dirRayo,normal)*2));
    }

    //Caclulo de la direccion en la que se refracta un rayo al chocar con una superficie refractiva perfecta
    Direccion refraction(Direccion dirRayo, Direccion& normal, float ior){
        //iorOut=ior en el medio donde se encuentra la escena (aire)
        //iorIn=ior del interior de la figura 
        float iorOut = 1, iorIn = ior; 
        Direccion n = normal; 

        //Para comprobar si el rayo va de n1 a n2 o al revés
        float cosOut = clamp(dot(dirRayo,normal), 1, -1);

        //Si dirRayo*N<0 el rayo va de n1 a n2
        if (cosOut < 0){ 
            //Se necesita que el coseno sea positivo
            cosOut = -cosOut; 
        } 
        //El rayo va de n2 a n1
        else{ 
            //n2 pasa a ser ior inicial y n1 el ior al que se va a pasar
            std::swap(iorOut, iorIn); 
            //hay que cambiar el signo de la normal
            n= normal*-1; 
        } 

        float ratioIor = iorOut / iorIn; 
        float k = 1 - ratioIor * ratioIor * (1 - cosOut * cosOut); 

        
        //Si k<0, caso de reflexion interna total 
        //Se da cuando el angulo de entrada es mayor al angulo critico y se pasa a un medio con menor ior que el actual
        if(k<0){
            return Direccion(0,0,0);
        }
        else{
            return dirRayo*ratioIor + n*(ratioIor * cosOut - sqrtf(k));
        }

    }

    //Dado un ior, calcula los valores de ksp y kr (cuanta luz se refleja y cuanta se refracta)
    void fresnel(Direccion dirRayo, Direccion normal, float ior, Rgb& ksp2, Rgb &kr2) { 
        float ksp,kr;
        float iorOut = 1, iorIn = ior; 
        float cosOut = clamp(dot(dirRayo,normal), 1, -1);

        //Si dirRayo*N<0 el rayo va de fuera a dentro de la figura
        if (cosOut > 0) { 
            std::swap(iorOut, iorIn); 
        } 

        //Si el seno de 02 es mayor a 1 hay reflexion total
        float sinIn = iorOut / iorIn * sqrtf(max(0, 1 - cosOut * cosOut)); 

        //Reflexion interna total si el seno del angulo de rafraccion excede la unidad
        if (sinIn >= 1) { 
            ksp = 1; 
        } 
        //Se aplica la ley de fresnel
        else { 
            float cosIn = sqrtf(max(0, 1 - sinIn * sinIn)); 
            //valor absoluto
            cosOut = fabs(cosOut); 
            float Rs = ((iorIn * cosOut) - (iorOut * cosIn)) / ((iorIn * cosOut) + (iorOut * cosIn)); 
            float Rp = ((iorOut * cosOut) - (iorIn * cosIn)) / ((iorOut * cosOut) + (iorIn * cosIn)); 
            ksp = (Rs * Rs + Rp * Rp) / 2; 
            kr=1-ksp;
        } 

        ksp2=Rgb(ksp,ksp,ksp);
        kr2=Rgb(kr,kr,kr);
    }

    //Devuelve 1 valor aleatorio dentro del rango especificado (a,b)
    float posAleatoria(float a, float b){
        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<float> dist(a,b);

        return dist(mt);
    }

    //Devuelve las coordenadas globales con respecto a la normal
    Matrix4 crearSistemaCoordenadas(Direccion normal, Punto p){
        float a=posAleatoria(-1.0f,1.0f);
        float b=posAleatoria(-1.0f,1.0f);
        float c=posAleatoria(-1.0f,1.0f);
        Direccion aleatorio=normalize(Direccion(a,b,c));
        //Si el vector es paralelo a la normal se vuelve a generar otro
        while(dot(aleatorio,normal)==module(aleatorio)*module(normal)){
            a=posAleatoria(-1.0f,1.0f);
            b=posAleatoria(-1.0f,1.0f);
            c=posAleatoria(-1.0f,1.0f);
            aleatorio=normalize(Direccion(a,b,c));
        }
        
        Direccion x=cross(normal,aleatorio);
        Direccion z=cross(normal,x);

        Matrix4 cambioBase(x,normal,z,p);
  
        return cambioBase;
    }

    //Devuelve una dirección aleatoria dentro de la hemiesfera que rodea a la normal
    Direccion direccionAleatoria(Direccion normal, Punto p){
        float random1,random2;
        Matrix4 sistCoord=crearSistemaCoordenadas(normal,p);
        //Se genera rayo en direccion aleatoria
        random1=posAleatoria(0.0f,1.0f);
        random2=posAleatoria(0.0f,1.0f);
        float theta = acosf(sqrt(1-random1));
        float phi=2*M_PI*random2;
        //Se obtiene direccion del rayo aleatorio
        Direccion rayoNuevo=normalize(Direccion(sin(theta)*cos(phi),cos(theta),sin(theta)*sin(phi)));
        //Cambio de base al sistema de coordenadas global
        return normalize(sistCoord.doTransformation(rayoNuevo));
    }

};

    