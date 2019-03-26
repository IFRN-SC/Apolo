#include <Arduino.h>
#include <robo_hardware2.h>
#include <main.h>

float delayOneEsq = 0; // Tempo que o robô leva para iniciar o giro
float delayTwoEsq = 0; // Tempo que o robô passa girando
float delayOneDir = 0;
float delayTwoDir = 0;

int pinMaisEsq = 3;
int pinEsq = 2;
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
        if (rampa) {
            rampa = false;      
            robo.desligarLed(1);
        } else {
            rampa = true;
            robo.ligarLed(1);
        }    
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
        if ((robo.lerSensorSonarEsq() < 10) && (robo.lerSensorSonarDir() < 10)) {
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
    int delay90 = 0;
    int delayCurva = 0;
  
    float sensores[4] = {0, 0, 0, 0};
    sensores[0] = (analogRead(pinMaisEsq)/1023.0)*100.0;
    sensores[1] = (analogRead(pinEsq)/1023.0)*100.0;
    sensores[2] = (analogRead(pinDir)/1023.0)*100.0;
    sensores[3] = (analogRead(pinMaisDir)/1023.0)*100.0;
        
     if (sensores[0] > valorCorte[0] && sensores[1] > valorCorte[1] && sensores[2] < valorCorte[2] && sensores[3] < valorCorte[3]) { // PPBB        
        Serial.println(" ====CURVA À ESQUERDA====");
        delay(delayOneEsq);
        robo.acionarMotores(-25,25);
        delay(delayTwoEsq);
    } else if (sensores[0] < valorCorte[0] && sensores[1] < valorCorte[1] && sensores[2] > valorCorte[2] && sensores[3] > valorCorte[3]) { // BBPP        
        Serial.println(" ====CURVA À DIREITA====");
        delay(delayOneDir);
        robo.acionarMotores(25,-25);    
        delay(delayTwoDir);
    }else if(sensores[0]<valorCorte[0] && sensores[1]>valorCorte[1] && sensores[3]<valorCorte[3] && sensores[2]>valorCorte[2]){
      robo.acionarMotores(30,30);

    }else if(sensores[0]>valorCorte[0] && sensores[1]>valorCorte[1] && sensores[3]<valorCorte[3] && sensores[2]<valorCorte[2]){
      robo.acionarMotores(35,-35);
      
    }else if(sensores[0]>valorCorte[0] && sensores[1]<valorCorte[1] && sensores[3]<valorCorte[3] && sensores[2]<valorCorte[2]){
      robo.acionarMotores(35,-35);
      
    }else if(sensores[0]<valorCorte[0] && sensores[1]>valorCorte[1] && sensores[3]<valorCorte[3] && sensores[2]<valorCorte[2]){
      robo.acionarMotores(10,-10);  
      
      
    } else if (sensores[2] < valorCorte[2] && sensores[1] > valorCorte[1]){ // DIR = branco e ESQ = preto        
        // ====CURVA À ESQUERDA===="
        robo.acionarMotores(10,-10); // Curva à esquerda        
    } else if (sensores[2] > valorCorte[2] && sensores[1] < valorCorte[1]){ // DIR = preto e ESQ = branco            
        // ====CURVA À DIREITA====
        robo.acionarMotores(-10,10); // Curva à direita
    } else if (sensores[3] > valorCorte[3] && sensores[0] < valorCorte[0]) { // +DIR = preto e +ESQ = branco        
        // ====CURVA À ESQUERDA====
        robo.acionarMotores(-35,35);        
    } else if (sensores[3] < valorCorte[3] && sensores[0] > valorCorte[0]) { // +DIR = branco e +ESQ = preto                
        Serial.println("====CURVA À DIREITA====");
        robo.acionarMotores(35,-35);                   
    } else if(sensores[0] > valorCorte[0] && sensores[3] > valorCorte[3]) {        
        robo.acionarMotores(33,30);
    } else if (sensores[1] < valorCorte[0] && sensores[2] < valorCorte[2]) {
        robo.acionarMotores(33,30);
    }
}


void initRampa() {        
    int delay90 = 0;
    int delayCurva = 0;
  
    float sensores[4] = {0, 0, 0, 0};
    sensores[0] = (analogRead(0)/1023.0)*100.0;
    sensores[1] = (analogRead(1)/1023.0)*100.0;
    sensores[2] = (analogRead(2)/1023.0)*100.0;
    sensores[3] = (analogRead(3)/1023.0)*100.0;
    
    if (sensores[2] < valorCorte[2] && sensores[1] > valorCorte[1]){ // DIR = branco e ESQ = preto
        robo.acionarMotores(-40,5); // Curva à esquerda
        delay(delayCurva);
    } else if (sensores[2] > valorCorte[2] && sensores[1] < valorCorte[1]){ // DIR = preto e ESQ = branco    
        robo.acionarMotores(5,-40); // Curva à direita
        delay(delayCurva);
    } else if (sensores[3] > valorCorte[3] && sensores[0] < valorCorte[0]) { // +DIR = preto ou +ESQ = branco
        robo.acionarMotores(5,-40);
        delay(delay90);      
    } else if (sensores[3] < valorCorte[3] && sensores[0] > valorCorte[0]) { // +DIR = branco e +ESQ = preto
        robo.acionarMotores(-40,5);
        delay(delay90);    
    } else {
        robo.acionarMotores(60,60);
    }
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

