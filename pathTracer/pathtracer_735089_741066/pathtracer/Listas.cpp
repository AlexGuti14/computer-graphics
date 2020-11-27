#include <iostream>

using namespace std;

//Contiene listas para mejorar la limpieza de codigo
class Listas{
public:

    //Atributos
    list<Esfera> listaEsferas;
    list<Plano> listaPlanos;
    list<Luz> listaLuces;

    //Constructor
    Listas(){}

    //Constructor
	Listas(list<Esfera> listaEsferas,list<Plano> listaPlanos,list<Luz> listaLuces) {
        this->listaEsferas=listaEsferas;
        this->listaPlanos=listaPlanos;
        this->listaLuces=listaLuces;
	}

};

