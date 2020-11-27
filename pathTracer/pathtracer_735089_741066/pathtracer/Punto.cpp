#include <iostream>
#include <math.h>       
#include "Direccion.cpp"

using namespace std;

//Punto
class Punto{
public:
    //Atributos
    float x, y, z, v;

    //Constructor
	Punto() {
        this->x = 1.0;
		this->y = 1.0;
		this->z = 1.0;
        this->v = 1.0;
	}

    //Constructor
	Punto(float xpos,float ypos,float zpos) {
        this->x = xpos;
		this->y = ypos;
		this->z = zpos;
        this->v = 1.0;
	}

    //Constructor
	Punto(float xpos,float ypos,float zpos, float vpos) {
        this->x = xpos;
		this->y = ypos;
		this->z = zpos;
        this->v = vpos;
        
	}

    Punto operator +(const Punto &p){
        return Punto(x + p.x, y + p.y, z + p.z);
    }

    Direccion operator -(const Punto &p){
        return Direccion(x - p.x, y - p.y, z - p.z);
    }

    Punto operator *(const Punto &p){
        return Punto(x * p.x, y * p.y, z * p.z);
    }

    Punto operator /(const Punto &p){
        return Punto(x / p.x, y / p.y, z / p.z);
    }

    bool operator ==(const Punto &p){
        return (x==p.x && y==p.y && z==p.z);
    }

    Punto operator +(const Direccion &d){
        return Punto(x + d.x, y + d.y, z + d.z);
    }
    
    Punto operator -(const Direccion &d){
        return Punto(x - d.x, y - d.y, z - d.z);
    }
};
    
    // Sobrecarga del operador << 
    ostream& operator << (ostream &o, Punto p){
        o << "(" << p.x << ", " << p.y <<", " << p.z << ", " << p.v << ")";
        return o;
    }

    //Producto escalar
    float dot(Punto p1, Punto p2){
      return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
    }

    //Producto escalar
    float dot(Direccion d, Punto p){
      return d.x * p.x + d.y * p.y + d.z * p.z;
    }

    //Distancia entre 2 puntos
    float distance(Punto p1, Punto p2) {
        Direccion p = p2 - p1;
        return module(p);
    }
    

