#include <robo_hardware2.h>
#include "Calibracao.h"

int calPretoEsq,calPretoMaisEsq,calPretoDir,
calPretoMaisDir;
int calBrancoEsq,calBrancoMaisEsq,calBrancoDir,
calBrancoMaisDir;
float verdeDir,verdeEsq,BrancoDir,BrancoEsq;

Calibracao::Calibracao(){
  calibracao_dados hm; 
  robo.lerCalibracao(hm);
  mDir=hm.refletanciaDir;
  mEsq=hm.refletanciaEsq;
  mMDir=hm.refletanciaMaisDir;
  mMEsq=hm.refletanciaMaisEsq;

  /*cor_dir=((hm.verdeDir.s + hm.BrancoDir.s)/2);
  cor_esq=((hm.verdeEsq.s + hm.BrancoEsq.s)/2);
    */
}


void Calibracao::menuSc(){
  
}


void Calibracao::menuCalibrando(){
  char varq= 'h';
  Serial.println("CALIBRANDO BRANCO");
    while(1){
      Serial.print("MaisEsq:");
      Serial.print(robo.lerSensorLinhaMaisEsq());
      Serial.print("Esq:");
      Serial.print(robo.lerSensorLinhaEsq());
      Serial.print("Dir:");
      Serial.print(robo.lerSensorLinhaDir());
      Serial.print("MaisDir:");
      Serial.print(robo.lerSensorLinhaMaisDir());

      Serial.println("");
      Serial.print("Deseja continuar Y ou N ?");

     if(Serial.available()){
       varq=Serial.read();       
       if(varq== 'Y'){
         varq='h';
         calBrancoEsq=robo.lerSensorLinhaEsq();
         calBrancoMaisEsq=robo.lerSensorLinhaMaisEsq();
         calBrancoDir=robo.lerSensorLinhaDir();
         calBrancoMaisDir=robo.lerSensorLinhaMaisDir();
         break;
       }
     }
     delay(500);
    }

   
  Serial.println("CALIBRANDO PRETO");
   while(1){
      Serial.print("MaisEsq:");
      Serial.print(robo.lerSensorLinhaMaisEsq());
      Serial.print("Esq:");
      Serial.print(robo.lerSensorLinhaEsq());
      Serial.print("Dir:");
      Serial.print(robo.lerSensorLinhaDir());
      Serial.print("MaisDir:");
      Serial.print(robo.lerSensorLinhaMaisDir());

      Serial.println("");
      Serial.print("Deseja continuar Y ou N ?");

     if(Serial.available()){
       varq=Serial.read();       
       if(varq== 'Y'){
         varq='h';
         calPretoEsq=robo.lerSensorLinhaEsq();
         calPretoMaisEsq=robo.lerSensorLinhaMaisEsq();
         calPretoDir=robo.lerSensorLinhaDir();
         calPretoMaisDir=robo.lerSensorLinhaMaisDir();
         break;
       }
     }
     delay(500);
    }
    
  mMEsq = (calBrancoMaisEsq + calPretoMaisEsq) / 2;
  mEsq = (calBrancoEsq + calPretoEsq) / 2;
  mDir = (calBrancoDir + calPretoDir) / 2;
  mMDir = (calBrancoMaisDir + calPretoMaisDir) / 2;


  calibracao_dados hm;
  hm.refletanciaDir = mDir; 
  hm.refletanciaEsq = mEsq;
  hm.refletanciaMaisDir = mMDir;
  hm.refletanciaMaisEsq = mMEsq;
  robo.salvarCalibracao(hm);

  Serial.println(" ");

  Serial.print(F("Valores finais: "));
  Serial.print(F("MAIS ESQ : "));
  Serial.print(mMEsq);
  Serial.print(F("  |  ESQ : "));
  Serial.print(mEsq);
  Serial.print(F("  |  DIR : "));
  Serial.print(mDir);
  Serial.print(F("  |  MAIS DIR : "));
  Serial.println(mMDir);

}

  Calibracao::dadosCal(){
    calibracao_dados hm;
    robo.lerCalibracao(hm);
    mDir = hm.refletanciaDir;
    mEsq = hm.refletanciaEsq;
    mMDir  = hm.refletanciaMaisDir;
    mMEsq = hm.refletanciaMaisEsq;

    /*cor_dir = ((hm.verdeDir.a + hm.brancoDir.a)/2);
    cor_esq = ((hm.verdeEsq.a + hm.brancoEsq.a)/2);
    */
  }
  
