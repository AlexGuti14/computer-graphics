#include <iostream>

using namespace std;

//Matriz 4x4
class Matrix4{
public:
    //Atributos
    float m[4][4];
    
    //Constructor (Traslacion(0) + escalado(1))
	Matrix4(float tx, float ty, float tz, int transformation) {
        if(transformation==0){
            m[0][0]=1;  m[0][1]=0;  m[0][2]=0;  m[0][3]=tx;
            m[1][0]=0;  m[1][1]=1;  m[1][2]=0;  m[1][3]=ty;
            m[2][0]=0;  m[2][1]=0;  m[2][2]=1;  m[2][3]=tz;
            m[3][0]=0;  m[3][1]=0;  m[3][2]=0;  m[3][3]=1;
        }
        else{
            m[0][0]=tx;  m[0][1]=0;  m[0][2]=0;  m[0][3]=0;
            m[1][0]=0;   m[1][1]=ty;  m[1][2]=0;  m[1][3]=0;
            m[2][0]=0;  m[2][1]=0;  m[2][2]=tz;  m[2][3]=0;
            m[3][0]=0;  m[3][1]=0;  m[3][2]=0;  m[3][3]=1;
        }
        
	}

    //Constructor (Rotacion)
    Matrix4(float th, int axis) {
        if(axis==0){
            m[0][0]=1;  m[0][1]=0;         m[0][2]=0;          m[0][3]=0;
            m[1][0]=0;  m[1][1]=cos(th);   m[1][2]=-sin(th);   m[1][3]=0;
            m[2][0]=0;  m[2][1]=sin(th);   m[2][2]=cos(th);    m[2][3]=0;
            m[3][0]=0;  m[3][1]=0;         m[3][2]=0;          m[3][3]=1;
        }
        else if(axis==1){
            m[0][0]=cos(th);    m[0][1]=0;      m[0][2]=sin(th);    m[0][3]=0;
            m[1][0]=0;          m[1][1]=1;      m[1][2]=0;          m[1][3]=0;
            m[2][0]=-sin(th);   m[2][1]=0;      m[2][2]=cos(th);    m[2][3]=0;
            m[3][0]=0;          m[3][1]=0;      m[3][2]=0;          m[3][3]=1;
        }
        else if(axis==2){
            m[0][0]=cos(th);    m[0][1]=-sin(th);   m[0][2]=0;      m[0][3]=0;
            m[1][0]=sin(th);    m[1][1]=cos(th);    m[1][2]=0;      m[1][3]=0;
            m[2][0]=0;          m[2][1]=0;          m[2][2]=1;     m[2][3]=0;
            m[3][0]=0;          m[3][1]=0;          m[3][2]=0;      m[3][3]=1;
        }
        
	}

    //Constructor (Cambio de base)
    Matrix4(Direccion u, Direccion v, Direccion w, Punto o) {
        m[0][0]=u.x;    m[0][1]=v.x;    m[0][2]=w.x;    m[0][3]=o.x;
        m[1][0]=u.y;    m[1][1]=v.y;    m[1][2]=w.y;    m[1][3]=o.y;
        m[2][0]=u.z;    m[2][1]=v.z;    m[2][2]=w.z;    m[2][3]=o.z;
        m[3][0]=0;      m[3][1]=0;      m[3][2]=0;      m[3][3]=1;
	}

    //Construcor
    Matrix4(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                m[i][j]=0;
            }
        }
    }

    float getValue(int index1, int index2){
        return this->m[index1][index2];
    }

    void setValue(int index1, int index2, int value){
        this->m[index1][index2]=value;
    }

    
    Direccion doTransformation(Direccion d){
        float a=m[0][0]*d.x + m[0][1]*d.y + m[0][2]*d.z + m[0][3]*d.v;
        float b=m[1][0]*d.x + m[1][1]*d.y + m[1][2]*d.z + m[1][3]*d.v;
        float c=m[2][0]*d.x + m[2][1]*d.y + m[2][2]*d.z + m[2][3]*d.v;
        float e=m[3][0]*d.x + m[3][1]*d.y + m[3][2]*d.z + m[3][3]*d.v;
        return Direccion(a,b,c,e);
    }

    Punto doTransformation(Punto p){
        float a=m[0][0]*p.x + m[0][1]*p.y + m[0][2]*p.z + m[0][3]*p.v;
        float b=m[1][0]*p.x + m[1][1]*p.y + m[1][2]*p.z + m[1][3]*p.v;
        float c=m[2][0]*p.x + m[2][1]*p.y + m[2][2]*p.z + m[2][3]*p.v;
        float e=m[3][0]*p.x + m[3][1]*p.y + m[3][2]*p.z + m[3][3]*p.v;
        return Punto(a,b,c,e);
    }

    Matrix4& inversaTraslacion(){
        Matrix4 *resul= new Matrix4();
        for(int i=0; i < 3; i++){
            for(int j=0; j < 4; j++){
                resul->setValue(j,i,m[j][i]);
            }
        } 
        resul->setValue(0,3,-m[0][3]);
        resul->setValue(1,3,-m[1][3]);
        resul->setValue(2,3,-m[2][3]);
        resul->setValue(3,3,m[3][3]);
        return *resul;
    }

    Matrix4& inversaEscalado(){
        Matrix4 *resul= new Matrix4();
        for(int i=0; i < 4; i++){
            for(int j=0; j < 4; j++){
                resul->setValue(j,i,m[j][i]);
            }
        } 
        resul->setValue(0,0,1/m[0][0]);
        resul->setValue(1,1,1/m[1][1]);
        resul->setValue(2,2,1/m[2][2]);
        return *resul;
    }

    //Operaciones
    friend Matrix4 operator +(Matrix4 &m1, Matrix4 &m2);
    friend Matrix4 operator -(Matrix4 &m1, Matrix4 &m2);
    friend Matrix4 operator *(float s1, Matrix4 &m);
    friend ostream& operator << (ostream &o, Matrix4 &m);
    

    

};

    Matrix4 operator +(Matrix4 &m1, Matrix4 &m2){
        Matrix4 resul;
        for(int i=0; i < 4; i++){
            for(int j=0; j < 4; j++){
                resul.setValue(i,j,m1.getValue(i,j)+m2.getValue(i,j));
            }
        }
        return resul; 
    }

    Matrix4 operator -(Matrix4 &m1, Matrix4 &m2){
        Matrix4 resul;
        for(int i=0; i < 4; i++){
            for(int j=0; j < 4; j++){
                resul.setValue(i,j,m1.getValue(i,j)-m2.getValue(i,j));
            }
        }
        return resul; 
    }

    Matrix4 operator *(float s1, Matrix4 &m){
        Matrix4 resul;
        for(int i=0; i < 4; i++){
            for(int j=0; j < 4; j++){
                resul.setValue(i,j,m.getValue(i,j)*s1);
            }
        }
        return resul; 
    }

    // Sobrecarga del operador << para la clase Matrix4
    ostream& operator << (ostream &o, Matrix4 &m){
        o << "[ " << m.getValue(0,0) << "  " << m.getValue(0,1) << "  " << m.getValue(0,2) << "  " << m.getValue(0,3) <<" ]" << endl;
        o << "[ " << m.getValue(1,0) << "  " << m.getValue(1,1) << "  " << m.getValue(1,2) << "  " << m.getValue(1,3) <<" ]" << endl;
        o << "[ " << m.getValue(2,0) << "  " << m.getValue(2,1) << "  " << m.getValue(2,2) << "  " << m.getValue(2,3) <<" ]" << endl;
        o << "[ " << m.getValue(3,0) << "  " << m.getValue(3,1) << "  " << m.getValue(3,2) << "  " << m.getValue(3,3) <<" ]" << endl;
        return o;
    }



    