#include "Estrategia.h"
#include "Calibracao.h"
//Estrategia::Estrategia(){

//}

void Estrategia::seguirLinha() {
    if(sensores.bbbb()){            //BBBB    
        motores.seguirFrente(); 
         
    }else if(sensores.pbbb()){       //PBBB
        motores.virarEsq();   
        
    }else if(sensores.bpbb()){       //BPBB
        motores.virarEsq();  
        
    }else if(sensores.bbpb()){       //BBPB            
        motores.virarDir();
          
    }else if(sensores.bbbp()){       //BBBP
        motores.virarDir(); 
         
    }else if(sensores.bppb()){       //BPPB
        motores.seguirFrente();
            
    }else if(sensores.bbpp()){       //BBPP
        while(sensores.PretoMaisEsquerdo()){
            motores.seguirFrente();   
        }
        while(sensores.BrancoEsquerdo()){
            motores.virarDir(); 
        } 
        while(sensores.PretoEsquerdo()){
            motores.virarEsq(); 
        }
        
    }else if(sensores.bppp()){       //BPPP
        while(sensores.PretoMaisDireito()){
            motores.seguirFrente();   
        }
        while(sensores.BrancoEsquerdo()){     
            motores.virarDir(); 
        }
        while(sensores.PretoEsquerdo()){
            motores.virarEsq(); 
        }
          
    }else if(sensores.pppb()){        //PPPB
        while(sensores.PretoMaisEsquerdo()){
            motores.seguirFrente();   
        }
        while(sensores.BrancoDireito()){
            motores.virarEsq(); 
        }
        while(sensores.PretoDireito()){
            motores.virarDir(); 
        }
        
    }else if(sensores.ppbb()){        //PPBB
        while(sensores.PretoMaisEsquerdo()){
            motores.seguirFrente();   
        }
        while(sensores.BrancoDireito()){
            motores.virarEsq(); 
        }  
        while(sensores.PretoDireito()){
            motores.virarDir(); 
        }
         
    }else if(sensores.pppp()){         //PPPP
        motores.seguirFrente();   
    }
}


void Estrategia::desviarObs(){         ////pa
    motores.parar();            //inconclusive
    delay(500);

    for(int i = 0; i < 3; i++){  
      robo.ligarTodosLeds();
      delay(350);
      robo.desligarTodosLeds();
      delay(200);
    }
    
    motores.re();               //inconclusive
    delay(50);
    
    while(sensores.BrancoMaisEsquerdo()){
        motores.virarDirU(); 
    }
    
    motores.parar();
    delay(500);
          
    while(sensores.BrancoMaisDireito()){
        motores.virarDirU(); 
    }
    
    motores.parar();
    delay(500);      
    motores.seguirFrente();
    delay(900);
    motores.parar();
    delay(500);
          
    motores.virarEsq();
    delay(400);
    motores.parar();  
    delay(500);
          
    motores.seguirFrente();
    delay(1300);
    motores.parar();
    delay(500);
          
    motores.virarEsq();
    delay(400);
    motores.parar();
    delay(500);
          
    while(sensores.BrancoEsquerdo() && sensores.BrancoDireito()){
        robo.acionarMotores(30,30);  
    }        
   
    motores.parar();  
    delay(500);
    robo.acionarMotores(30,30); 
    delay(100); 
    motores.parar();  
    delay(500);

    while(sensores.BrancoDireito()){
        motores.virarDir();    
    }
    while(sensores.PretoDireito()){
        motores.virarDir();    
    }       
}

void Estrategia::Rampa(){
    if(sensores.bbbb()){           //BBBB    
        robo.acionarMotores(60,60);  
    }
    else if(sensores.pbbb()){       //PBBB
        robo.acionarMotores(50,60);      
    }
    else if(sensores.bpbb()){       //BPBB
        robo.acionarMotores(50,60); 
    }
    else if(sensores.bbpb()){       //BBPB
        robo.acionarMotores(60,50);
    }
    else if(sensores.bbbp()){       //BBBP
        robo.acionarMotores(60,50); 
    }
    else if(sensores.pppp()){          //PPPP 
        while (sensores.idRampa()){
            robo.acionarMotores(60,60);
        }
     
       //----------------------------------- CÓDIGO PARA A SALA 3 -----------------------------------------
     /*   resgate.entrarNaSala(); 
       resgate.alinhar();
       resgate.zona = resgate.indentificaZona();
       resgate.seguirNaSala();                
       */
    
    
    
    }
}

 
void Estrategia::calibracao(){
    Serial.println(F("Pressione o Botão para fazer a Calibração!"));
    Serial.println();
    for (int i = 1; i <= 10; i++){
        robo.ligarLed(3);

        // para calibrar a refletância
        if(robo.botao1Pressionado()){
            robo.desligarLed(3);
            robo.ligarLed(2);
            cali.menuCalibrando();
            robo.desligarTodosLeds(); 
        }
      
        // para calibrar a cor
       /*  if(robo.botao2Pressionado()){
            robo.desligarLed(3);
            robo.ligarLed(1);
            cali.menuCor();
            robo.desligarTodosLeds(); 
        }
*/
        // testar movimentos do robô
      /*   if (robo.botao3Pressionado()){
            robo.ligarTodosLeds(); 
            robo.acionarMotores(0,0); 
            robo.desligarTodosLeds(); 
        }
        */
        Serial.println(F("Tentando:"));
        Serial.println(i);
        delay(500); 
    }
    robo.ligarTodosLeds();
    sensores.dadosCal();
    Serial.println(F("Calibrado!"));
}


void Estrategia::fazerVerde(){
}

void Estrategia::exec(){
    if(sensores.detObs()){
        desviarObs();
    }
    else if (sensores.idRampa()){ 
        robo.ligarLed(1);
        Rampa();  
    }
    else{
        robo.desligarTodosLeds();
        robo.ligarLed(3);
        seguirLinha();
    }
}
