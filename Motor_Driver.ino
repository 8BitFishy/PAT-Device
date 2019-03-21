int motorPin = 9;               // PWM Output Pin
int DAQPin = 8;                 // DAQ Signal Input Pin

//int DAQSig = 0;                 // DAQ Signal
int motorSpeed = 0;             // PWM Duty Cycle

const int numReadings = 10;     // Number of readings to average

int DAQSig[numReadings];        // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average



void setup() {
pinMode(motorPin, OUTPUT);      // Assign Pin
pinMode(DAQSig, INPUT);         // Assign Pin
Serial.begin(9600);             // Begin Serial Communication

for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    DAQSig[thisReading] = 0;
  }                             // Initialize all the readings to 0

}


void loop() {
  
total = total - DAQSig[readIndex];
DAQSig[readIndex] = analogRead(DAQPin);

total = total + DAQSig[readIndex];

readIndex = readIndex + 1;

if (readIndex >= numReadings){
  readIndex = 0;
  
}

average = total / numReadings;

motorSpeed = map(average, 0, 1023, 0, 254);

if(motorSpeed<20){
analogWrite(motorPin, 0);
}

else{
analogWrite(motorPin, motorSpeed);
}


Serial.print(average);
Serial.print('\t');
Serial.print(motorSpeed);
Serial.print('\n');
}
