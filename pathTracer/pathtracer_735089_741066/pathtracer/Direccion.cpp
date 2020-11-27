#include <iostream>


using namespace std;

//Direccion
class Direccion{
public:
    //Atributos
    float x, y, z, v;

    //Constructor
	Direccion() {
        this->x = 1.0;
		this->y = 1.0;
		this->z = 1.0;
        this->v = 0.0;
	}

    //Constructor
	Direccion(float xpos,float ypos,float zpos) {
        this->x = xpos;
		this->y = ypos;
		this->z = zpos;
        this->v = 0.0;
        
	}

    //Constructor
	Direccion(float xpos,float ypos,float zpos, float vpos) {
        this->x = xpos;
		this->y = ypos;
		this->z = zpos;
        this->v = vpos;
        
	}

    Direccion operator +(const Direccion &d){
        return Direccion(x + d.x, y + d.y, z + d.z);
    }

    Direccion operator -(const Direccion &d){
        return Direccion(x - d.x, y - d.y, z - d.z);
    }

    Direccion operator *(const Direccion &d){
        return Direccion(x * d.x, y * d.y, z * d.z);
    }

    Direccion operator *(const float &s){
        return Direccion(s * x, s * y, s * z);
    }

    Direccion operator /(const float &s){
        return Direccion(x / s, y / s, z / s);
    }

    Direccion operator /(const Direccion &d){
        return Direccion(x / d.x, y / d.y, z / d.z);
    }

    bool operator ==(const Direccion &d){
        return (x==d.x && y==d.y && z==d.z);
    }

    
};
    
    // Sobrecarga del operador <<
    ostream& operator << (ostream &o, Direccion d){
        o << "(" << d.x << ", " << d.y <<", " << d.z << ", " << d.v << ")";
        return o;
    }

    //Producto escalar
    float dot(Direccion d1, Direccion d2){
      return d1.x * d2.x + d1.y * d2.y + d1.z * d2.z;
    }

    //Producto vectorial
    Direccion cross(Direccion d1, Direccion d2){
        return Direccion(d1.y*d2.z - d1.z*d2.y, d1.z*d2.x - d1.x*d2.z, d1.x*d2.y - d1.y*d2.x);
    }

    //Modulo
    float module(Direccion d){
        return sqrt(d.x*d.x + d.y*d.y  + d.z*d.z);
    }

    //Normalizacion
    Direccion normalize(Direccion d){
        float modulo=module(d);
        return Direccion(d.x/modulo,d.y/modulo,d.z/modulo);
    }


