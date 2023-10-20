int number = 16;
int ledPin[] = {13, 12, 11, 10, 9, 8, 7, 6};
int len = sizeof ledPin / sizeof(int);
String mystr;
String str;

void convertDecToBin();

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < len; i++) {
    pinMode(ledPin[i], OUTPUT);
  }  
}

void loop() {
  // put your main code here, to run repeatedly:
  char myRes[len];
  convertDecToBin(myRes);
  for (int i = 0; i < len; i++) {
    if (myRes[i] == '0') {
      digitalWrite(ledPin[i], LOW);
    }
    else if (myRes[i] == '1') {
      digitalWrite(ledPin[i], HIGH);
    }
  }
}

void convertDecToBin(char result[]) {
  int s;
  int pos;
  
  while(number > 0) {
    s = number % 2;
    str = String(s);
    number = number / 2;
    mystr = mystr + str; 
  }

  pos = len - mystr.length();
  for (int i = 0; i < len; i++) {
    if (i < pos) {
      result[i] = '0';
    } else if (i >= pos){
      result[i] = mystr[len - i - 1];
    }
  }
}
