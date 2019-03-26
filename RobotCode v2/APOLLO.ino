#include <Adafruit_TCS34725.h>
#include <cor.h>
#include <CorHardware.h>
#include <CorTcs23.h>
#include <CorTcs34.h>
#include <EEPROM2.h>
#include <main.h>
#include <pinagem.h>
#include <robo_hardware2.h>
#include <SensoresCor.h>
#include <Ultrasonic.h>

#include <Arduino.h>
#include <robo_hardware2.h>
#include <main.h>

float delayOneEsq = 0; // Tempo que o robô leva para iniciar o giro a esquerda
float delayTwoEsq = 0; // Tempo que o robô passa girando a esquerda
float delayOneDir = 0; // Tempo que o robo leva para iniciar o giro a direita
float delayTwoDir = 0; // Tempo que o robo passa girando a direita

float verde[2] = {0, 0};

int pinMaisEsq = 2;
int pinEsq = 3;
int pinDir = 1;
int pinMaisDir = 0;

calibracao_dados val;

void setup() {
    Serial.begin(9600);
    robo.configurar(false);    
}

void loop() { 
    btnSubirRampa = robo.botao1Pressionado();
    btnCalibrarBranco = robo.botao2Pressionado();
    btnSeguirLinha = robo.botao3Pressionado();

    if (btnSubirRampa == true) {
        calibrarVerde();        
    } else if (btnCalibrarBranco == true) {    
        calibrarBranco();
        delay(5000);
        calibrarPreto();
        for (int i=0; i<4; i++) { 
            valorCorte[i] = (valorBranco[i] + valorPreto[i])/2;      
        }
        val.refletanciaMaisEsq = valorCorte[0];
        val.refletanciaEsq = valorCorte[1];
        val.refletanciaDir = valorCorte[2];
        val.refletanciaMaisDir = valorCorte[3];
        robo.salvarCalibracao(val);
    } else if (btnSeguirLinha == true) {        
        robo.lerCalibracao(val);
        valorCorte[0] = val.refletanciaMaisEsq;
        valorCorte[1] = val.refletanciaEsq;
        valorCorte[2] = val.refletanciaDir;
        valorCorte[3] = val.refletanciaMaisDir;    
        for (int i = 0; i < 4; i++) {
            Serial.print("VALOR DE CORTE ");
            Serial.print(i);
            Serial.print(" : ");
            Serial.println(valorCorte[i]);
        }
        if (seguirLinha) {
            seguirLinha = false;
            robo.desligarLed(3);
        } else {
            seguirLinha = true;
            robo.ligarLed(3);
        }
    }
    
    if (seguirLinha) {            
        if ((robo.lerSensorSonarEsq() < 10)) {
            initRampa();
        } else if (robo.lerSensorSonarFrontal() < 10) {
           desviarObstaculo();
        } else {
            initSeguirLinha();
        }
    } else if (rampa) {
        initRampa();
    } else {
        robo.acionarMotores(0,0);
    }
}

void calibrarPreto() {
    float valorSensores[4] = {0, 0, 0, 0};
  
    Serial.println("Calibrando preto");
    Serial.print("[");
    for (int i=0; i<40; i++){
        Serial.print(" ");
    }
    Serial.println("]");
    Serial.print(" ");
  
    for (int i=0; i<4; i++) {
        bool led = false;
        for (int j=0; j<10; j++) {
            valorSensores[0] = (analogRead(pinMaisEsq)/1023.0)*100.0;
            valorSensores[1] = (analogRead(pinEsq)/1023.0)*100.0;
            valorSensores[2] = (analogRead(pinDir)/1023.0)*100.0;
            valorSensores[3] = (analogRead(pinMaisDir)/1023.0)*100.0;  
            valorPreto[i] += valorSensores[i];
            Serial.print("|");
            if (led) {
                led = false;
                robo.desligarLed(2);
            } else {
                led = true;
                robo.ligarLed(2);
            }
            delay(150);
        }
    }

    for (int i=0; i<4; i++) {
        valorPreto[i] /= 10;
        Serial.print("PRETO ");
        Serial.print(i);
        Serial.print(" : ");
        Serial.println(valorPreto[i]);
    }

    Serial.println();
    Serial.println("Preto calibrado");
}

void calibrarBranco() {
    float valorSensores[4] = {0, 0, 0, 0};
  
    Serial.println("Calibrando branco");
    Serial.print("[");
    for (int i=0; i<40; i++){
        Serial.print(" ");
    }
    Serial.println("]");
    Serial.print(" ");
  
    for (int i=0; i<4; i++) {
        bool led = false;
        for (int j=0; j<10; j++) {
            valorSensores[0] = (analogRead(pinMaisEsq)/1023.0)*100.0;
            valorSensores[1] = (analogRead(pinEsq)/1023.0)*100.0;
            valorSensores[2] = (analogRead(pinDir)/1023.0)*100.0;
            valorSensores[3] = (analogRead(pinMaisDir)/1023.0)*100.0;  
            valorBranco[i] += valorSensores[i];
            Serial.print("|");
            delay(150);
            if (led) {
                led = false;
                robo.desligarLed(2);
            } else {
                led = true;
                robo.ligarLed(2);
            }
        }
    }

    for (int i=0; i<4; i++) {
        valorBranco[i] /= 10;
        Serial.print("BRANCO ");
        Serial.print(i);
        Serial.print(" : ");
        Serial.println(valorBranco[i]);
    }
  
    Serial.println();
    Serial.println("Branco calibrado");
}

void initSeguirLinha() {        
    float sensores[4] = {0, 0, 0, 0};
    sensores[0] = (analogRead(pinMaisEsq)/1023.0)*100.0;
    sensores[1] = (analogRead(pinEsq)/1023.0)*100.0;
    sensores[2] = (analogRead(pinDir)/1023.0)*100.0;
    sensores[3] = (analogRead(pinMaisDir)/1023.0)*100.0;
        
   Serial.println("INICIANDO SEGUIR LINHA");
    Serial.print("[");
    for (int i=0; i<40; i++){
        Serial.print(" ");
    }
    Serial.println("]");
    Serial.print(" ");
    for (int j=0; j<10; j++) {
    Serial.print("|");

    }
     if(sensores[0] < valorCorte[0] && sensores[1] < valorCorte[1] && sensores[2] < valorCorte[2] && sensores[3] < valorCorte[3]) {//BBBB
        Serial.println("======RETA========");
        robo.acionarMotores(30,30);
     } else if(sensores[0] < valorCorte[0] && sensores[1] > valorCorte[1] && sensores[2] < valorCorte[2] && sensores[3] < valorCorte[3]) {//BPBB
        Serial.println("======INDIREITAR ROBO A ESQUERDA========");
        robo.acionarMotores(5,-5);
    } else if(sensores[0] < valorCorte[0] && sensores[1] < valorCorte[1] && sensores[2] > valorCorte[2] && sensores[3] < valorCorte[3]) {//BBPB
        Serial.println("======INDIREITAR ROBO A DIREITA========");
        robo.acionarMotores(-5,5);
    } else if (sensores[0] < valorCorte[0] && sensores[1] < valorCorte[1] && sensores[2] > valorCorte[2] && sensores[3] > valorCorte[3]) { // BBPP        
        Serial.println("======CURVA À DIREITA======");
        delay(delayOneDir);
        robo.acionarMotores(-30,30);    
        delay(delayTwoDir);
    } else if (sensores[0] > valorCorte[0] && sensores[1] > valorCorte[1] && sensores[2] < valorCorte[2] && sensores[3] < valorCorte[3]) { // PPBB       
         Serial.println("======CURVA À ESQUERDA======");
        delay(delayOneDir);
        robo.acionarMotores(30,-30);    
        delay(delayTwoDir);
    } else if (sensores[0] > valorCorte[0] && sensores[1] < valorCorte[1] && sensores[2] < valorCorte[2] && sensores[3] < valorCorte[3]) { // PBBB       
         Serial.println("======MANOBRAR À ESQUERDA======");
        delay(delayOneDir);
        robo.acionarMotores(-20,10);    
        delay(delayTwoDir);
    } else if (sensores[0] < valorCorte[0] && sensores[1] < valorCorte[1] && sensores[2] < valorCorte[2] && sensores[3] > valorCorte[3]) { // BBBP       
         Serial.println("======MANOBRAR À DIREITA======");
        delay(delayOneDir);
        robo.acionarMotores(10,-20);    
        delay(delayTwoDir);
    } else if (sensores[0] > valorCorte[0] && sensores[1] > valorCorte[1] && sensores[2] > valorCorte[2] && sensores[3] > valorCorte[3]) { // PPPP       
         Serial.println("======RETA PRETA======");
        delay(delayOneDir);
        robo.acionarMotores(20,20);    
        delay(delayTwoDir);
        
        
    } else if (sensores[1] > (verde[1]-4) && sensores[1] < (verde[1]+4)) { // VERDE ESQ
         Serial.println("======VERDE 1======");
        delay(delayOneEsq);
        robo.acionarMotores(30,-30);
        delay(delayTwoEsq);
    } else if (sensores[2] > (verde[2]-4) && sensores[2] < (verde[2]+4)) { // VERDE DIR
         Serial.println("======VERDE 2======");
        delay(delayOneDir);
        robo.acionarMotores(-30,30);    
        delay(delayTwoDir);
    } else if (sensores[2] < valorCorte[2] && sensores[1] > valorCorte[1]){ // DIR = branco e ESQ = preto        
         Serial.println("======INDIREITAR ROBO A ESQUERDA 2========");
        robo.acionarMotores(-10,10); // Curva à esquerda        
    } else if (sensores[2] > valorCorte[2] && sensores[1] < valorCorte[1]){ // DIR = preto e ESQ = branco            
         Serial.println("======INDIREITAR ROBO A DIREITA 2========");
        robo.acionarMotores(10,-10); // Curva à direita
    } else if (sensores[3] > valorCorte[3] && sensores[0] < valorCorte[0]) { // +DIR = preto ou +ESQ = branco        
         Serial.println("====CURVA À ESQUERDA 2====");
        robo.acionarMotores(35,-35);        
    } else if (sensores[3] < valorCorte[3] && sensores[0] > valorCorte[0]) { // +DIR = branco e +ESQ = preto                
         Serial.println("====CURVA À DIREITA 2====");
        robo.acionarMotores(-35,35);                
    } else {
        robo.acionarMotores(33,30);
    }
}

void initRampa() {        
    float sensores[4] = {0, 0, 0, 0};
    sensores[0] = (analogRead(0)/1023.0)*100.0;
    sensores[1] = (analogRead(1)/1023.0)*100.0;
    sensores[2] = (analogRead(2)/1023.0)*100.0;
    sensores[3] = (analogRead(3)/1023.0)*100.0;
    
    if (sensores[2] < valorCorte[2] && sensores[1] > valorCorte[1]){ // DIR = branco e ESQ = preto
        robo.acionarMotores(40,-5); // Curva à esquerda
    } else if (sensores[2] > valorCorte[2] && sensores[1] < valorCorte[1]){ // DIR = preto e ESQ = branco    
        robo.acionarMotores(-5,40); // Curva à direita
    } else if (sensores[3] > valorCorte[3] && sensores[0] < valorCorte[0]) { // +DIR = preto ou +ESQ = branco
        robo.acionarMotores(-5,40);
    } else if (sensores[3] < valorCorte[3] && sensores[0] > valorCorte[0]) { // +DIR = branco e +ESQ = preto
        robo.acionarMotores(40,-5);
    } else {
        robo.acionarMotores(60,60);
    }
}

void calibrarVerde() {
    boolean led = false;
     for (int j=0; j<10; j++) {
        verde[0] += (analogRead(1)/1023.0)*100.0;
        delay(100);
        if (led) {
          led = false;
          robo.desligarLed(2);
        } else {
          led = true;
          robo.ligarLed(2);
        }
     }    
    verde[0] /= 10;
    delay(5000);
    for (int j=0; j<10; j++) {
        verde[1] += (analogRead(2)/1023.0)*100.0;
        delay(100);
        if (led) {
          led = false;
          robo.desligarLed(2);
        } else {
          led = true;
          robo.ligarLed(2);
        }
     }    
    verde[1] /= 10;
}

void desviarObstaculo() {
  robo.acionarMotores(-10,-10);
    delay(1000); 
    robo.acionarMotores(-40,40); // Gira para a direita
    delay(350);
    robo.acionarMotores(0,0);
    delay(1000);
    robo.acionarMotores(40,35); // Vai para frente
    delay(550); 
    robo.acionarMotores(0,0);
    delay(1000);
    robo.acionarMotores(40,-40); // Gira a esquerda
    delay(300);    
    robo.acionarMotores(0,0);
    delay(1000);
    robo.acionarMotores(40,35); // Vai pra frente
    delay(880);
    //robo.acionarMotores(0,0);
    //delay(1000);
    robo.acionarMotores(40,-20); // Gira para esquerda
    delay(500);
    robo.acionarMotores(40,50); 
    delay(85);
    robo.acionarMotores(-10,30);
    delay(350);
    robo.acionarMotores(0,0);
    delay(3000); 
}
