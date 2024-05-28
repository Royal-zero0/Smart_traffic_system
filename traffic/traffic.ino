#include<TimerOne.h>
int signal1[] = {41, 43, 45};
int signal2[] = {35, 37, 39};
int signal3[] = {29, 31, 33};
int signal4[] = {23, 25, 27};
int incoming[4];
int redDelay = 10000;
int yellowDelay = 5000;
int r1=1;
int r2=1;
int r3=1;
int r4=1;      
long time;                    // Variable for storing the time traveled
volatile int S1, S2, S3, S4;           // Variables for storing the distance covered
int t = 000;  // distance under which it will look for vehicles.
void setup(){
  Serial.begin(115200);
  Serial.setTimeout(1);
  Timer1.initialize(1000000);  //Begin using the timer. This function must be called first. "microseconds" is the period of time the timer takes.
  Timer1.attachInterrupt(softInterr); //Run a function each time the timer period finishes.
  // Declaring LED pins as output
  for(int i=0; i<3; i++){
    pinMode(signal1[i], OUTPUT);
    pinMode(signal2[i], OUTPUT);
    pinMode(signal3[i], OUTPUT);
    pinMode(signal4[i], OUTPUT);
  }
  // Declaring ultrasonic sensor pins as output
 
}
void loop()
{
  // If there are vehicles at signal 1
  if(S1>0)
  {
    signal1Function();
  }
  // If there are vehicles at signal 2
  if(S2>0)
  {
    signal2Function();
  }
  // If there are vehicles at signal 3
  if(S3>0)
  {
    signal3Function();
  }
  // If there are vehicles at signal 4
  if(S4>0)
  {
    signal4Function();
  }
}


void rf()
{ 
  if(r1==0){
  
  digitalWrite(signal1[0], LOW);
  digitalWrite(signal1[1], LOW);
  digitalWrite(signal1[2], HIGH);
  Serial.println("r1: ");
  

  digitalWrite(signal2[0], HIGH);
  digitalWrite(signal2[1], LOW);
  digitalWrite(signal2[2], LOW);


  digitalWrite(signal3[0], HIGH);
  digitalWrite(signal3[1], LOW);
  digitalWrite(signal3[2], LOW);
 
  digitalWrite(signal4[0],HIGH);
  digitalWrite(signal4[1], LOW);
  digitalWrite(signal4[2], LOW);
  
  
}else if(r2==0){
  
  digitalWrite(signal1[0], HIGH);
  digitalWrite(signal1[1], LOW);
  digitalWrite(signal1[2], LOW);
  Serial.println("r2: ");
  

  digitalWrite(signal2[0], LOW);
  digitalWrite(signal2[1], LOW);
  digitalWrite(signal2[2], HIGH);


  digitalWrite(signal3[0], HIGH);
  digitalWrite(signal3[1], LOW);
  digitalWrite(signal3[2], LOW);
 
  digitalWrite(signal4[0],HIGH);
  digitalWrite(signal4[1], LOW);
  digitalWrite(signal4[2], LOW);
}else if(r3==0){
  
  digitalWrite(signal1[0], HIGH);
  digitalWrite(signal1[1], LOW);
  digitalWrite(signal1[2], LOW);
  Serial.println("r3: ");
  

  digitalWrite(signal2[0], HIGH);
  digitalWrite(signal2[1], LOW);
  digitalWrite(signal2[2], LOW);


  digitalWrite(signal3[0], LOW);
  digitalWrite(signal3[1], LOW);
  digitalWrite(signal3[2], HIGH);
 
  digitalWrite(signal4[0],HIGH);
  digitalWrite(signal4[1], LOW);
  digitalWrite(signal4[2], LOW);
  }else if(r4==0){
  
  digitalWrite(signal1[0], HIGH);
  digitalWrite(signal1[1], LOW);
  digitalWrite(signal1[2], LOW);
  Serial.println("r4: ");
  

  digitalWrite(signal2[0], HIGH);
  digitalWrite(signal2[1], LOW);
  digitalWrite(signal2[2], LOW);


  digitalWrite(signal3[0], HIGH);
  digitalWrite(signal3[1], LOW);
  digitalWrite(signal3[2], LOW);
 
  digitalWrite(signal4[0],LOW);
  digitalWrite(signal4[1], LOW);
  digitalWrite(signal4[2], HIGH);
  }
  
}
// This is interrupt function and it will run each time the timer period finishes. The timer period is set at 100 milli seconds.
void softInterr()
{
  
  
  while(Serial.available() >= 4){
    // fill array
    for (int i = 0; i < 4; i++){
      incoming[i] = Serial.read();
    }
  }
  S1= incoming[0];

  S2= incoming[1];

  S3= incoming[2];
 
  S4= incoming[3];
  // Print distance values on serial monitor for debugging
//  Serial.print("S1: ");
//  Serial.print(S1);
//  Serial.print("  S2: ");
//  Serial.print(S2);
//  Serial.print("  S3: ");
//  Serial.print(S3);
//  Serial.print("  S4: ");
//  Serial.println(S4);
}
void signal1Function()
{
  low();
  // Make RED LED LOW and make Green HIGH for 5 seconds
  digitalWrite(signal1[0], LOW);
  digitalWrite(signal1[2], HIGH);
  delay(redDelay);
  // if there are vehicels at other signals
  if(S2>t || S3>t || S4>t)
  {
    // Make Green LED LOW and make yellow LED HIGH for 2 seconds
    digitalWrite(signal1[2], LOW);
    digitalWrite(signal1[1], HIGH);
    delay(yellowDelay);
    Serial.print("1");
  }
  
}
void signal2Function()
{
  
  low();
  digitalWrite(signal2[0], LOW);
  digitalWrite(signal2[2], HIGH);
  delay(redDelay);
  
  if(S1>t || S3>t || S4>t)
  {
    digitalWrite(signal2[2], LOW);
    digitalWrite(signal2[1], HIGH);
    delay(yellowDelay);
    Serial.print("2");   
  }
  
}
void signal3Function()
{
  
  low();
  digitalWrite(signal3[0], LOW);
  digitalWrite(signal3[2], HIGH);
  delay(redDelay);
  if(S1>t || S2>t || S4>t)
  {
    digitalWrite(signal3[2], LOW);
    digitalWrite(signal3[1], HIGH);
    delay(yellowDelay);
    Serial.print("3");
  }
    
}
void signal4Function()
{

  low();
  digitalWrite(signal4[0], LOW);
  digitalWrite(signal4[2], HIGH);
  delay(redDelay);
  if(S1>t || S2>t || S3>t)
  {
    digitalWrite(signal4[2], LOW);
    digitalWrite(signal4[1], HIGH);
    delay(yellowDelay);
    Serial.print("4");
  }
  
}
// Function to make all LED's LOW except RED one's.
void low()
{
  for(int i=1; i<3; i++)
  {
    digitalWrite(signal1[i], LOW);
    digitalWrite(signal2[i], LOW);
    digitalWrite(signal3[i], LOW);
    digitalWrite(signal4[i], LOW);
  }
  for(int i=0; i<1; i++)
  {
    digitalWrite(signal1[i], HIGH);
    digitalWrite(signal2[i], HIGH);
    digitalWrite(signal3[i], HIGH);
    digitalWrite(signal4[i], HIGH);
  }
}
