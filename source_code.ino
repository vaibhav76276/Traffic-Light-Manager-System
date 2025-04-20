#include <Servo.h>

// IR Sensors
#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3

// Traffic LEDs
#define R1 2
#define Y1 3
#define G1 4

#define R2 5
#define Y2 6
#define G2 7

#define R3 8
#define Y3 9
#define G3 10

#define R4 11
#define Y4 12
#define G4 13

// Servo Motors
Servo S1;
Servo S2;
Servo S3;
Servo S4;

int delayTime = 8000; // green light delay in milliseconds

void setup() {
  // Initialize IR Sensors
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);

  // Initialize LEDs
  pinMode(R1, OUTPUT); pinMode(Y1, OUTPUT); pinMode(G1, OUTPUT);
  pinMode(R2, OUTPUT); pinMode(Y2, OUTPUT); pinMode(G2, OUTPUT);
  pinMode(R3, OUTPUT); pinMode(Y3, OUTPUT); pinMode(G3, OUTPUT);
  pinMode(R4, OUTPUT); pinMode(Y4, OUTPUT); pinMode(G4, OUTPUT);

  // Attach servos
  S1.attach(22); // Servo pins (use PWM-capable pins)
  S2.attach(23);
  S3.attach(24);
  S4.attach(25);

  // Start with all red lights and barriers down
  allRed();
  closeAllBarriers();
}

void loop() {
  bool car1 = digitalRead(IR1) == LOW;
  bool car2 = digitalRead(IR2) == LOW;
  bool car3 = digitalRead(IR3) == LOW;
  bool car4 = digitalRead(IR4) == LOW;

  if (car1) manageTraffic(R1, Y1, G1, S1);
  if (car2) manageTraffic(R2, Y2, G2, S2);
  if (car3) manageTraffic(R3, Y3, G3, S3);
  if (car4) manageTraffic(R4, Y4, G4, S4);

  // If no vehicles, stay red
  if (!car1 && !car2 && !car3 && !car4) {
    allRed();
    closeAllBarriers();
  }
}

void manageTraffic(int R, int Y, int G, Servo &barrier) {
  // Turn all signals red and barriers down
  allRed();
  closeAllBarriers();

  digitalWrite(R, LOW);
  digitalWrite(G, HIGH);
  barrier.write(90); // open barrier
  delay(delayTime);

  digitalWrite(G, LOW);
  digitalWrite(Y, HIGH);
  delay(1000);
  digitalWrite(Y, LOW);
  digitalWrite(R, HIGH);
  barrier.write(0); // close barrier
}

void allRed() {
  digitalWrite(R1, HIGH); digitalWrite(Y1, LOW); digitalWrite(G1, LOW);
  digitalWrite(R2, HIGH); digitalWrite(Y2, LOW); digitalWrite(G2, LOW);
  digitalWrite(R3, HIGH); digitalWrite(Y3, LOW); digitalWrite(G3, LOW);
  digitalWrite(R4, HIGH); digitalWrite(Y4, LOW); digitalWrite(G4, LOW);
}

void closeAllBarriers() {
  S1.write(0);
  S2.write(0);
  S3.write(0);
  S4.write(0);
}
