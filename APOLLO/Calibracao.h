#ifndef CALIBRACAO_H
#define CALIBRACAO_H
#include <robo_hardware2.h>

class Calibracao{
  
  public:

  Calibracao();
  void menuSc();
  void menuCalibrando();
   dadosCal();

  protected:

    int mEsq;
    int mDir;
    int mMEsq;
    int mMDir;
   float cor_dir,cor_esq;

};
#endif
