#include <iostream>
#include "Brdf.cpp"

using namespace std;

//Gestion de la interseccion de un rayo con una figura
class Interseccion{
public:

    //Atributos
    Punto p;
    Esfera esfera;
    Plano plano;
    bool esEsfera;
    float t;
    bool hayCorte;

    //Constructor
    Interseccion(){}

    //Constructor
	Interseccion(Punto p, Esfera e, Plano pl, bool es) {
        this->p=p;
        this->esfera=e;
        this->plano=pl;
        this->esEsfera=es;
	}

    //Constructor
    Interseccion(Esfera e, Plano pl, bool es, bool c, float t0) {
        this->esfera=e;
        this->plano=pl;
        this->esEsfera=es;
        this->hayCorte=c;
        this->t=t0;
	}

    
    //Getters
    Punto getPoint(){
        return p;
    }

    Esfera getEsfera(){
        return esfera;
    }

    Plano getPlano(){
        return plano;
    }

    float getT(){
        return t;
    }

    bool getCorte(){
        return hayCorte;
    }

    //Setters
    void setPoint(Punto p){
        this->p=p;
    }

    void setEsfera(bool es){
        esEsfera=es;
    }
    
    void setT(float t0){
        t=t0;
    }

    //Devuelve la información necesaria del punto intersectado
    void getInfo(Direccion dirRayo, Direccion& normal, Rgb& kd, Rgb& ks, Rgb& ksp, Rgb& kr, float& ior, float& alfa, Rgb& emite){
        if(esEsfera){
            normal=normalize(getPoint()-getEsfera().center);
            kd=getEsfera().kd;
            ks=getEsfera().ks;
            ior=getEsfera().ior;
            alfa=getEsfera().alfa;

            //Si se usa fresnel se ignoran los parametros ksp y kr ya que este los va a generar dado el ior
            if(getEsfera().fresnel){
                Brdf().fresnel(dirRayo,normal,ior,ksp,kr);
            }
            else{
                ksp=getEsfera().ksp;
                kr=getEsfera().kr;
            }

            //Si tiene textura
            if(getEsfera().tex){
               kd=getEsfera().colorTextura(normal);
            }

            emite=Rgb(0,0,0);
        }
        //PLANO
        else {
            normal=normalize(getPlano().n);
            kd=getPlano().kd;
            ks=getPlano().ks;
            ior=getPlano().ior;
            alfa=getPlano().alfa;

            //Si se usa fresnel se ignoran los parametros ksp y kr ya que este los va a generar dado el ior
            if(getPlano().fresnel){
                Brdf().fresnel(dirRayo,normal,ior,ksp,kr);
            }
            else{
                ksp=getPlano().ksp;
                kr=getPlano().kr;
            }

            //Si tiene textura
            if(getPlano().tex){
                kd=getPlano().colorTextura(getPoint(),normal);
            }

            //Si emite 
            if(!getPlano().pot.cero()){
                emite=getPlano().pot;
            }
            else{
                emite=Rgb(0,0,0);
            }
        }
    }

    

};

