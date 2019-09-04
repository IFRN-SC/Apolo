#include <cor.h>
#include <CorHardware.h>
#include <CorTcs23.h>
#include <CorTcs34.h>
#include <EEPROM2.h>
#include <pinagem.h>
#include <robo_hardware2.h>
#include <SensoresCor.h>
#include <Ultrasonic.h>

#include <Arduino.h>
#include <robo_hardware2.h>
#include "Estrategia.h"

Estrategia apolo;
void setup(){
    Serial.begin(9600);
    robo.configurar(true);
   /* robo.habilitaTCS34();*/
    apolo.calibracao();
}
void loop(){
    apolo.exec();
}
