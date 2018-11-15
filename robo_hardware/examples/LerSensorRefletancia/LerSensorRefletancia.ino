int estados=0;

void setup()
{ 
  Serial.begin(9600);
  pinMode(2, INPUT);//B1
  pinMode(3, INPUT);//B2
  pinMode(4, INPUT);//B3 Desliga
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);//Motor
  pinMode(9, OUTPUT);//Motor
  pinMode(10, OUTPUT);//Motor
  pinMode(11, OUTPUT);//Motor
}

void loop()
{
  switch(estados)
  {
    case 0:
    Serial.println("ESTOU NO ESTADO 0");
    digitalWrite(11,0);
    digitalWrite(10,0);
    digitalWrite(9,0);
    digitalWrite(8,0);
    digitalWrite(5,0);
    digitalWrite(6,0);
    break;
    case 1:
    Serial.println("ESTOU NO ESTADO 1");
    digitalWrite(8,0);
    digitalWrite(11,1);
    delay(1000);
    digitalWrite(11,0);
    digitalWrite(10,1);
    delay(1000);
    digitalWrite(10,0);
    digitalWrite(9,1);
    delay(1000);
    digitalWrite(9,0);
    digitalWrite(8,1);
    delay(1000);
    digitalWrite(5,0);
    digitalWrite(6,1);
    break;
    case 2:
    Serial.println("ESTOU NO ESTADO 2");
    digitalWrite(8,0);
    digitalWrite(11,1);
    delay(500);
    digitalWrite(11,0);
    digitalWrite(10,1);
    delay(500);
    digitalWrite(10,0);
    digitalWrite(9,1);
    delay(500);
    digitalWrite(9,0);
    digitalWrite(8,1);
    delay(500);
    digitalWrite(5,0);
    digitalWrite(6,1);
    break;
    case 3:
    Serial.println("ESTOU NO ESTADO 3");
    digitalWrite(8,0);
    digitalWrite(11,1);
    delay(250);
    digitalWrite(11,0);
    digitalWrite(10,1);
    delay(250);
    digitalWrite(10,0);
    digitalWrite(9,1);
    delay(250);
    digitalWrite(9,0);
    digitalWrite(8,1);
    delay(250);
    digitalWrite(5,0);
    digitalWrite(6,1);
    break;
    case 4:
    Serial.println("ESTOU NO ESTADO 4");
    digitalWrite(8,0);
    digitalWrite(11,1);
    delay(2);
    digitalWrite(11,0);
    digitalWrite(10,1);
    delay(2);
    digitalWrite(10,0);
    digitalWrite(9,1);
    delay(2);
    digitalWrite(9,0);
    digitalWrite(8,1);
    delay(2);
    digitalWrite(5,1);
    digitalWrite(6,1);
    break;
    case -1:
    Serial.println("ESTOU NO ESTADO -1");
    digitalWrite(11,0);
    digitalWrite(8,1);
    delay(1000);
    digitalWrite(8,0);
    digitalWrite(9,1);
    delay(1000);
    digitalWrite(9,0);
    digitalWrite(10,1);
    delay(1000);
    digitalWrite(10,0);
    digitalWrite(11,1);
    delay(1000);
    digitalWrite(5,1);
    digitalWrite(6,0);
    break;
    case -2:
    Serial.println("ESTOU NO ESTADO -2");
    digitalWrite(11,0);
    digitalWrite(8,1);
    delay(500);
    digitalWrite(8,0);
    digitalWrite(9,1);
    delay(500);
    digitalWrite(9,0);
    digitalWrite(10,1);
    delay(500);
    digitalWrite(10,0);
    digitalWrite(11,1);
    delay(500);
    digitalWrite(5,1);
    digitalWrite(6,0);
    break;
    case -3:
    Serial.println("ESTOU NO ESTADO -3");
    digitalWrite(11,0);
    digitalWrite(8,1);
    delay(250);
    digitalWrite(8,0);
    digitalWrite(9,1);
    delay(250);
    digitalWrite(9,0);
    digitalWrite(10,1);
    delay(250);
    digitalWrite(10,0);
    digitalWrite(11,1);
    delay(250);
    digitalWrite(5,1);
    digitalWrite(6,0);
    break;
    case -4:
    Serial.println("ESTOU NO ESTADO -4");
    digitalWrite(11,0);
    digitalWrite(8,1);
    delay(2);
    digitalWrite(8,0);
    digitalWrite(9,1);
    delay(2);
    digitalWrite(9,0);
    digitalWrite(10,1);
    delay(2);
    digitalWrite(10,0);
    digitalWrite(11,1);
    delay(2);
    digitalWrite(5,1);
    digitalWrite(6,1);
    break;
  }
  if(estados==0&&digitalRead(2)==1){estados=1;delay(500);};
  if(estados==0&&digitalRead(3)==1){estados=-1;delay(500);};
  if(estados==1&&digitalRead(2)==1){estados=2;delay(500);};
  if(estados==1&&digitalRead(3)==1){estados=0;delay(500);};
  if(estados==1&&digitalRead(4)==1){estados=0;delay(500);};
  if(estados==2&&digitalRead(2)==1){estados=3;delay(500);};
  if(estados==2&&digitalRead(3)==1){estados=1;delay(500);};
  if(estados==2&&digitalRead(4)==1){estados=0;delay(500);};
  if(estados==3&&digitalRead(2)==1){estados=4;delay(500);};
  if(estados==3&&digitalRead(3)==1){estados=2;delay(500);};
  if(estados==3&&digitalRead(4)==1){estados=0;delay(500);};
  if(estados==4&&digitalRead(3)==1){estados=3;delay(500);};
  if(estados==4&&digitalRead(4)==1){estados=0;delay(500);};
  if(estados==-1&&digitalRead(3)==1){estados=-2;delay(500);};
  if(estados==-1&&digitalRead(2)==1){estados=0;delay(500);};
  if(estados==-1&&digitalRead(4)==1){estados=0;delay(500);};
  if(estados==-2&&digitalRead(3)==1){estados=-3;delay(500);};
  if(estados==-2&&digitalRead(2)==1){estados=-1;delay(500);};
  if(estados==-2&&digitalRead(4)==1){estados=0;delay(500);};
  if(estados==-3&&digitalRead(3)==1){estados=-4;delay(500);};
  if(estados==-3&&digitalRead(2)==1){estados=-2;delay(500);};
  if(estados==-3&&digitalRead(4)==1){estados=0;delay(500);};
  if(estados==-4&&digitalRead(2)==1){estados=-3;delay(500);};
  if(estados==-4&&digitalRead(4)==1){estados=0;delay(500);};
}

