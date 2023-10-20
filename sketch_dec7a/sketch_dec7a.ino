volatile int trangthai = LOW;
volatile int count = 0;

void setup()
{
  Serial.begin(9600);
  digitalWrite(2, HIGH);    // Treo chân ngắt 0, chân số 2 lên mức cao.
  attachInterrupt(0, dem, CHANGE); // khai báo ngắt 0, chương trình con daoled, chế độ có sự
  //  thay đổi là sinh ngắt
}
void loop()                           // đoạn chương trình chính, vòng lặp vô tận.
{
  //Serial.println(count);
}
void dem()                       // chương trình con ngắt, khi có ngắt xảy ra sẽ thực hiện chương trình này.
{
  count++; 
  Serial.println(count);
}
ISR ( TIME1_OVF_vect)
    {
      TCNT1=3036;
      Serial.print("f= ");
      Serial.print(count);
      Serial.print("\n");
      count=0;
    }
