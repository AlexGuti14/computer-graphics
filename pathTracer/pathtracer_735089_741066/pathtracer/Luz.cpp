#include <iostream>    

using namespace std;

//Representa una fuente de luz puntual
class Luz{
public:

    //Atributos
    Punto pos;
    Rgb pot;
    Rgb rgb;

    //Constructor
	Luz(Punto pos, Rgb pot, Rgb rgb) {
        this->pos.x = pos.x;
		this->pos.y = pos.y;
        this->pos.z = pos.z;
        this->pot=pot;
        this->rgb=rgb;
	}

};
    

