void setup() {
  // put your setup code here, to run once:
  int i;
  for(i = 6;i<=13;i++){
    pinMode(i,OUTPUT);
  }
  
}

void loop() {
   //put your main code here, to run repeatedly:
//  int m;
//  for(m=0;m<=255;m++){
//    int i;
//    int j;
//    int n[7];
//    int b = 2;
//    for(i = 7;i>=0;i--){
//    n[i]=m%b;
//    m = m/b;
//  }
//  for(i=0,j=13;i<=7,j>=6;i++,j--){
//    if(n[i] == 1){
//      digitalWrite(j,HIGH);
//    }
//    if(n[i] == 0){
//      digitalWrite(j,LOW);
//    }
//  }
//       delay(200);
//  }
  
    //for(int m=0;m<=255;m++){
      setModeBin(16);
      delay(200);
   //}
}

void setModeBin(int m){
    int i;
    int j;
    int b=2;
    int n[7];
    for(i = 7;i>=0;i--){
      n[i]=m%b;
      m = m/b;
    }
      for(i=0,j=13;i<=7,j>=6;i++,j--){
    if(n[i] == 1){
      digitalWrite(j,HIGH);
    }
    if(n[i] == 0){
      digitalWrite(j,LOW);
    }
  }
  }
