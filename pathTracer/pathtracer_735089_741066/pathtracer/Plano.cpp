#include <iostream>    

using namespace std;

//Representa un plano
class Plano{
public:
    Direccion n;         //Normal             
    Punto pp;            //Punto 
    Punto ai;            //esquina arriba izquieda plano finito
    Punto ad;            //esquina arriba derecha plano finito
    Punto abi;           //esquina abajo izquieda plano finito
    Punto abd;           //esquina abajo derecha plano finito
    bool esFinito;       //esFinito=true plano finito
    Rgb kd;              //Coeficiente difuso
    Rgb ks;              //Coeficiento especular
    Rgb ksp;             //Coeficiente especular perfecto
    Rgb kr;              //Coeficiente refractor perfecto
    float ior;           //Indice de refraccion
    float fresnel;       //fresnel=true si se usa fresnel
    bool tex;            //tex=true si la esfera tiene textura
    float alfa;          //Rugosidad en caso de material de Phong
    Textura textura;     //Textura

    Rgb pot;

    //Constructor
    Plano(){
        this->esFinito=false;
    }

    Plano(Rgb pot,Direccion n, Punto puntoPlano, Punto ai, Punto ad, Punto abi, Punto abd, Rgb kd) {
        this->n= normalize(n);
        this->pp=puntoPlano;
        this->ai= ai;
        this->ad=ad;
        this->abi=abi;
        this->abd=abd;
        this->esFinito=true;
        this->kd=kd;
        this->ks=Rgb(0,0,0);
        this->ksp=Rgb(0,0,0);
        this->kr=Rgb(0,0,0);
        this->ior=0;
        this->fresnel=false;
        this->tex=false;
        this->alfa=0;
        this->pot=pot;
        
	}
    
    //Consructor plano finito
	Plano(Direccion n, Punto puntoPlano, Punto ai, Punto ad, Punto abi, Punto abd, Rgb kd, Rgb ks, float alfa, Rgb ksp, Rgb kr, float ior,float fresnel) {
        this->n=normalize(n);
        this->pp=puntoPlano;
        this->ai= ai;
        this->ad=ad;
        this->abi=abi;
        this->abd=abd;
        this->esFinito=true;
        this->kd=kd;
        this->ks=ks;
        this->ksp=ksp;
        this->kr=kr;
        this->ior=ior;
        this->fresnel=fresnel;
        this->tex=false;
        this->alfa=alfa;
        this->pot=Rgb(0,0,0);
	}

    //Consructor plano finito con textura
	Plano(Direccion n, Punto puntoPlano, Punto ai, Punto ad, Punto abi, Punto abd, Rgb kd, Rgb ks, float alfa, Rgb ksp, Rgb kr, float ior, float fresnel, Textura textura) {
        this->n=normalize(n);
        this->pp=puntoPlano;
        this->ai= ai;
        this->ad=ad;
        this->abi=abi;
        this->abd=abd;
        this->esFinito=true;
        this->kd=kd;
        this->ks=ks;
        this->ksp=ksp;
        this->kr=kr;
        this->ior=ior;
        this->fresnel=fresnel;
        this->tex=true;
        this->alfa=alfa;
        this->textura=textura;
        this->pot=Rgb(0,0,0);
	}

    //Constructor plano infinito
    Plano(Direccion n, Punto puntoPlano, Rgb kd, Rgb ks, float alfa, Rgb ksp, Rgb kr, float ior, float fresnel) {
        this->n=normalize(n);
        this->pp=puntoPlano;
        this->esFinito=false;
        this->kd=kd;
        this->ks=ks;
        this->ksp=ksp;
        this->kr=kr;
        this->ior=ior;
        this->fresnel=fresnel;
        this->tex=false;
        this->alfa=alfa;
        this->pot=Rgb(0,0,0);
	}

    //Interseccion rayo-plano
    bool intersectan(Punto o, Direccion dir, float& t0) { 
        //Se cambia de signo la normal porque el rayo incide en la parte posterior del plano
        Direccion normal=n*-1;
        float denom = dot(normal,dir); 
        //Rayo no corta a plano si normal*dir esta muy cerca de 0 (paralelos o se cortan infinitamente)
        if (denom > 1e-6) { 
            //t0= (pp-o)*n / l*n
            Direccion p0l0 = pp - o; 
            t0 = dot(p0l0,normal) / denom; 
            return (t0 >= 0); 
        } 
        return false; 
    }


    //Comprueba si el rayo corta al plano (sea finito o no)
    bool estaDentro(Punto P){
        bool dentro=false;
        //Pared fondo
        if(n.x==0 && n.y==0 && n.z==-1){
            dentro = ((P.x>=ai.x && P.x<=ad.x && P.y<=ad.y && P.y>=abd.y) || (!esFinito));
        }
        //Pared izq o pared der
        else if((n.x==1 && n.y==0 && n.z==0)||(n.x==-1 && n.y==0 && n.z==0)){
            dentro = ((P.y<=ai.y && P.y>=abi.y && P.z<=ad.z && P.z>=ai.z) || (!esFinito));
        }
        //Techo o suelo
        else if((n.x==0 && n.y==-1 && n.z==0)||(n.x==0 && n.y==1 && n.z==0)){
            dentro = ((P.x>=ai.x && P.x<=ad.x && P.z<=abi.z && P.z>=ai.z) || (!esFinito));
        }
        else{
            if(!esFinito){
                dentro = true;
            }
        }
        return dentro;
    }

    //Obtiene el color presente en la posición de la textura adecuada de acuerdo a la normal y punto de corte
    Rgb colorTextura(Punto P, Direccion n){
        int dimX;
        int dimY;
        float pX;
        float pY;
        int pixelX;
        int pixelY;
        float r,g,b;

        //Pared izq o pared der
        if((n.x==1 && n.y==0 && n.z==0)||(n.x==-1 && n.y==0 && n.z==0)){
            dimX=ad.z-ai.z;
            dimY=ad.y-abd.y;
            pX=(P.z-ai.z)/(float)dimX;
            pY=(ad.y-P.y)/(float)dimY;
            pixelX=pX*textura.dimX;
            pixelY=pY*textura.dimY;
            if(pixelX==0){pixelX=1;}
            if(pixelY==0){pixelY=1;}

            textura.getRGB(pixelX,pixelY,r,g,b);
        }
        //Techo o suelo
        else if((n.x==0 && n.y==1 && n.z==0)||(n.x==0 && n.y==-1 && n.z==0)){
            dimX=ad.x-ai.x;
            dimY=abd.z-ad.z;
            pX=(P.x-ai.x)/(float)dimX;
            pY=(P.z-ai.z)/(float)dimY;
            pixelX=pX*textura.dimX;
            pixelY=pY*textura.dimY;
            if(pixelX==0){pixelX=1;}
            if(pixelY==0){pixelY=1;}

            textura.getRGB(pixelX,pixelY,r,g,b);
        }
        //Pared fondo
        else if((n.x==0 && n.y==0 && n.z==-1)){
            dimX=ad.x-ai.x;
            dimY=ad.y-abd.y;
            pX=(P.x-ai.x)/(float)dimX;
            pY=(ai.y-P.y)/(float)dimY;
            pixelX=pX*textura.dimX;
            pixelY=pY*textura.dimY;
            if(pixelX==0){pixelX=1;}
            if(pixelY==0){pixelY=1;}

            textura.getRGB(pixelX,pixelY,r,g,b);
        }
        
        return Rgb(r/255.0f,g/255.0f,b/255.0f);
    }

    //Comprueba si dos esferas son iguales
    bool iguales(Plano p){
        return (n==p.n && pp==p.pp);
    }
};
    

