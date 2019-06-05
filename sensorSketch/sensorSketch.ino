const int sensorPin = 11;    // the number of the pushbutton pin
   // the number of the LED pin

// Variables will change:

int buttonState = LOW;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int lineCount = -1;
int beginTime = 0;
double averageRPM = 0;
double rpm = 0;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 5;    // the debounce time; increase if the output flickers
boolean detection = false;
long previousTime = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(sensorPin, INPUT);
  Serial.println("Started");
  beginTime = micros();
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(sensorPin);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = micros();
  }
  
  if ((micros() - lastDebounceTime) > debounceDelay) {
  
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        lineCount++; 
        /*
        Serial.println("Line count:");
        Serial.println(lineCount);
        Serial.println("averageRPM:");
        averageRPM = lineCount/(millis()/60000);
        Serial.println(averageRPM);
        */
        //Serial.print("1\n");
        if(detection == true){
          rpm = 60000000/(micros()-previousTime);
          Serial.println(rpm);
        }else{
          rpm = 0;
        }
        detection = true;
        previousTime = micros();
      }
    }
  }
  
  lastButtonState = reading;
}
