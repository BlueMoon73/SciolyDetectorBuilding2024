int redLED = 6;
int greenLED = 5; 
int blueLED = 3;
int ORPpin = 7; 
int ORPReading;   
int ORPSVoltage; 
float lowRange = 1500; 
float highRange = 4500; 
float ORPVoltage; 
float ORPSalinity; 
float lowThreshold = 50; 
float highThreshold = 5000; 
// setup function that runs once at the start of the code
void setup() { 
  
  // initialize the digital pin as an output.
    Serial.begin(9600); 

  // declare LED pins as output
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT); 
  pinMode(blueLED, OUTPUT);
}

// loop function that runs repeatedly
void loop() {

//   gets the ORP reading (0-1023)
  ORPReading = analogRead(A0); 
  Serial.println("=====================");   
  Serial.print("Raw Reading:: ") ;
  Serial.println(ORPReading);   
  
//converting the ORP reading into millivolts  and printing to serial console 
  ORPSVoltage = map(ORPReading, 0, 1023, 0, 5000);
  ORPVoltage = ORPSVoltage / 1000.000; 
  Serial.print("Voltage reading in ");
  Serial.println(ORPVoltage, 4);  
  Serial.print("Predicted Salinity:"); 
  ORPSalinity = predictSalinity(ORPVoltage);
  if (ORPSalinity > 5000) { 
    ORPSalinity = 4900;
  }
  Serial.println(ORPSalinity); 

  
//  conditionals for determining LEDS to turn on.  
  if (ORPSalinity < lowThreshold || ORPSalinity > highThreshold){
    turnOffAll();
  }
 else if (ORPSalinity < lowRange){
    Serial.print("In low range ");
   turnOffAll();
  digitalWrite(redLED, HIGH) ;
  }
  else if (ORPSalinity < highRange){
    Serial.print("In mid range ");
  turnOffAll();
  digitalWrite(greenLED, HIGH);
  }
  else {
    Serial.print("In high range in ");
    turnOffAll();
    digitalWrite(blueLED, HIGH); 
  }

    delay(10000);

}

//function to turn off LED
void turnOffAll () { 
  digitalWrite(redLED, LOW);  
  digitalWrite(greenLED, LOW); 
  digitalWrite(blueLED, LOW); 
}

// return predicted salinity based on voltage 
float predictSalinity(float voltage) {

  // formulas to convert voltage into grams, depending on the range of the voltage 
if (voltage < 0.01) { return 35;} 

else if (voltage < 1.4) {  return pow(10, (0.29904306*voltage + 1.61632775)); }

else if (voltage < 3.3) {return pow(10, (0.23089355*voltage + 1.61717848)); }

else if (voltage < 4.2) {return pow(10, (0.33579583*voltage + 1.28475486)) ; }

else if (voltage < 4.5) {return pow(10, (0.712250 * voltage - 0.36356125)) +70; } 

else {return pow(10, (1.50489089*voltage -3.90820165));}

}
