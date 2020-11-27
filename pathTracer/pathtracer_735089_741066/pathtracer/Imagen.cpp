#include <iostream>
#include "Tone_mapping.cpp"

using namespace std;

//Gestion de la imagen resultante
class Imagen{
public:
    
    //Atributos
    Rgb * img;
    int W, H;
    Tone_mapping t;
    string nombre;

    //Constructor
    Imagen(){}

    //Constructor
    Imagen(int h, int w, string nombre){
        this->H=h;
        this->W=w;
        img = new Rgb[h*w];
        this->nombre=nombre;
    }

    //Getters
    int getH(){
        return H;
    }
    
    int getW(){
        return W;
    }

    //Acceder a una posicion del vector
    Rgb& operator()(int row, int col) const {
        return img[(row*W) + col];
    }

    //Escribir la imagen generada en un fichero
    void write(){
        ofstream out(nombre+".ppm");
        out << "P3\n" << W << ' ' << H << '\n' << "255\n";

        out << '\t';
        for(int y=H-1;y>=0;y--){
            for(int x=0;x<W;x++){
                out << (int)t.clamping((*this)(y,x).r,255) << '\t'; 
                out << (int)t.clamping((*this)(y,x).g,255) << '\t';
                out << (int)t.clamping((*this)(y,x).b,255) << '\t' << '\t'; 
            }
            out << endl << '\t';
        }
        out.close();
        delete[] img;
    }
	

};

