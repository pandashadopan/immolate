int flowPin = 2;    //This is the input pin on the Arduino
double flowRate;    //This is the value we intend to calculate. 
volatile int count; //This integer needs to be set as volatile to ensure it updates correctly during the interrupt process.  
int volume = 0;

int ledG = 11;
int ledR = 9;
int ledY = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledG, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(flowPin, INPUT);           //Sets the pin as an input
  attachInterrupt(0, Flow, RISING);  //Configures interrupt 0 (pin 2 on the Arduino Uno) to run the function "Flow"  
  Serial.begin(9600);  //Start Serial
}
void loop() {
  // put your main code here, to run repeatedly:  
  count = 0;      // Reset the counter so we start counting from 0 again
  interrupts();   //Enables interrupts on the Arduino
  delay (1000);   //Wait 1 second 
  noInterrupts(); //Disable the interrupts on the Arduino
   
  //Start the math
  flowRate = (count * 2.25);        //Take counted pulses in the last second and multiply by 2.25mL 
  flowRate = flowRate * 60;         //Convert seconds to minutes, giving you mL / Minute
  flowRate = flowRate / 1000;       //Convert mL to Liters, giving you Liters / Minute

  volume += count;
  if(volume < 400) digitalWrite(ledY, HIGH);
  else if (volume < 800) {
    digitalWrite(ledY, LOW);
    digitalWrite(ledG, HIGH);
  }
  else {
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledR, HIGH);
  }
  Serial.println(flowRate);         //Print the variable flowRate to Serial
  Serial.println(volume);
}
 
void Flow()
{
   count++; //Every time this function is called, increment "count" by 1
}
