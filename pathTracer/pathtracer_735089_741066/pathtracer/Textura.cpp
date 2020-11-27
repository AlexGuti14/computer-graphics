#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//Imagen que se añade a la superficie de una figura
class Textura{
public:

    //Atributos
    int dimX;
    int dimY;
    float* R;
    float* G;
    float* B;

    //Constructor
	Textura(string t) {
        ifstream f(t);
        string linea;
        string rgb;
        getline(f,linea); //P3
        getline(f,linea); //400 400 255

        istringstream iss(linea);
        iss >> rgb;
        this->dimX=stoi(rgb);
        iss >> rgb;
        this->dimY=stoi(rgb);

        R=new float[dimX*dimY];
        G=new float[dimX*dimY];
        B=new float[dimX*dimY];

        //Se guarda el color asociado a cada pixel de la textura
        int i=1;
        while(!f.eof()){
            getline(f,linea); //0 0 3
            istringstream iss(linea);
            iss >> rgb;
            this->R[i]=stoi(rgb);
            iss >> rgb;
            this->G[i]=stoi(rgb);
            iss >> rgb;
            this->B[i]=stoi(rgb);
            i++;    
        }
        
	}

    //Constructor
    Textura(){

    }

    //Devuelve el color presente en la posicion (x,y) de la textura
    void getRGB(int x, int y, float& r, float& g, float& b){
        int pos=y*dimX-(dimY-x);
        r=R[pos];
        g=G[pos];
        b=B[pos];
    }

    //Libera la memoria ocupada
    void finTextura(){
        delete[] R;
        delete[] G;
        delete[] B;
    }

};
    
