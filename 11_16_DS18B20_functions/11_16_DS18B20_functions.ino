void  SetMode(unsigned char mode){//set tín hiệu I/O cho pin
  if (mode==0){
    pinMode(DS18B20_PIN, OUTPUT);	//Master control bus
    digitalWrite(DS18B20_PIN,LOW);	//Making falling-edge
    }
  else
    pinMode(DS18B20_PIN, INPUT);	//Release bus so Slave can control bus.
}
unsigned char DS18B20_Reset()     //khởi tạo cảm biến 
{
  unsigned char result;
  SetMode(0);
  delayMicroseconds(480);
  SetMode(1);
  delayMicroseconds(70);  //550-480
  result = digitalRead(DS18B20_PIN);
  delayMicroseconds(410); //960-550

  return result;
}

void DS18B20_Write1()//viết bit 1
{
  SetMode(0);
  delayMicroseconds(6);
  SetMode(1);
  delayMicroseconds(64);//54+10
}

void DS18B20_Write0()// viết bit 0
{
  SetMode(0);
  delayMicroseconds(60);

  SetMode(1);
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
  delayMicroseconds(4);
  result = digitalRead(DS18B20_PIN);
  delayMicroseconds(60);

  return result;
}
unsigned int DS18B20_Read_Byte(void) { //đọc 1 byte
   unsigned char result=0;
   unsigned char i;
   for(i=0;i<8;i++){                        //vòng lặp chạy 8 lần để đọc đủ 8 bit
    result>>=1;                             //dữ liệu chứa trong result được dịch sang bên phải 1 bit sau mỗi lần đọc, do bit đọc lần sau có trọng số lớn hơn.
    result=result | (DS18B20_Read_Bit()<<7); //Đọc dữ liệu từ bus, dịch sang trái 7 bit(đẩy thành MSB) và kết hợp với dữ liệu đã đọc lần trước của result
    //Note: Sau mỗi lần đọc thì MSB phải dịch sang phải 1 bit vì những bit đọc được
    // ở những lần tiếp theo có trong số lớn hơn thì bit đọc trước phải dịch sang phải 1 bit
    }
   return result;
}

void DS18B20_Write_Byte(unsigned char b)//viết 1 byte
{
  unsigned char i ;

  for(i=0;i<8;i++)               //cho vòng lặp chạy 8 lần
  {
    DS18B20_Write_Bit(b & 0x01);//lấy ra bit thấp nhất của byte b và gửi đi. Do 1-Wire truyền LSB đi trước
    b >>= 1;                    //dịch bit tiếp theo sang phải để thành bit thấp nhất 
  }
}