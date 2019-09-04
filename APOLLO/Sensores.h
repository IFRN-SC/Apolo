#include <Adafruit_TCS34725.h>
#include <cor.h>
#include <Ultrasonic.h>
#include <robo_hardware2.h>
#include <EEPROM2.h>
#include <CorHardware.h>
#include <pinagem.h>


#include <robo_hardware2.h>
#include "Calibracao.h"

class Sensores: public Calibracao{
  
  private:
  
  float valor_sensor_dir;
  float valor_sensor_mais_dir;
  float valor_sensor_esq;
  float valor_sensor_mais_esq;
  
  public:

  // Funcoes para definir o branco
  
  boolean BrancoMaisEsquerdo(){
    return (robo.lerSensorLinhaMaisEsq() > mMEsq);
    }
  boolean BrancoEsquerdo()    {
    return (robo.lerSensorLinhaEsq() > mEsq);
    }
  boolean BrancoDireito()     {
    return (robo.lerSensorLinhaDir() > mDir);
    }
  boolean BrancoMaisDireito() {
    return (robo.lerSensorLinhaMaisDir() > mMDir);
    }


    boolean PretoMaisEsquerdo(){
    return (robo.lerSensorLinhaMaisEsq() < mMEsq);
    }
  boolean PretoEsquerdo()    {
    return (robo.lerSensorLinhaEsq() < mEsq);
    }
  boolean PretoDireito()     {
    return (robo.lerSensorLinhaDir() < mDir);
    }
  boolean PretoMaisDireito() {
    return (robo.lerSensorLinhaMaisDir() < mMDir);
    }

  // Funcoes para condicoes
  
  boolean bbbb(){
   return (BrancoMaisEsquerdo() && BrancoEsquerdo() && BrancoDireito() && BrancoMaisDireito());
   }   //BBBB
  boolean pbbb(){  
   return (!BrancoMaisEsquerdo() && BrancoEsquerdo() && BrancoDireito() && BrancoMaisDireito());
   }  //PBBB
  boolean bpbb(){  
   return (BrancoMaisEsquerdo() && !BrancoEsquerdo() && BrancoDireito() && BrancoMaisDireito());
   }  //BPBB
  boolean bbpb(){  
   return (BrancoMaisEsquerdo() && BrancoEsquerdo() && !BrancoDireito() && BrancoMaisDireito());
   }  //BBPB
  boolean bbbp(){  
   return (BrancoMaisEsquerdo() && BrancoEsquerdo() && BrancoDireito() && !BrancoMaisDireito());
   }  //BBBP
  boolean bppb(){   
   return (BrancoMaisEsquerdo() && !BrancoEsquerdo() && !BrancoDireito() && BrancoMaisDireito());
   } //BPPB
  boolean ppbb(){   
   return (!BrancoMaisEsquerdo() && !BrancoEsquerdo() && BrancoDireito() && BrancoMaisDireito());
   } //PPBB
  boolean bbpp(){   
   return (BrancoMaisEsquerdo() && BrancoEsquerdo() && !BrancoDireito() && !BrancoMaisDireito());
   } //BBPP
  boolean bppp(){   
   return (BrancoMaisEsquerdo() && !BrancoEsquerdo() && !BrancoDireito() && !BrancoMaisDireito());
   } //BPPP
  boolean pppb(){   
   return (!BrancoMaisEsquerdo() && !BrancoEsquerdo() && !BrancoDireito() && BrancoMaisDireito());
   } //PPPB
  boolean pppp(){ 
   return (!BrancoMaisEsquerdo() && !BrancoEsquerdo() && !BrancoDireito() && !BrancoMaisDireito());
   } //PPPP
  
  // Sonares

  bool detObs(){
    return (robo.lerSensorSonarFrontal() <= 5 && robo.lerSensorSonarFrontal() >= 1);
    }
  bool idRampa(){
    return (robo.lerSensorSonarEsq() < 15 ) && (robo.lerSensorSonarDir() < 15);
    }

};
