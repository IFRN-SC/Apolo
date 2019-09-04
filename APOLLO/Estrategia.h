
#include "Sensores.h"
#include "Motores.h"
#include "Calibracao.h"

class Estrategia{
    private:
        /*Resgate resgate;*/
        Sensores sensores;
        Motores motores;
        Calibracao cali;
        
       
    protected:    
        void fazerVerde();
        void Rampa(); 
        void seguirLinha();
        void desviarObs();
//        Estrategia Estrategia();
    public:
        void calibracao();
        void exec();
};
