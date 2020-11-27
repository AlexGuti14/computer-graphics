#include <iostream>
#include "PathTracer.cpp"
#include "Escenas.cpp"

using namespace std::chrono; 

int main(int argc, char *argv[]) {

  //RESOLUCION
  const int W = atoi(argv[2]);
  const int H = atoi(argv[3]);

  //CAMINOS POR PIXEL
  float numRayos=atoi(argv[1]);
  
  //CAMARA
  Camara camara(Direccion(0,H/2,0),Direccion(W/2,0,0),Direccion(0,0,H/(2*tan(0.32))),Punto(W/2,H/2,0));

  //SELECCIONAR LA ESCENA A CREAR
  Escenas escena(1,W,H,camara);

  Listas lista(escena.getEsferas(),escena.getPlanos(),escena.getLuces());

  Imagen imagen(H,W,argv[4]);

  PathTracer tracer = PathTracer(lista, camara, numRayos, camara.f.z, imagen);
  tracer.renderImageMultithread();

}
