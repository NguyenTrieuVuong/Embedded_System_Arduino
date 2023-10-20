#define DS18B20_PIN 2

void  SetMode(unsigned char mode){//set tín hiệu I/O cho pin
  if (mode==0){
    pinMode(DS18B20_PIN, OUTPUT);
    digitalWrite(DS18B20_PIN,LOW);		// Chu y cai lenh nay
  }
  else
    pinMode(DS18B20_PIN, INPUT);
}
unsigned char DS18B20_Reset()     //khởi tạo cảm biến 
{
  unsigned char result;
  SetMode(0);
  
  delayMicroseconds(480);
  SetMode(1);//release bus
  delayMicroseconds(70);  //550-480
  result = digitalRead(DS18B20_PIN);// Read Presence pulse
  delayMicroseconds(410); //960-550

  return result;
}

void DS18B20_Write1()//viết bit 1
{
  SetMode(0);
  delayMicroseconds(6);
  SetMode(1);//release bus
  delayMicroseconds(64);//54+10
}

void DS18B20_Write0()// viết bit 0
{
  SetMode(0);  
  delayMicroseconds(60);
  SetMode(1);//release bus
  delayMicroseconds(10);  
}

void DS18B20_Write_Bit(unsigned char b)//viết bit
{
  if(b == 1)
  {
    DS18B20_Write1();
  }
  else
  {
    DS18B20_Write0();
  }
}

unsigned char DS18B20_Read_Bit()//đọc bit
{
  unsigned char result;
  SetMode(0);  
  delayMicroseconds(6);
  SetMode(1);
  delayMicroseconds(4);// Chú ý cái lệnh này, So cái này với giản đồ xung!
  result = digitalRead(DS18B20_PIN);
  delayMicroseconds(60);
  return result;
}
unsigned int DS18B20_Read_Byte(void) { //đọc 1 byte
   unsigned char result=0;
   unsigned char i;
   for(i=0;i<8;i++){                        //cho vòng lặp chạy 8 lần
    result>>=1;                             //dịch result sang phải 1
    result=result | DS18B20_Read_Bit()<< 7; //lưu bit đọc được vào bit cuối cùng của result
    }
   return result;
}


void DS18B20_Write_Byte(unsigned char b)//viết 1 byte
{
  unsigned char i ;

  for(i=0;i<8;i++)               //cho vòng lặp chạy 8 lần
  {
    DS18B20_Write_Bit(b & 0x01);//lấy ra bit thấp nhất của bite b và gửi đi 
    b >>= 1;                    //dịch bit tiếp theo xuống thành bit thấp nhất 
  }
}
void setup(){
  Serial.begin(9600);
  DS18B20_Reset();
  delay(1000);

}
void loop(){
  unsigned char j;
  unsigned char lsB, msB;
  float t;

  DS18B20_Reset();
  DS18B20_Write_Byte(0xCC);             //skip ROM
  DS18B20_Write_Byte(0x44);        	//convert_T
  delay(1000);
  DS18B20_Reset();
  DS18B20_Write_Byte(0xCC);             //skip ROM
  DS18B20_Write_Byte(0xBE);         	//read Scratchpad

  lsB=DS18B20_Read_Byte();              // đọc LSByte cua nhiet đô
  msB=DS18B20_Read_Byte();              // đọc MSByte của nhiệt độ

  t= ((float)(lsB&0x0F))/16;          //byte thứ nhất lấy 4 bit đầu (phần thập phân)
  t=((lsB&0xF0)>>4|(msB&0x0F)<<4)+t;  //(Lấy 4 bit cao cua msByte) + (Lấy 4 bit thấp của lsByte) + phần thập phân ở trên

  Serial.println(" ");
  Serial.println("Nhiet do: ");
  Serial.println(t,4);                //in ra giá trị nhiệt độ, 4 vị trí cho giá trị thập phân

}