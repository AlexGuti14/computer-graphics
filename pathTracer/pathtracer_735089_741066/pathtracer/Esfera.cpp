#include <iostream>   
#include "Textura.cpp"

using namespace std;

//Representa una esfera
class Esfera{
public:

    //Atributos
    Punto center;        //Centro
    Direccion axis;      //Eje
    Punto refCity;       //Ciudad de referencia
    Rgb kd;              //Coeficiente difuso
    Rgb ks;              //Coeficiento especular
    Rgb ksp;             //Coeficiente especular perfecto
    Rgb kr;              //Coeficiente refractor perfecto
    float ior;           //Indice de refraccion
    bool fresnel;        //fresnel=true si se usa fresnel
    bool tex;            //tex=true si la esfera tiene textura
    float alfa;          //Rugosidad en caso de material de Phong
    Textura textura;     //Textura
    
    
    //Constructor con textura
	Esfera(Punto c, Direccion a, Punto r, Rgb kd, Rgb ks, float alfa, Rgb ksp, Rgb kr, float ior, bool fresnel,Textura textura) {
        //Comprobacion de que la distancia de c-r es igual al radio de la esfera
        if( (module(a)/2) == distance(r,c)){
            this->center = c;
		    this->axis = a;
		    this->refCity = r;
            this->kd=kd;
            this->ks=ks;
            this->ksp=ksp;
            this->kr=kr;
            this->ior=ior;
            this->fresnel=fresnel;
            this->tex=true;
            this->alfa=alfa;
            this->textura=textura;
        }
        else{
            cout << "Esfera mal construida -> centro: " << c << endl;
            exit(EXIT_FAILURE);
        }
	}

    //Constructor sin textura
    Esfera(Punto c, Direccion a, Punto r, Rgb kd, Rgb ks, float alfa, Rgb ksp, Rgb kr, float ior, bool fresnel) {
        //Comprobacion de que la distancia de c-r es igual al radio de la esfera
        if( (module(a)/2) == distance(r,c)){
            this->center = c;
		    this->axis = a;
		    this->refCity = r;
            this->kd=kd;
            this->ks=ks;
            this->ksp=ksp;
            this->kr=kr;
            this->ior=ior;
            this->fresnel=fresnel;
            this->alfa=alfa;
            this->tex=false;
        }
        else{
            cout << "Esfera mal construida -> centro: " << c << endl;
            exit(EXIT_FAILURE);
        }
	}

    //Constructor
    Esfera(){
        
    }

    //Interseccion rayo-esfera
    bool intersectan(Punto o, Direccion d, float& t) {
        float t0,t1;
        float radius=axis.y/2;
        Direccion L = center - o;
        float tca = dot(L,d);
        if(tca < 0){return false;}
        float d2 = dot(L,L) - tca*tca;
        if(d2 > (radius*radius)){return false;}
        float thc=sqrt((radius*radius)-d2);
        t0=tca-thc;
        t1=tca+thc;

        if(t0>t1){ std::swap(t0,t1);}
        if(t0<0){ 
            t0=t1;
            if(t0<0){
                return false;
            }  
        }
        t=t0;
        return true;
    }
    
    //Comprueba si dos esferas son iguales
    bool iguales(Esfera e){
        return (center==e.center && axis==e.axis && refCity==e.refCity);
    }

    //Obtiene el color presente en la posición de la textura adecuada de acuerdo a la normal (uv mapping)
    Rgb colorTextura(Direccion normal){
        //si u=0.2, se quiere obtener el color del pixel desplazado 20% hacia la derecha de la textura
        float u=0.5 + (atan2(normal.z,normal.x)/(2*M_PI));
        //si v=0.3, se quiere obtener el color del pixel desplazado 30% hacia la arriba de la textura
        float v=0.5 - (asin(normal.y)/M_PI);
        //Conversion de la posición en porcentajes a la posicion real en la textura
        int pixelX=u*textura.dimX;
        int pixelY=v*textura.dimY;
        float r,g,b;
        //Obtener color de la textura en (pixelX,pixelY)
        textura.getRGB(pixelX,pixelY,r,g,b);
    
        r=r/255.0f; 
        g=g/255.0f;
        b=b/255.0f;

        if(r<0.2){
            r=0.2;
        }
        else if(r>0.8){
            r=0.8;
        }

        if(g<0.2){
            g=0.2;
        }
        else if(g>0.8){
            g=0.8;
        }

        if(b<0.2){
            b=0.2;
        }
        else if(b>0.8){
            b=0.8;
        }

        return Rgb(r,g,b);
    }
};

    