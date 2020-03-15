#include <Servo.h>
#include <math.h>
#include <SoftwareSerial.h>

//_____________________________________________________________________________________________________________________________________________________________________
                                                             // SERVOMOTEURS
//_____________________________________________________________________________________________________________________________________________________________________

Servo epaule;
Servo coude;
Servo poignet;

float tetaE=50;
float tetaC=50;
double Alpha;//angle intermediaire
float tetaE_micro, tetaC_micro;

const float le=7, lc=6.5; //longueurs en cm
float h = 0; //longueur intermédiaire
float x, y; //coordonnées du stylo
const float pi = M_PI; //Store pi in a less annoying format

int x2=-5; //position x initiale de la première lettre écrite
int y2=8 ;// position y initiale de la première lettre écrite
//_______________________________________________________________________________________________________________________________________________________________________
                                                               // MODULE BLUETOOTH
//_______________________________________________________________________________________________________________________________________________________________________
const int RX=3;
const int TX=11;
char Data; //variable qui stocke la lettre reçue
SoftwareSerial BlueT(RX,TX);

//_______________________________________________________________________________________________________________________________________________________________________
void setup() {
  epaule.attach(9,0,180);
  coude.attach(10,0,180);
  poignet.attach(8,0,180);
  Serial.begin(9600);
  Serial.println("Bonjour -Pret pour les commandes AT"); 
  BlueT.begin(9600); 
  delay(500);
}


//_____________________________________________________________________________________________________________________________________________________________________
                                                            //Fonctions du bras
//_____________________________________________________________________________________________________________________________________________________________________
void ligneV(int x1, int y1){ //permet de tracer une ligne verticale à partir du point (x1,y1)
  goTo(x1,y1);
  delay(500);
  setDown();
  delay(500);   
  for(int i=0; i<100; i++){
    x=(0.03*i)+x1; //le trait fera 3 carreaux 
    y=y1;
  
    h=sqrt(sq(x)+sq(y));
    Alpha=(acos( (sq(h) + sq(le) - sq(lc)) / (2*le*h) )) * (180/pi);
    tetaC= (pi - (acos ( (sq(le) + sq(lc) - sq(h)) / (2*le*lc) ))) *(180/pi);
    tetaE= acos( x / h) * (180/pi) - Alpha;

    tetaE_micro= 9.2339*tetaE+1100.3;
    tetaC_micro= -10.023*tetaC+2155.8;
    epaule.writeMicroseconds(tetaE_micro);
    coude.writeMicroseconds(tetaC_micro);

    delay(10);
    
 }
}


 void ligneH(int x1, int y1){ //permet de tracer une ligne horizontale à partir du point (x1, y1);
  goTo(x1,y1); 
  delay(500);
  setDown();
  delay(500);
  for(int i=0; i<100; i++){
    x=x1;
    y=0.02*i + y1; //le trait fera 2 carreaux

    h=sqrt(sq(x)+sq(y));
    Alpha=(acos( (sq(h) + sq(le) - sq(lc)) / (2*le*h) )) * (180/pi);
    tetaC= (pi - (acos ( (sq(le) + sq(lc) - sq(h)) / (2*le*lc) ))) *(180/pi);
    tetaE= acos( x / h) * (180/pi) - Alpha;

    tetaE_micro= 9.2339*tetaE+1100.3;
    tetaC_micro= -10.023*tetaC+2155.8;
    epaule.writeMicroseconds(tetaE_micro);
    coude.writeMicroseconds(tetaC_micro);
   delay(10);
  
 }
 }

 void ligneObliqueAS(int x1, int y1){ //permet de tracer un anti-slash
  for(int i=0; i<100; i++){
    x=0.03*i + x1;
    y=0.02*i + y1;
    

    h=sqrt(sq(x)+sq(y));
    Alpha=(acos( (sq(h) + sq(le) - sq(lc)) / (2*le*h) )) * (180/pi);
    tetaC= (pi - (acos ( (sq(le) + sq(lc) - sq(h)) / (2*le*lc) ))) *(180/pi);
    tetaE= acos( x / h) * (180/pi) - Alpha;

    tetaE_micro= 9.2339*tetaE+1100.3;
    tetaC_micro= -10.023*tetaC+2155.8;
    epaule.writeMicroseconds(tetaE_micro);
    coude.writeMicroseconds(tetaC_micro);
   delay(10);
 }
 }

  void ligneObliqueS(int x1, int y1){ //permet de tracer un slash (mais dans la pratique le trait n'est pas droit))
  for(int i=0; i<100; i++){
    x=-0.02*i + x1;
    y=0.02*i + y1;
    //permet de tracer un trait horizontal de la position (5,7) à (5,14)

    h=sqrt(sq(x)+sq(y));
    Alpha=(acos( (sq(h) + sq(le) - sq(lc)) / (2*le*h) )) * (180/pi);
    tetaC= (pi - (acos ( (sq(le) + sq(lc) - sq(h)) / (2*le*lc) ))) *(180/pi);
    tetaE= acos( x / h) * (180/pi) - Alpha;

    tetaE_micro= 9.2339*tetaE+1100.3;
    tetaC_micro= -10.023*tetaC+2155.8;
    epaule.writeMicroseconds(tetaE_micro);
    coude.writeMicroseconds(tetaC_micro);
   delay(10);
 }
 }

 void goTo(int x1,int y1){ //le stylo se rend au point (x1, y1);
   x=x1;
   y=y1;
   h=sqrt(sq(x)+sq(y));
   Alpha=(acos( (sq(h) + sq(le) - sq(lc)) / (2*le*h) )) * (180/pi);
   tetaC= (pi - (acos ( (sq(le) + sq(lc) - sq(h)) / (2*le*lc) ))) *(180/pi);
   tetaE= acos( x / h) * (180/pi) - Alpha;

   tetaE_micro= 9.2339*tetaE+1100.3;
   tetaC_micro= -10.023*tetaC+2155.8;
   epaule.writeMicroseconds(tetaE_micro);
   coude.writeMicroseconds(tetaC_micro);
   delay(10);
  
 }

 void raiseP(){ //permet de lever le stylo
  poignet.writeMicroseconds(1500);
  delay(500);  
 }

 void setDown(){//permet d'abaisser le stylo
  poignet.writeMicroseconds(1700);
  delay(500);
 }

 
//______________________________________________________________________________________________________________________________________________________________________
                                                                //Alphabet
//______________________________________________________________________________________________________________________________________________________________________                                                               
void L(int x, int y){
  ligneV(x,y);
  delay(500);
  ligneH(x+3,y);
  delay(500);
  raiseP();
  delay(100);
}
void I(int x, int y){
  ligneV(x,y);
  delay(500);
  raiseP();
  delay(100);
  }

void f(int x, int y){
  goTo(x,y+2);
  delay(500);
  setDown();
  delay(500);
  ligneV(x,y);
  delay(500);
  ligneH(x+1,y);
  delay(500);
  raiseP();
  delay(100);
}
void e(int x, int y){
  goTo(x,y+2);
  delay(500);
  setDown();
  delay(500);
  goTo(x,y);
  delay(500);
  ligneV(x,y);
  delay(500);
  ligneH(x+3,y);
  delay(500);
  raiseP();
  delay(500);
  ligneH(x+1,y);
  delay(500);
  raiseP();
  delay(100);
 }

void H(int x,int y){
  ligneV(x,y);
  delay(500);
  raiseP();
  delay(500);
  ligneV(x,y+2);
  delay(500);
  raiseP();
  delay(500);
  ligneH(x+1,y);
  delay(500);
  raiseP();
  delay(100);
}

void C(int x,int y){
  goTo(x,y+2);
  delay(500);
  setDown();
  delay(500);
  goTo(x,y);
  delay(500);
  ligneV(x,y);
  delay(500);
  ligneH(x+3,y);
  delay(500);
  raiseP();
  delay(100); 
}

void U(int x,int y){
  ligneV(x,y);
  delay(500);
  ligneH(x+3,y);
  delay(500);
  goTo(x,y+2);
  delay(500);
  raiseP();
  delay(100);
}

void A(int x,int y){
  goTo(x+3,y);
  delay(500);
  setDown();
  goTo(x,y+1);
  delay(500);
  goTo(x+3,y+2);
  delay(500);
  raiseP();
  delay(500);
  ligneH(x+1,y);
  delay(500);
  raiseP();
  delay(100); 
}
void V(int x, int y){
  goTo(x,y);
  delay(500);
  setDown();
  delay(500);
  goTo(x+3,y+1);
  delay(500);
  goTo(x,y+2);
  delay(500);
  raiseP();
  delay(1000);
}

void N(int x, int y){
  ligneV(x,y);
  delay(500);
  ligneObliqueAS(x,y);
  delay(500);
  goTo(x,y+2);
  delay(500);
  raiseP();
  delay(100);
}
void M(int x, int y){
  ligneV(x,y);
  delay(500);
  ligneObliqueAS(x,y);
  delay(500);
  goTo(x,y+3);
  delay(500);
  ligneV(x,y+3);
  delay(500);
  raiseP();
  delay(100);
}

void X(int x, int y){
  goTo(x,y);
  delay(500);
  setDown();
  ligneObliqueAS(x,y);
  delay(500);
  raiseP();
  goTo(x+1,y+2);
  delay(500);
  setDown();
  delay(500);
  goTo(x+2,y);
  delay(500);
  raiseP();
  delay(500);
}

void T(int x, int y){
  ligneH(x,y);
  delay(500);
  raiseP();
  delay(500);
  ligneV(x,y+1);
  delay(500);
  raiseP();
  delay(500);
}

void loop() {
  raiseP();
  while (BlueT.available()) {//tant que des données sont dispo sur le module Bluetooth 
    Data=BlueT.read(); //on stocke le caractère lu  
    Serial.print(Data);// on affiche le caractère
    }
  while (Serial.available()) { //tant que des données sont dispo sur le moniteur série
    BlueT.write(char(Serial.read())); //on les envoie au module
    } 
  if (Data=='v'){
   V(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
  }
  if (Data=='e'){
   e(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
  }
  if (Data=='n'){
   N(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
  }
  if (Data=='m'){
   M(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
  }
  if (Data=='i'){
   I(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
  }
  if (Data=='f'){
   f(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
  }
  if (Data=='u'){
   U(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
  }
  if (Data=='l'){
   L(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
  }
  if (Data=='h'){
   H(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
  }
  if (Data=='c'){
   C(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
  }
  if (Data=='a'){
   A(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
  }
  if (Data=='x'){
   X(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
  }  
  if (Data=='t'){
   T(x2,y2);
   delay(1000);
   x2+=4;
   y2-=1;
    
  }
   
  
 }
