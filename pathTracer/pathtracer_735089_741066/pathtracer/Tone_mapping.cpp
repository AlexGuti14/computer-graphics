#include <iostream>

using namespace std;

class Tone_mapping{
public:

    float clamping(float dato, int rango){
        if(dato>=rango){
            dato=rango;
        }
        else if(dato<0){
            dato=0;
        }
        return dato;
    }

    float equalization(float dato, float rango, float max){
        return (dato*rango)/max;
    }

    float equalizeYclamp(float dato, float rango, float max){
        float d = equalization(dato,rango,max);
        return clamping(d,rango);
    }

    float gammaCurve(float dato, float rango, float max){
        float d = equalization(dato,1,max);
        float gamma=1.6;
        return pow(d, gamma)*65535;
    }

    float clampYgammaCurve(float dato, float rango, float max){
        float d = equalizeYclamp(dato,rango,max);
        float gamma=1.6;
        return pow(d, gamma)*65535;
    }


    //Dada una f, elige la función seleccionada
    float elegirFuncion(int f, float dato, int rango, int max){
        if(f == 1){
            return clamping(dato,rango);
        }
        else if(f == 2){
            return equalization(dato,rango,max);
        }
        else if(f == 3){
            return equalizeYclamp(dato,rango,max);
        }
        else if(f == 4){
            return gammaCurve(dato,rango,max);
        }
        else if(f == 5){
            return clampYgammaCurve(dato,rango,max);
        }
        else{
            return 0;
        }
    }

    //Carga la imagen
    void load(string fichero, int funcion, float rango){
        ifstream f(fichero);
        ofstream fs("ldr_" + fichero);

        string linea;
        float colorResolution, storedValue, max, width, height, dato;

        //Lectura de primeros valores
        getline(f,linea);
        fs << linea << endl;
        getline(f,linea);
        fs << linea << endl;
        getline(f,linea);
        fs << linea << endl;
        f >> width >> height;
        fs << width << " " << height << endl;
        f >> colorResolution;
        fs << rango << endl;

        //Lee valores de 3 en 3 hasta la anchura de la imagen
        int limit = 3;
        int i=1;
        int j=1;

        while(!f.eof()){
          f >> storedValue;
          if(i<limit){
              dato = (storedValue/colorResolution)*65535;
              fs << round(elegirFuncion(funcion,dato,rango,65535)) << " ";
          }
          else{
              dato = (storedValue/colorResolution)*65535;
              fs << round(elegirFuncion(funcion,dato,rango,65535)) << "    ";
              i=0;
              j++;
          }
          if(j==width){
              fs << endl;
              j=1;
          }
          i++;
        }
        //Cierro ficheros
        f.close();
        fs.close();
    }
};
