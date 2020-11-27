#include <iostream>
#include <list>

using namespace std;

class Escenas{
public:

    list<Luz> listaLuces;
    list<Esfera> listaEsferas;
    list<Plano> listaPlanos;

    Escenas(int escena, int W, int H, Camara camara){
        //CORNELL LUZ PUNTUAL (640x480) (Figura 17 memoria) 
        if(escena==1){
            //FUENTES DE LUZ PUNTUALES 
            listaLuces.push_back(Luz(Punto(320,350,1050),Rgb(140000,140000,140000),Rgb(255,255,255)));

            //ESFERAS
            Punto centro1(440,100,1300);
            Direccion eje1(0,200,0); 
            Punto ciudad1(440,200,1300);           
            Esfera esfera(centro1,eje1,ciudad1,Rgb(0.26,0.3,0.78),Rgb(0.1,0.1,0.1),30,Rgb(0,0,0),Rgb(0,0,0),2,false);
            
            Punto centro2(150,100,900);
            Direccion eje2(0,200,0); 
            Punto ciudad2(150,200,900);           
            Esfera esfera2(centro2,eje2,ciudad2,Rgb(0,0,0),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),2,true);

            listaEsferas.push_back(esfera);
            listaEsferas.push_back(esfera2);

            //PLANOS
            Direccion n(1,0,0);
            Punto puntoPlano(0,200,351);
            Plano paredIzq(n,puntoPlano,Rgb(0.8,0.2,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n1(-1,0,0);
            Punto puntoPlano1(W,200,351);
            Plano paredDer(n1,puntoPlano1,Rgb(0.2,0.8,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n2(0,0,-1);
            Punto puntoPlano2(350,200,camara.f.z+700);
            Plano paredFondo(n2,puntoPlano2,Rgb(0.6,0.6,0.6),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n3(0,-1,0);
            Punto puntoPlano3(200,H,351);
            Plano techo(n3,puntoPlano3,Rgb(0.6,0.6,0.6),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n4(0,1,0);
            Punto puntoPlano4(200,0,351);
            Plano suelo(n4,puntoPlano4,Rgb(0.6,0.6,0.6),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            listaPlanos.push_back(paredIzq);
            listaPlanos.push_back(paredDer);
            listaPlanos.push_back(paredFondo);
            listaPlanos.push_back(techo);
            listaPlanos.push_back(suelo);
        }
        //CORNELL LUZ PUNTUAL (1280x720) 
        else if(escena==2){
            //FUENTES DE LUZ PUNTUALES 
            listaLuces.push_back(Luz(Punto(640,600,1636),Rgb(400000,400000,400000),Rgb(255,255,255)));

            //ESFERAS
            Punto centro1(940,150,2000);
            Direccion eje1(0,300,0); 
            Punto ciudad1(940,300,2000);           
            Esfera esfera(centro1,eje1,ciudad1,Rgb(0.26,0.3,0.78),Rgb(0.1,0.1,0.1),30,Rgb(0,0,0),Rgb(0,0,0),2,false);
            
            Punto centro2(250,150,1400);
            Direccion eje2(0,300,0); 
            Punto ciudad2(250,300,1400);           
            Esfera esfera2(centro2,eje2,ciudad2,Rgb(0,0,0),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),2,true);

            listaEsferas.push_back(esfera);
            listaEsferas.push_back(esfera2);

            //PLANOS
            Direccion n(1,0,0);
            Punto puntoPlano(0,200,351);
            Plano paredIzq(n,puntoPlano,Rgb(0.8,0.2,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n1(-1,0,0);
            Punto puntoPlano1(W,200,351);
            Plano paredDer(n1,puntoPlano1,Rgb(0.2,0.8,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n2(0,0,-1);
            Punto puntoPlano2(350,200,camara.f.z+1100);
            Plano paredFondo(n2,puntoPlano2,Rgb(0.6,0.6,0.6),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n3(0,-1,0);
            Punto puntoPlano3(200,H,351);
            Plano techo(n3,puntoPlano3,Rgb(0.6,0.6,0.6),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n4(0,1,0);
            Punto puntoPlano4(200,0,351);
            Plano suelo(n4,puntoPlano4,Rgb(0.6,0.6,0.6),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            listaPlanos.push_back(paredIzq);
            listaPlanos.push_back(paredDer);
            listaPlanos.push_back(paredFondo);
            listaPlanos.push_back(techo);
            listaPlanos.push_back(suelo);
        }
        //CORNELL LUZ AREA (640x480) (Figura 16 memoria)
        else if(escena==3){
            //ESFERAS
            Punto centro1(440,100,1300);
            Direccion eje1(0,200,0); 
            Punto ciudad1(440,200,1300);            
            Esfera esfera(centro1,eje1,ciudad1,Rgb(0.26,0.3,0.78),Rgb(0.1,0.1,0.1),20,Rgb(0,0,0),Rgb(0,0,0),2,false);
            
            Punto centro2(150,100,900);
            Direccion eje2(0,200,0); 
            Punto ciudad2(150,200,900);           
            Esfera esfera2(centro2,eje2,ciudad2,Rgb(0,0,0),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),2,true);

            listaEsferas.push_back(esfera);
            listaEsferas.push_back(esfera2);

            //PLANOS
            Direccion n(1,0,0);
            Punto puntoPlano(0,200,351);
            Plano paredIzq(n,puntoPlano,Rgb(0.8,0.2,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n1(-1,0,0);
            Punto puntoPlano1(W,200,351);
            Plano paredDer(n1,puntoPlano1,Rgb(0.2,0.8,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n2(0,0,-1);
            Punto puntoPlano2(350,200,camara.f.z+700);
            Plano paredFondo(n2,puntoPlano2,Rgb(0.6,0.6,0.6),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n3(0,-1,0);
            Punto puntoPlano3(200,H,351);
            Plano techo(n3,puntoPlano3,Rgb(0.6,0.6,0.6),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n4(0,1,0);
            Punto puntoPlano4(200,0,351);
            Plano suelo(n4,puntoPlano4,Rgb(0.6,0.6,0.6),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n5(0,-1,0);
            Punto puntoPlano5(200,479,900);
            Plano luzArea(Rgb(1700,1700,1700),n5,puntoPlano5,Punto(200,479,900),Punto(440,479,900),Punto(200,479,1200),Punto(440,479,1200),Rgb(1,1,1));

            listaPlanos.push_back(paredIzq);
            listaPlanos.push_back(paredDer);
            listaPlanos.push_back(paredFondo);
            listaPlanos.push_back(techo);
            listaPlanos.push_back(suelo);
            listaPlanos.push_back(luzArea);
        }
        //ESCENA PLANOS FINITOS DE MADERA Y 3 ESFERAS (640 x 480) (Figura 18 memoria)
        else if(escena==4){
            //TEXTURAS
            Textura madera("texturas/madera.ppm");
            Textura marmol("texturas/marmol.ppm");
            Textura marmol2("texturas/marmol2.ppm");
            Textura cuadro("texturas/cuadro.ppm");
            Textura sueloPatron("texturas/suelo.ppm");

            //ESFERAS
            Punto centro1(175,300,1100);
            Direccion eje1(0,200,0); 
            Punto ciudad1(175,400,1100);           
            Esfera esfera(centro1,eje1,ciudad1,Rgb(0,0,0),Rgb(0.1,0.1,0.1),30,Rgb(0,0,0),Rgb(0,0,0),2,false,marmol);

            Punto centro2(325,175,1100);
            Direccion eje2(0,150,0); 
            Punto ciudad2(325,250,1100);           
            Esfera esfera2(centro2,eje2,ciudad2,Rgb(0,0,0),Rgb(0,0,0),30,Rgb(0,0,0),Rgb(0,0,0),2,false,marmol2);

            Punto centro3(530,100,800);
            Direccion eje3(0,200,0); 
            Punto ciudad3(530,200,800);           
            Esfera esfera3(centro3,eje3,ciudad3,Rgb(0,0,0),Rgb(0,0,0),30,Rgb(0,0,0),Rgb(0,0,0),1.7,true);

            listaEsferas.push_back(esfera);
            listaEsferas.push_back(esfera2);
            listaEsferas.push_back(esfera3);

            //PLANOS
            Direccion n(1,0,0);
            Punto puntoPlano(0,200,351);
            Plano paredIzq(n,puntoPlano,Rgb(0.8,0.2,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n1(-1,0,0);
            Punto puntoPlano1(W,200,351);
            Plano paredDer(n1,puntoPlano1,Rgb(0.2,0.8,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n2(0,0,-1);
            Punto puntoPlano2(350,200,camara.f.z+700);
            Plano paredFondo(n2,puntoPlano2,Rgb(0.6,0.6,0.6),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n3(0,-1,0);
            Punto puntoPlano3(200,H,351);
            Plano techo(n3,puntoPlano3,Rgb(0.6,0.6,0.6),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n4(0,1,0);
            Punto puntoPlano4(0,0,700);
            Plano suelo(n4,puntoPlano4,Punto(0,0,700),Punto(640,0,700),Punto(0,0,1400),Punto(640,0,1400),Rgb(0,0,0),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false,sueloPatron);

            Direccion n5(-1,0,0);
            Punto puntoPlano5(630,400,520);
            Plano espejoDer(n5,puntoPlano5,Punto(639,400,750),Punto(639,400,1317),Punto(639,85,750),Punto(639,85,1317),Rgb(0,0,0),Rgb(0,0,0),0,Rgb(0.9,0.9,0.9),Rgb(0,0,0),0,false,cuadro);
            Direccion n51(0,0,-1);
            Punto puntoPlano51(630,400,750);
            Plano espejoDer1(n51,puntoPlano51,Punto(630,400,750),Punto(640,400,750),Punto(630,85,750),Punto(640,85,750),Rgb(1,1,1),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n6(1,0,0);
            Punto puntoPlano6(1,400,520);
            Plano espejoIzq(n6,puntoPlano6,Punto(1,400,700),Punto(1,400,1320),Punto(1,80,700),Punto(1,80,1320),Rgb(0,0,0),Rgb(0,0,0),0,Rgb(0.9,0.9,0.9),Rgb(0,0,0),0,false);
            
            Direccion n7(0,0,-1);
            Punto puntoPlano7(100,200,1000);
            Plano baseFrente(n7,puntoPlano7,Punto(100,200,1000),Punto(250,200,1000),Punto(100,0,1000),Punto(250,0,1000),Rgb(0.8,0.2,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false,madera);
            Direccion n8(-1,0,0);
            Punto puntoPlano8(100,200,1000);
            Plano baseIzq(n8,puntoPlano8,Punto(100,200,1000),Punto(100,200,1200),Punto(100,0,1000),Punto(100,0,1200),Rgb(0.8,0.2,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false,madera);
            Direccion n9(1,0,0);
            Punto puntoPlano9(250,200,1000);
            Plano baseDer(n9,puntoPlano9,Punto(250,200,1000),Punto(250,200,1200),Punto(250,0,1000),Punto(250,0,1200),Rgb(0.8,0.8,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false,madera);
            Direccion n10(0,1,0);
            Punto puntoPlano10(100,200,1000);
            Plano baseTecho(n10,puntoPlano10,Punto(100,200,1000),Punto(250,200,1000),Punto(100,200,1200),Punto(250,200,1200),Rgb(0.8,0.2,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false,madera);
            Direccion n15(0,0,-1);
            Punto puntoPlano15(100,200,1200);
            Plano baseFondo(n15,puntoPlano15,Punto(100,200,1200),Punto(250,200,1200),Punto(100,0,1200),Punto(250,0,1200),Rgb(0.8,0.2,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false,madera);

            Direccion n11(0,0,-1);
            Punto puntoPlano11(250,100,1000);
            Plano baseFrente2(n11,puntoPlano11,Punto(250,100,1000),Punto(400,100,1000),Punto(250,0,1000),Punto(400,0,1000),Rgb(0.8,0.2,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false,madera);
            Direccion n12(-1,0,0);
            Punto puntoPlano12(250,100,1000);
            Plano baseIzq2(n12,puntoPlano12,Punto(250,100,1000),Punto(250,100,1200),Punto(250,0,1000),Punto(250,0,1200),Rgb(0.8,0.2,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false,madera);
            Direccion n13(1,0,0);
            Punto puntoPlano13(400,100,1000);
            Plano baseDer2(n13,puntoPlano13,Punto(400,100,1000),Punto(400,100,1200),Punto(400,0,1000),Punto(400,0,1200),Rgb(0.8,0.2,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false,madera);
            Direccion n14(0,1,0);
            Punto puntoPlano14(250,100,1000);
            Plano baseTecho2(n14,puntoPlano14,Punto(250,100,1000),Punto(400,100,1000),Punto(250,100,1200),Punto(400,100,1200),Rgb(0,0,0),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false,madera);
            Direccion n16(0,0,-1);
            Punto puntoPlano16(250,100,1200);
            Plano baseFondo2(n16,puntoPlano16,Punto(250,100,1200),Punto(400,100,1200),Punto(250,0,1200),Punto(400,0,1200),Rgb(0.8,0.2,0.2),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false,madera);

            Direccion n17(0,-1,0);
            Punto puntoPlano17(50,479,50);
            Plano luzArea(Rgb(1400,1400,1400),n17,puntoPlano17,Punto(50,479,750),Punto(150,479,750),Punto(50,479,950),Punto(150,479,950),Rgb(1,1,1));

            Direccion n18(0,-1,0);
            Punto puntoPlano18(490,479,50);
            Plano luzArea2(Rgb(1400,1400,1400),n18,puntoPlano18,Punto(490,479,750),Punto(590,479,750),Punto(490,479,950),Punto(590,479,950),Rgb(1,1,1));
            
            Direccion n19(0,-1,0);
            Punto puntoPlano19(50,479,1150);
            Plano luzArea3(Rgb(1400,1400,1400),n19,puntoPlano19,Punto(50,479,1150),Punto(150,479,1150),Punto(50,479,1350),Punto(150,479,1350),Rgb(1,1,1));

            Direccion n20(0,-1,0);
            Punto puntoPlano20(490,479,1150);
            Plano luzArea4(Rgb(1400,1400,1400),n20,puntoPlano20,Punto(490,479,1150),Punto(590,479,1150),Punto(490,479,1350),Punto(590,479,1350),Rgb(1,1,1));
            
            listaPlanos.push_back(paredIzq);
            listaPlanos.push_back(paredDer);
            listaPlanos.push_back(paredFondo);
            listaPlanos.push_back(techo);
            listaPlanos.push_back(suelo);
            listaPlanos.push_back(espejoDer);
            listaPlanos.push_back(espejoDer1);
            listaPlanos.push_back(espejoIzq);
            listaPlanos.push_back(baseFrente);
            listaPlanos.push_back(baseFondo);
            listaPlanos.push_back(baseIzq);
            listaPlanos.push_back(baseDer);
            listaPlanos.push_back(baseTecho);
            listaPlanos.push_back(baseFrente2);
            listaPlanos.push_back(baseFondo2);
            listaPlanos.push_back(baseIzq2);
            listaPlanos.push_back(baseDer2);
            listaPlanos.push_back(baseTecho2);
            listaPlanos.push_back(luzArea);
            listaPlanos.push_back(luzArea2);
            listaPlanos.push_back(luzArea3);
            listaPlanos.push_back(luzArea4);
        }
        //ESCENA CON 7 ESFERAS DE DISTINTOS MATERIALES (640x480) (Figura 19 memoria)
        else if(escena==5){
            //FUENTES DE LUZ PUNTUALES 
            listaLuces.push_back(Luz(Punto(320,240,680),Rgb(93000,93000,93000),Rgb(255,255,255)));

            //ESFERAS
            Punto centro1(120,100,800);
            Direccion eje1(0,150,0); 
            Punto ciudad1(120,175,800);           
            Esfera esfera(centro1,eje1,ciudad1,Rgb(0.78,0.75,0.24),Rgb(0,0,0),20,Rgb(0.9,0.9,0.9),Rgb(0,0,0),2,false);

            Punto centro2(540,220,810);
            Direccion eje2(0,150,0); 
            Punto ciudad2(540,295,810);           
            Esfera esfera2(centro2,eje2,ciudad2,Rgb(0.23,0.51,0.8),Rgb(0.1,0.1,0.1),10,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Punto centro3(350,350,960);
            Direccion eje3(0,150,0); 
            Punto ciudad3(350,425,960);            
            Esfera esfera3(centro3,eje3,ciudad3,Rgb(0.8,0.2,0.2),Rgb(0,0,0),20,Rgb(0,0,0),Rgb(0,0,0),2,false);
            
            Punto centro4(75,300,1050);
            Direccion eje4(0,150,0); 
            Punto ciudad4(75,375,1050);           
            Esfera esfera4(centro4,eje4,ciudad4,Rgb(0,0,0),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),1.5,true);

            Punto centro5(350,75,840);
            Direccion eje5(0,150,0); 
            Punto ciudad5(350,150,840);           
            Esfera esfera5(centro5,eje5,ciudad5,Rgb(0,0,0),Rgb(0,0,0),20,Rgb(0,0,0),Rgb(0,0,0),2,true);
            
            Punto centro6(540,75,950);
            Direccion eje6(0,150,0); 
            Punto ciudad6(540,150,950);           
            Esfera esfera6(centro6,eje6,ciudad6,Rgb(0,0,0),Rgb(0,0,0),20,Rgb(0.9,0.9,0.9),Rgb(0,0,0),2,false);

            Punto centro7(220,75,1100);
            Direccion eje7(0,150,0); 
            Punto ciudad7(220,150,1100);           
            Esfera esfera7(centro7,eje7,ciudad7,Rgb(0.2,0.8,0.2),Rgb(0.2,0.2,0.2),30,Rgb(0,0,0),Rgb(0,0,0),2,false);
            
            listaEsferas.push_back(esfera);
            listaEsferas.push_back(esfera2);
            listaEsferas.push_back(esfera3);
            listaEsferas.push_back(esfera4);
            listaEsferas.push_back(esfera5);
            listaEsferas.push_back(esfera6);
            listaEsferas.push_back(esfera7);

            //PLANOS
            Direccion n(1,0,0);
            Punto puntoPlano(0,200,351);
            Plano paredIzq(n,puntoPlano,Rgb(0.61,0.62,0.8),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n1(-1,0,0);
            Punto puntoPlano1(W,200,351);
            Plano paredDer(n1,puntoPlano1,Rgb(0.73,0.8,0.61),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n2(0,0,-1);
            Punto puntoPlano2(350,200,camara.f.z+500);
            Plano paredFondo(n2,puntoPlano2,Rgb(0.8,0.8,0.8),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n3(0,-1,0);
            Punto puntoPlano3(200,H,351);
            Plano techo(n3,puntoPlano3,Rgb(0.8,0.8,0.8),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            Direccion n4(0,1,0);
            Punto puntoPlano4(200,0,351);
            Plano suelo(n4,puntoPlano4,Rgb(0.8,0.8,0.8),Rgb(0,0,0),0,Rgb(0,0,0),Rgb(0,0,0),0,false);

            listaPlanos.push_back(paredIzq);
            listaPlanos.push_back(paredDer);
            listaPlanos.push_back(paredFondo);
            listaPlanos.push_back(techo);
            listaPlanos.push_back(suelo);
        }

    }

    list<Luz> getLuces(){
        return listaLuces;
    }
    
    list<Plano> getPlanos(){
        return listaPlanos;
    }

    list<Esfera> getEsferas(){
        return listaEsferas;
    }
    
    
    

   


   
    
};

    


    