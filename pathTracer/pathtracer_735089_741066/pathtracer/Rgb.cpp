#include <iostream>

using namespace std;

//Color
class Rgb{
public:

    float r,g,b;

    Rgb(){
        this->r=0;
        this->g=0;
        this->b=0;
    }
    
    Rgb(float r,float g,float b){
        this->r=r;
        this->g=g;
        this->b=b;
    }

    float getR(){
        return r;
    }

    float getG(){
        return g;
    }

    float getB(){
        return b;
    }

    Rgb operator +(const Rgb &c){
        return Rgb(r + c.r, g + c.g, b + c.b);
    }

    Rgb operator -(const Rgb &c){
        return Rgb(r - c.r, g - c.g, b - c.b);
    }

    Rgb operator *(const Rgb &c){
        return Rgb(r*c.r, g*c.g, b*c.b);
    }

    Rgb operator *(const float &c){
        return Rgb(r*c, g*c, b*c);
    }

    Rgb operator *(const Punto &c){
        return Rgb(r*c.x, g*c.y, b*c.z);
    }

    Rgb operator *(const Direccion &c){
        return Rgb(r*c.x, g*c.y, b*c.z);
    }

    Rgb operator /(const Rgb &c){
        return Rgb(r/c.r, g/c.g, b/c.b);
    }

    Rgb operator /(const float &c){
        return Rgb(r/c, g/c, b/c);
    }

    bool cero(){
        return (r==0 && g==0 && b==0);
    }

    float max(){
        if(r>=g && r>=b){
            return r;
        }
        else if(g>r && g>=b){
            return g;
        }
        else{
            return b;
        }

    }
    
};

    


    