#include <iostream>

using namespace std;

//Representa la camara(pinhole) desde la que se ve la escena
class Camara{
public:
    //Atributos
    Direccion u,r,f;     //u:eje vertical r:eje horizontal f:eje frontal
    Punto o;            //posición camara pinhole

    //Constructor
    Camara(){}

    //Constructor
	Camara(Direccion up, Direccion right, Direccion front, Punto origen) {
        this->u = up;
		this->r = right;
        this->f = front;
        this->o = origen;
	}

    //Getters
    Punto getO(){
        return o;
    }

};


