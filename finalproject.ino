// Define color sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Calibration Values
// *Get these from Calibration Sketch
int redMin = 15; // Red minimum value
int redMax = 100; // Red maximum value
int greenMin = 30; // Green minimum value
int greenMax = 160; // Green maximum value
int blueMin = 28; // Blue minimum value
int blueMax = 130; // Blue maximum value

// https://samueladesola.medium.com/how-to-play-the-musical-notes-on-the-arduino-1e9505d00c60
// https://starboardquest.com/sir-isaac-newton-music-notes-and-color
// RED: D note
// GREEN: G note
// BLUE: A note
// YELLOW: F note
// INDIGO: B note
// ORANGE: E note
// VIOLET: C note

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variables for final Color values
int redValue;
int greenValue;
int blueValue;

void setup() {
	// Set S0 - S3 as outputs
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

  pinMode(2, OUTPUT);  // for speaker

	// Set Sensor output as input
	pinMode(sensorOut, INPUT);

	// Set Frequency scaling to 20%
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);

	// Setup Serial Monitor
	Serial.begin(9600);
}

void loop() {
	// Read Red value
	redPW = getRedPW();
	// Map to value from 0-255
	redValue = map(redPW, redMin,redMax,255,0);
	// Delay to stabilize sensor
	delay(1000);

	// Read Green value
	greenPW = getGreenPW();
	// Map to value from 0-255
	greenValue = map(greenPW, greenMin,greenMax,255,0);
	// Delay to stabilize sensor
	delay(1000);

	// Read Blue value
	bluePW = getBluePW();
	// Map to value from 0-255
	blueValue = map(bluePW, blueMin,blueMax,255,0);
	// Delay to stabilize sensor
	delay(1000);

	// Print output to Serial Monitor
	Serial.print("Red = ");
	Serial.print(redValue);
	Serial.print(" - Green = ");
	Serial.print(greenValue);
	Serial.print(" - Blue = ");
	Serial.println(blueValue);

  // Checks the current detected color and prints
  // a message in the serial monitor


  if(redValue > greenValue && redValue > blueValue){ // RED RANGE
    if(redValue > 230 && blueValue > 230 && greenValue > 230) {
      Serial.println("Holding sensor too close. Please move it back and try again.");
    } else if (redValue > greenValue + 30 && redValue - 50 > blueValue) {
        Serial.println(" - ORANGE detected!");
        tone(2, 659, 1000); //E note
        delay(1000);
    } else if (redValue - 50 > blueValue && greenValue - 50 > blueValue){
        Serial.println(" - YELLOW detected!");
        tone(2, 698, 1000); //F note
        delay(1000);
    } else if(blueValue - 50 > greenValue && redValue - 30 > greenValue){
        Serial.println(" - INDIGO detected!");
        tone(2, 494, 1000); //B note
        delay(1000);
    } else if(redValue - 15 > greenValue && blueValue + 15 > greenValue && greenValue + 50 > redValue) {
        Serial.println(" - VIOLET detected!");
        tone(2, 523, 1000); //C note
        delay(1000);
    } else {
        Serial.println(" - RED detected!");
        tone(2, 587, 1000); // D NOTE
        delay(1000);
    }
  }

  if(greenValue > redValue && greenValue > blueValue){ // GREEN RANGE
    if(redValue > 230 && blueValue > 230 && greenValue > 230) {
      Serial.println("Holding sensor too close. Please move it back and try again.");
    } else if(redValue > blueValue+30 && greenValue > blueValue+30){
        Serial.println(" - YELLOW detected!");
        tone(2, 698, 1000); //F note
        delay(1000);
    } else {
        Serial.println(" - GREEN detected!");
        tone(2, 784, 1000); //G note
        delay(1000);
    }
  }

  if(blueValue > redValue && blueValue > greenValue){ // BLUE RANGE
    if(redValue > 230 && blueValue > 230 && greenValue > 230) {
        Serial.println("Holding sensor too close. Please move it back and try again.");
    } else if(redValue > greenValue){
        Serial.println(" - INDIGO detected!");
        tone(2, 494, 1000); //B note
        delay(1000);
    } else if(blueValue > greenValue + 50 && redValue > greenValue + 50){
        Serial.println(" - VIOLET detected!");
        tone(2, 523, 1000); //C note
        delay(1000);
      } else {
        Serial.println(" - BLUE detected!");
        tone(2, 440, 1000); //A note
        delay(1000);
    }
  }

}


// Function to read Red Pulse Widths
int getRedPW() {
	// Set sensor to read Red only
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
	// Set sensor to read Green only
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
	// Set sensor to read Blue only
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}