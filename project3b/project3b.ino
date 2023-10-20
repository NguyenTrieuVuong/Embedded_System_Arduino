#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


// hardware settings
const byte pinBacklight=9;
const byte potDigital=2;
const byte pin=A2;
Adafruit_PCD8544 display = Adafruit_PCD8544(2, 3, 4, 5, 6);

void setBacklight(byte intensity) {
  analogWrite(pinBacklight,intensity);
}  

void setup()   {
  display.begin();
  display.setContrast(50);
  setBacklight(80);
  pinMode(pinBacklight,OUTPUT);
  pinMode(potDigital,OUTPUT);
  digitalWrite(potDigital,HIGH);
  randomSeed(analogRead(pin));
  gameOver();
}

// game descriptors: ball position and direction, racket position and width, points, lives
int X=0;
int Y=0;
float aX=1;
float aY=1;
int rY=0;
int rL=15;
long point=0;
int life=3;
int velocity=4;

// game auxiliary variables
int nextHundred=100;
float Xf=0;
float Yf=0;
int oldX=-1;
int oldY=-1;
int oldrY=-1;
int oldrL=-1;
float oldaX=aX;
float oldaY=aY;

void positionBallXY() {  
// erase the ball from the previous position and draw in the current one
  if (oldX>=0)   display.drawRect(oldX,oldY,3,3,WHITE);
  display.drawRect(X,Y,3,3,BLACK);
  oldX=X;
  oldY=Y;
}  

void positionRacketYL() {  
// erase the racket from the previous position and draw in the current one
  if (oldrY>=0)   display.drawRect(78,oldrY,2,oldrL,WHITE);  
  display.drawRect(78,rY,2,rL,BLACK);
  oldrY=rY;
  oldrL=rL;
}  

void updateScoreboards() {  
// informs on the screen the number of lives and the points
  display.fillRect(0,40,70,8,WHITE);
  display.setCursor(20,40);
  display.print(point);
  display.setCursor(5,40);
  display.print(life);
}  

void gameOver() {  
// screen that waits for the start of a new game, and initializes it
  display.clearDisplay();
  display.setTextSize(2);  
  display.setCursor(10,0);
  display.print("PONG");
  display.setCursor(30,17);
  display.print("GAME");
  display.setTextSize(0.5);
  display.setCursor(1,32);
  display.print("Rotate & play");  
  life=0;
  updateScoreboards();  
  display.display();
  int a=analogRead(pin);
  while(abs(a-analogRead(pin))<=100) {
    delay(50);
  }  
  point=0;
  life=3;
  velocity=4;
  X=0;
  Y=0;
  aX=1;
  aY=1;
  rY=0;
  rL=15;  
  display.clearDisplay();
  updateScoreboards();
}  

void blinkScreen() {
  for (int p=0; p<=6; p++) {
    setBacklight(250);
    delay(140);
    setBacklight(25);
    delay(60);
  }  
}

void detectBeats() {
  oldaX=aX;
  oldaY=aY;
  if (X==0) aX=1;
  if (Y==36) aY=-1;
  if (Y==0) aY=1;  
  if (X==76) {
    // checks if he hit the racket and continues, reduces lives or ends, as the case may be
    if ((Y>=rY-3) & (Y<=rY+rL)) { 
      aX=-0.65+random(0,90)/100;
      point+=10;
      managePhases(); 
      setBacklight(200);    
    } else {
      life--;
      Xf=0;   
      blinkScreen();
      updateScoreboards();  
     if (life<0) {
       gameOver();
     }  
    }  
  }  
}

void moveBounceBall() {
  setBacklight(10+X*0.8);
  Xf=Xf+aX;
  Yf=Yf+aY;
  X=int(Xf);
  Y=int(Yf);
  if ((oldaY!=aY) | (oldaX!=aX)) {
    point++;
    updateScoreboards();   
    managePhases(); 
  }  
}

void moveRacket() {
  int potRead=analogRead(pin);
  if (potRead<448) potRead=448;
  if (potRead>576) potRead=576;  
  rY=map(potRead,448,576,40-rL,0);
}

void managePhases() {
  if (point>nextHundred) {
    if ((nextHundred % 200)==0) life++;
    if (rL>4) rL--;
    if (velocity<8) velocity++;
    nextHundred+=100;
  }  
}

void loop() {
  positionRacketYL();
  positionBallXY();
  delay(10-velocity);
  detectBeats();
  moveBounceBall();
  moveRacket();
  display.display(); 

  
}
