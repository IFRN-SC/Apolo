#include"Motores.h"
#include <Arduino.h>
#include <robo_hardware2.h>

void Motores::seguirFrente(){
  robo.acionarMotores(40,40);
}
void Motores::virarEsq(){
  robo.acionarMotores(-40,40);
}
void Motores::virarDir(){
  robo.acionarMotores(40,-40);
}
void Motores::re(){
  robo.acionarMotores(-40,-40);
}
void Motores::parar(){
  robo.acionarMotores(0,0);
}
void Motores::virarDirU(){
  robo.acionarMotores(0,-40);
}
void Motores::virarEsqU(){
  robo.acionarMotores(-40,0);
}
