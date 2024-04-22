

const int ldrPin = A1;  
const int sensorPin = A0; 
float sensorValue;
float voltageOut;
const int lightPin = 4;   // Output for light detection

float temperatureC;
float temperatureF;

// uncomment if using LM335
float temperatureK;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(ldrPin, INPUT);  
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
   pinMode(lightPin, OUTPUT);
//  digitalWrite(3,LOW);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  voltageOut = (sensorValue * 5000) / 1024;
  // calculate temperature for LM335  
  temperatureK = voltageOut / 10;   
  temperatureC = temperatureK - 273; 
  temperatureF = (temperatureC * 1.8) + 32;
  
  Serial.print(" "); 
  Serial.print(temperatureC);  

  if (temperatureC >= 5 ) {
    Serial.print(" WARNING ");
    digitalWrite(2,HIGH);
  } else if (temperatureC <=5) {
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    }

  
  // Check LDR sensor for light
  int lightValue = analogRead(ldrPin);
//  Serial.print("LDR Value: ");
  Serial.print(lightValue);

  if (lightValue > 0) {
    
    digitalWrite(lightPin, HIGH);
    Serial.println(" Closed");// Turn on lightPin if light is detected
  } else{
    digitalWrite(lightPin, LOW); // Turn off lightPin if no light is detected
    Serial.println(" Opened");
  }
  

  delay(1000); 
}
