
#define INTERRUPT_INPUT 2  // Pin assignments

int pulse_counter = 0;


void setup() {
  Serial.begin(9600);
  // For noise suppression, enable pullup on interrupt pin
  digitalWrite(INTERRUPT_INPUT, HIGH);
  attachInterrupt(INTERRUPT_INPUT - 2,
                  interrupt_handler,
                  RISING);
  //khoi dong ngat ngoai 2,
  //chuong trinh phuc vu ngat ngoai interrupt_handler
  //ngat suon len(suon xung tu thap len cao)
}


void loop() {
  if (pulse_counter > 0) {
    Serial.println(pulse_counter);
    delay(100);
    int pulseHigh = pulseIn(INTERRUPT_INPUT, HIGH);
    int pulseLow = pulseIn(INTERRUPT_INPUT, LOW);
    int period = pulseHigh + pulseLow;
    int freq = 1000000 / period;
    int duty = pulseHigh * 1000 / period;
    Serial.print("Freq = ");
    Serial.println(freq);
    Serial.print("Duty cycle = ");
    Serial.println(duty);
    delay(500);
  }
}


void interrupt_handler() {
  pulse_counter = pulse_counter + 1;
}