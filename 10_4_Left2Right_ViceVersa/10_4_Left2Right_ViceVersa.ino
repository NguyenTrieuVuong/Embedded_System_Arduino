int led[]={13,12,11,10,9,8,7,6};
int len = sizeof led / sizeof(int);
int number =100;
int s;
int i,j;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  int i;
  for(i = 6;i<=13;i++){
    pinMode(i,OUTPUT);
  }
}
//int dec2bin(){
//  while(number>=0){
//    s=number%2;
//    number = number/2;
//  }
//  return s;
//}
//void check(){
//  
//}

// the loop function runs over and over again forever
void loop() {
  for (i=0;i<=7;i++){
    digitalWrite(led[i],HIGH);
    delay(1000);
    digitalWrite(led[i],LOW);
  }
  for (i=7;i>=0;i--){
    digitalWrite(led[i],HIGH);
    delay(1000);
    digitalWrite(led[i],LOW);
  }
  exit(1);
}
