
#include <Servo.h>

// twelve servo objects can be created on most boards
Servo myservoLeft;  // create servo object to control a servo
Servo myservoRight;

const int trigPinObject = 5;
const int echoPinObject = 6;
const int trigPinEdge = 10;
const int echoPinEdge = 9;

float durationObject, distanceObject;
float durationEdge, distanceEdge;

int pos = 0;    // variable to store the servo position
int startFlag = 0;
int edgeFlag = 0;
int objectFlag = 0;
int flag = 0;

void setup() {
  myservoLeft.attach(3);  // attaches the servo on pin 9 to the servo object
  myservoRight.attach(11);  // attaches the servo on pin 9 to the servo object

  // Ultrasonic for Object Detection
  pinMode(trigPinObject, OUTPUT);
  pinMode(echoPinObject, INPUT);

  // Ultrasonic for Edge Detection
  pinMode(trigPinEdge, OUTPUT);
  pinMode(echoPinEdge, INPUT);

  // Starts the serial monitor with data rate of 9600 bits per second
  Serial.begin(9600);
}

void loop() {
  distanceEdge = detectEdge();
  distanceObject = detectObject();

  // Starts the Sanibot
  if (distanceObject <= 6) {
    flag = 1;
  }

  // Edge of surface hit
  if (distanceEdge >= 10) {
    flag = 2;
  }

  // Object Detected
  if (distanceObject <= 15 and distanceObject > 10) {
    flag = 3;
  }

  switch (flag) {
    case 1:
      go();
      break;
    case 2:
      edgeDetected();
      flag = 1;
      break;
    case 3:
      objectDetected();
      flag = 1;
      break;
  }

  delay(75);
}

int detectEdge() {
  // Ultrasonic for Edge Detection
  digitalWrite(trigPinEdge, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinEdge, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinEdge, LOW);
  durationEdge = pulseIn(echoPinEdge, HIGH);
  // calculating distance in cm
  distanceEdge = (durationEdge * .0343) / 2; 
  Serial.print("Edge Distance: ");
  Serial.println(distanceEdge);
  return distanceEdge;
}

int detectObject() {
  // Ultrasonic for Object Detection
  digitalWrite(trigPinObject, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinObject, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPinObject, LOW);
  durationObject = pulseIn(echoPinObject, HIGH);
  // calculating distance in cm
  distanceObject = (durationObject * .0343) / 2; 
  Serial.print("Object Distance: ");
  Serial.println(distanceObject);
  return distanceObject;
}

void edgeDetected() {
  reverse(30);
  turnLeft(35);
}

void objectDetected() {
  reverse(50);
  turnLeft(26);
  driveForward(30);
  turnRight(13);
  driveForward(50);
  turnRight(13);
  driveForward(50);
  turnLeft(26);
}

void go() {
  // Left Servo
  int posLeft = 180;
  posLeft -= 1;
  myservoLeft.write(posLeft);
  delay(15);

  // Right Servo
  int posRight = 0;
  posRight += 1;
  myservoRight.write(posRight);
  delay(15);
}

void driveForward(int duration) {
  for (int i = 0; i <= duration; i += 1) {
    // Left Servo
    int posLeft = 180;
    posLeft -= 1;
    myservoLeft.write(posLeft);
    delay(15);

    // Right Servo
    int posRight = 0;
    posRight += 1;
    myservoRight.write(posRight);
    delay(15);
  }
}

void reverse(int duration) {
  // Reverse
  for (int i = 0; i <= duration; i += 1) {
    // Left Servo
    int posLeft = 0;
    posLeft += 1;
    myservoLeft.write(posLeft);
    delay(15);

    // Right Servo
    int posRight = 180;
    posRight -= 1;
    myservoRight.write(posRight);
    delay(15);
  }
}

void turnRight(int distance) {
  for (int i = 0; i <= distance; i += 1) {
    // Left Servo
    int posLeft = 180;
    posLeft -= 1;
    myservoLeft.write(posLeft);
    delay(15);

    // Right Servo
    int posRight = 180;
    posRight -= 1;
    myservoRight.write(posRight);
    delay(15);
  }
}

void turnLeft(int distance) {
  // Turn Left
  for (int i = 0; i <= distance; i += 1) {
    // Left Servo
    int posLeft = 0;
    posLeft += 1;
    myservoLeft.write(posLeft);
    delay(15);

    // Right Servo
    int posRight = 0;
    posRight += 1;
    myservoRight.write(posRight);
    delay(15);
  }
}
