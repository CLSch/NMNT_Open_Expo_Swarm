 /***************************************************
  * 
  * Code made for New Media, New Technology at Leiden University
  * 
  * Art project: Swarm
  * 
  * This code is made for 6 bots with movable parts, attached with a servo and led.
  * It is a choreography of movements for the bots, made to investigate the realms of behavior 
  * in artificial entities.
  * 
  * For our setup:
  * Bot 0 and 1: Crane bots
  * Bot 2 and 3: Long Arm bots
  * Bot 4 and 5: Bat bots
  * 
  * I took inspiration from https://www.youtube.com/watch?v=kUHmYKWwuWs
  * 
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// cthese values makes servo go from 0 to 180 degrees
#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
// Analog servos run at ~50 Hz updates
#define SERVO_FREQ 50 

int ledPin0 = 3;
int ledPin1 = 5;
int ledPin2 = 6;
int ledPin3 = 9;
int ledPin4 = 10;
int ledPin5 = 11;
int start0 = 10;
int start1 = 10;
int start2 = 10;
int start3 = 10;
int start4 = 10;
int start5 = 10;
bool fwd0 = true;
bool fwd1 = true;
bool fwd2 = true;
bool fwd3 = true;
bool fwd4 = true;
bool fwd5 = true;

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  delay(10);

  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);

  // initialize servo position
  start();

  // servo choreography sequence
  seq5();
  delay(1500);
  seq3();
  delay(1500);
  seq1();
  delay(1500);
  seq4LedIntermezzo();
  seq4();
  delay(1500);
  seq6();
  delay(1500);
  seq1();
  delay(1500);
  seq2();
  delay(1500);
  seq4();
  delay(1000);
  seq2();
  delay(1500);
  seq6();
  delay(1500);
  seq2();
  delay(1500);
  seq5();
  delay(1500);
  seq3();
}

// initialization of servo positions
void start() {
  setServo(start0, 0);
  setServo(start1, 1);
  setServo(start2, 2);
  setServo(start3, 3);
  setServo(start4, 4);
  setServo(start5, 5);
  delay(5000);
}

// Sixt sequence: jitters with in between pauses
// bots involved: 0, 1, 2, 3, 4, 5
void seq6() {
  ledSeq6();
  jitterSequence6();
}

// Fifth sequence: 1 slow initiator and 3 slow responses
// bots involved: 2, 3, 4, 5
void seq5() {
  ledSeq5Initiator();
  seq5Initiator();
  delay(2000);
  ledSeq5Response();
  delay(500);
  seq5Response();
}

// Fourth sequence: two bots start jittering after one another and then the rest follows.
// bots involved: 1, 2, 3, 4, 5
void seq4() {
  digitalWrite(ledPin5, HIGH);
  delay(1000);
  digitalWrite(ledPin5, LOW);
  jitterSequence4();
}

// Led blink intermezzo before sequence 4
// bots involved: 1, 2
void seq4LedIntermezzo() {
  ledSeq4First();
  delay(2000);
  ledSeq4Second();
}

// Third sequence: two bots start rocking moderatly fast, rest follows
// bots involved: 0, 1, 2, 5
void seq3() {
  digitalWrite(ledPin4, HIGH);
  delay(2000);
  seq3Initiator();
  ledSeq3();
  seq3Response();
}

// Second sequence: Quick sweep across, servo's create a wave like pattern
// bots involved: 0, 1, 2, 3, 4, 5
void seq2() {
  digitalWrite(ledPin3, HIGH);
  start3 = 70;
  delay(1500);
  setServo(start3, 3);
  digitalWrite(ledPin3, LOW);
  delay(1000);
  ledSeq2();
  start1 = 70;
  setServo(start1, 1);
  delay(300);
  start0 = 130;
  setServo(start0, 0);
  delay(300);
  start2 = 70;
  setServo(start2, 2);
  delay(300);
  start4 = 70;
  setServo(start4, 4);
  delay(300);
  start5 = 70;
  setServo(start5, 5);
  delay(300);
  start4 = 10;
  setServo(start4, 4);
  delay(300);
  start2 = 10;
  setServo(start2, 2);
  delay(300);
  start0 = 70;
  setServo(start0, 0);
  delay(300);
  start1 = 10;
  setServo(start1, 1);
}

// First sequence: two bots slowly move after one another, the rest follows
// bots involved: 0, 1, 2, 3, 4, 5
void seq1() {
  digitalWrite(ledPin1, HIGH);
  firstSeqInitiator1();
  delay(2000);
  firstSeqInitiator2();
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin0, LOW);
  ledSeq1();
  firstSeqResponse();
}

// Leds pattern before the sixt sequence
// bots involved: 0, 1, 2, 3, 4, 5
void ledSeq6() {
  digitalWrite(ledPin0, HIGH);
  digitalWrite(ledPin1, HIGH);
  delay(500);
  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin1, LOW);
  delay(2000);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  delay(500);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  delay(500);
  digitalWrite(ledPin4, HIGH);
  digitalWrite(ledPin5, HIGH);
  delay(500);
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin5, LOW);
}

// Leds pattern before the fifth sequence
// bots involved: 2
void ledSeq5Initiator() {
  digitalWrite(ledPin2, HIGH);
  delay(300);
  digitalWrite(ledPin2, LOW);
  delay(300);
  digitalWrite(ledPin2, HIGH);
  delay(300);
  digitalWrite(ledPin2, LOW);
  delay(255); // 300
  digitalWrite(ledPin2, HIGH);
  delay(250); // 450
  digitalWrite(ledPin2, LOW);
  delay(200); // 600
  digitalWrite(ledPin2, HIGH);
  delay(175); //700
  digitalWrite(ledPin2, LOW);
  delay(100); //850
  digitalWrite(ledPin2, HIGH);
  delay(100); //900
  digitalWrite(ledPin2, LOW);
  delay(100); //850
  digitalWrite(ledPin2, HIGH);
  delay(100); //900
  digitalWrite(ledPin2, LOW);
}

// Leds patterns after the initiator of the fifth sequence
// bots involved: 3, 4, 5
void ledSeq5Response() {
  digitalWrite(ledPin3, HIGH);
  delay(200);
  digitalWrite(ledPin4, HIGH);
  delay(50);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin3, LOW);
  delay(250); 
  digitalWrite(ledPin5, LOW);
  delay(50); 
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, LOW);
  delay(300); 
  digitalWrite(ledPin5, HIGH);
  delay(50);
  digitalWrite(ledPin4, HIGH);
  delay(200);
  digitalWrite(ledPin5, LOW);
  delay(50); 
  digitalWrite(ledPin4, LOW);
  delay(50); 
  digitalWrite(ledPin5, HIGH);
  delay(150);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, HIGH);
  delay(50);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin3, HIGH);
  delay(100);
  digitalWrite(ledPin4, LOW);
  delay(250);
  digitalWrite(ledPin5, HIGH);
  delay(450);
  digitalWrite(ledPin3, LOW);
  delay(150);
  digitalWrite(ledPin5, LOW);
  delay(50);
  digitalWrite(ledPin4, HIGH);
  delay(250);
  digitalWrite(ledPin4, LOW);
}

// Leds second intermezzo for sequence 4
// bots involved: 2
void ledSeq4Second(){
  digitalWrite(ledPin2, HIGH);
  delay(200);
  digitalWrite(ledPin2, LOW);
  delay(150); 
  digitalWrite(ledPin2, HIGH);
  delay(150); 
  digitalWrite(ledPin2, LOW);
  delay(450); 
  digitalWrite(ledPin2, HIGH);
  delay(300); 
  digitalWrite(ledPin2, LOW);
  delay(150); 
  digitalWrite(ledPin2, HIGH);
  delay(400); 
  digitalWrite(ledPin2, LOW);
}


// Leds first intermezzo for sequence 4
// bots involved: 4
void ledSeq4First(){
  digitalWrite(ledPin4, HIGH);
  delay(200);
  digitalWrite(ledPin4, LOW);
  delay(150); 
  digitalWrite(ledPin4, HIGH);
  delay(150); 
  digitalWrite(ledPin4, LOW);
  delay(250); 
  digitalWrite(ledPin4, HIGH);
  delay(100); 
  digitalWrite(ledPin4, LOW);
  delay(150); 
  digitalWrite(ledPin4, HIGH);
  delay(200);
  digitalWrite(ledPin4, LOW);
}

// Leds pattern before the third sequence
// bots involved: 0, 1, 2, 5
void ledSeq3() {
  delay(500);
  digitalWrite(ledPin5, HIGH);
  delay(250);
  digitalWrite(ledPin5, LOW);
  delay(50); 
  digitalWrite(ledPin5, HIGH);
  delay(150); 
  digitalWrite(ledPin5, LOW);
  delay(150);
  digitalWrite(ledPin5, HIGH);
  delay(100); 
  digitalWrite(ledPin5, LOW);
  delay(150); 
  digitalWrite(ledPin5, HIGH);
  delay(50); 
  digitalWrite(ledPin5, LOW);
  delay(500);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin0, HIGH);
  delay(250);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin0, LOW);
  delay(50); 
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin0, HIGH);
  delay(150);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin0, LOW);
  delay(150); 
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin0, HIGH);
  delay(100); 
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin0, LOW);
  delay(150); 
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin0, HIGH);
  delay(50); 
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin0, LOW);
}

// Leds pattern before the first sequence
// bots involved: 2, 3, 4, 5
void ledSeq1() {
  delay(200);
  digitalWrite(ledPin2, HIGH);
  delay(50);
  digitalWrite(ledPin3, HIGH);
  delay(50); 
  digitalWrite(ledPin4, HIGH);
  delay(150); 
  digitalWrite(ledPin5, HIGH);
  delay(100); 
  digitalWrite(ledPin3, LOW);
  delay(50); 
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, LOW);
  delay(100); 
  digitalWrite(ledPin3, LOW);
  delay(150); 
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin2, LOW);
  delay(50); 
  digitalWrite(ledPin3, LOW);
  delay(150);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin5, LOW);
  delay(150);
  digitalWrite(ledPin4, HIGH);
  digitalWrite(ledPin3, LOW);
  delay(100); 
  digitalWrite(ledPin4, LOW);
  delay(50); 
  digitalWrite(ledPin2, HIGH);
  delay(200);
  digitalWrite(ledPin5, HIGH);
  delay(50); 
  digitalWrite(ledPin5, LOW);
  delay(50); 
  digitalWrite(ledPin2, LOW);
}

// Leds pattern before the second sequence
// bots involved: 0, 1, 2, 4, 5
void ledSeq2() {
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin0, HIGH);
  delay(200);
  digitalWrite(ledPin1, HIGH);
  delay(50);  
  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin4, HIGH);
  digitalWrite(ledPin1, LOW);
  delay(50); 
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin0, HIGH);
  digitalWrite(ledPin1, HIGH);
  delay(200);
  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin5, HIGH);
  delay(200);
  digitalWrite(ledPin0, HIGH);
  digitalWrite(ledPin2, HIGH);
  delay(200);
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin0, LOW);
  delay(100); 
  digitalWrite(ledPin0, HIGH);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin1, LOW);
  delay(300);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin1, HIGH);
  delay(100);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin1, LOW);
}

// Fourth sequence: Jitters with a pause in between
// bots involved: 1, 2, 3, 4, 5
void jitterSequence4() {
  unsigned long startTimer = millis();
  unsigned long curTimer = millis();

  // starts off with bot 4 and 5
  while (curTimer < (startTimer + 1500)) {
    start5 = 140; 
    setServo(start5, 5);
    start4 = 70;
    setServo(start4, 4);
    delay(10);
    start4 = 140;
    setServo(start4, 4);
    start5 = 70; 
    setServo(start5, 5);
    delay(10);
    curTimer = millis();
  }
  startTimer = millis();

  // bot 2 gets added
  while (curTimer < (startTimer + 1000)) {
    start5 = 140;
    start2 = 70; 
    start4 = 70; 
    setServo(start4, 4); 
    setServo(start5, 5);
    setServo(start2, 2);
    delay(10);
    start5 = 70; 
    start2 = 140;
    start4 = 140; 
    setServo(start4, 4); 
    setServo(start5, 5);
    setServo(start2, 2);
    delay(10);
    curTimer = millis();
  }
  startTimer = millis();

  // bot 1 and 3 get added
  while (curTimer < (startTimer + 2000)) {
    start5 = 70;
    start3 = 70;
    start2 = 70;
    start1 = 80;
    start4 = 70; 
    setServo(start4, 4);  
    setServo(start3, 3);
    setServo(start2, 2);
    setServo(start1, 1);
    setServo(start5, 5);
    delay(10);
    start5 = 140;
    start3 = 140; 
    start2 = 140;
    start1 = 10;
    start4 = 140; 
    setServo(start4, 4); 
    setServo(start3, 3);
    setServo(start2, 2);
    setServo(start1, 1);
    setServo(start5, 5);
    delay(10);
    curTimer = millis();
  }
  startTimer = millis();

  // bot 4 and 5 stop
  while (curTimer < (startTimer + 1500)) {
    start1 = 80;
    start2 = 70;
    start3 = 70;
    setServo(start2, 2);
    setServo(start1, 1);
    setServo(start3, 3);
    delay(10);
    start1 = 10; 
    start2 = 140;
    start3 = 140;
    setServo(start2, 2);
    setServo(start1, 1);
    setServo(start3, 3);
    delay(10);
    curTimer = millis();
  }
  startTimer = millis();

  // bot 2 stops
  while (curTimer < (startTimer + 1000)) {
    start1 = 80;
    start3 = 70;
    setServo(start1, 1);
    setServo(start3, 3);
    delay(10);
    start1 = 10; 
    start3 = 140;
    setServo(start1, 1);
    setServo(start3, 3);
    delay(10);
    curTimer = millis();
  }
}

// Sequence four: first one bot starts to jitter, then the rest slowly joins
// bots involved: 0, 1, 2, 3, 4, 5
void jitterSequence6() {
  unsigned long startTimer = millis();
  unsigned long curTimer = millis();

  // bot 5 starts
  while (curTimer < (startTimer + 1500)) {
    start5 = 140; 
    setServo(start5, 5);
    start5 = 70; 
    setServo(start5, 5);
    curTimer = millis();
  }
  delay(1000);
  startTimer = millis();

  // bot 2 and 4 join
  while (curTimer < (startTimer + 1000)) {
    start5 = 140;
    start2 = 70; 
    start4 = 70; 
    setServo(start4, 4);
    setServo(start5, 5);
    setServo(start2, 2);
    
    start5 = 70; 
    start2 = 140;
    start4 = 140;
    setServo(start4, 4);
    setServo(start5, 5);
    setServo(start2, 2);
    curTimer = millis();
  }
  startTimer = millis();

  // bot 5 stops, 0 and 1 join
  while (curTimer < (startTimer + 2000)) {
    start3 = 70;
    start2 = 70;
    start1 = 80;
    start0 = 70;
    start4 = 70; 
    setServo(start4, 4); 
    setServo(start3, 3);
    setServo(start2, 2);
    setServo(start1, 1);
    setServo(start0, 0);
    start3 = 140; 
    start2 = 140;
    start1 = 10;
    start0 = 140;
    start4 = 140; 
    setServo(start4, 4); 
    setServo(start3, 3);
    setServo(start2, 2);
    setServo(start1, 1);
    setServo(start0, 0);
    curTimer = millis();
  }
  startTimer = millis();

  // bot 0, 2 and 3 stop
  while (curTimer < (startTimer + 700)) {
    start1 = 80;
    start4 = 70; 
    setServo(start4, 4); 
    setServo(start1, 1);
    start1 = 10; 
    start4 = 140; 
    setServo(start4, 4); 
    setServo(start1, 1);
    curTimer = millis();
  }
}

// Fifth sequence response: response slowly waving
// bots involved: 3, 4, 5
void seq5Response() {
  int tempNum;
  fwd4 = true;
  fwd5 = true;
  fwd3 = false;
  unsigned long startTimer = millis();
  unsigned long curTimer = millis();
  while (curTimer < (startTimer + 7000)) {
    if (fwd3 && start3 < 135) {
      start3++;
    }
    else if (!fwd3 && start3 > 75) {
      start3--;
    }
    else {
      fwd3 = !fwd3;
    }
    setServo(start3, 3);

    if (fwd4 && start4 < 135) {
      start4++;
    }
    else if (!fwd4 && start4 > 75) {
      start4--;
    }
    else {
      fwd4 = !fwd4;
    }
    setServo(start4, 4);

    if (fwd5 && start5 < 135) {
      start5++;
    }
    else if (!fwd5 && start5 > 75) {
      start5--;
    }
    else {
      fwd5 = !fwd5;
    }
    setServo(start5, 5);
    delay(20);
    curTimer = millis();
  }
}

// Fifth sequence iniator: one bot slowly starts to wave
// bots involved: 2
void seq5Initiator() {
  int tempNum;
  fwd2 = false;
  unsigned long startTimer = millis();
  unsigned long curTimer = millis();
  while (curTimer < (startTimer + 4500)) {
    if (fwd2 && start2 < 135) {
      start2++;
    }
    else if (!fwd2 && start2 > 75) {
      start2--;
    }
    else {
      fwd2 = !fwd2;
    }
    
    setServo(start2, 2);
    delay(20);
    curTimer = millis();
  }
}

// Third sequence response: rocking back and forth, moderate speed
// bots involved: 0, 1, 2, 5
void seq3Response() {
  int tempNum, delayC; 
  int delayC2 = 0;
  unsigned long startTimer = millis();
  unsigned long curTimer = millis();
  while (curTimer < (startTimer + 5000)) {
    delayC = 0;
    while (delayC < 20) {
      tempNum = checkDirS1(fwd5, start5);
      if (tempNum == -1)
        fwd5 = !fwd5;
      else
        start5 = tempNum;

      tempNum = checkDirS1(fwd2, start2);
      if (tempNum == -1)
        fwd2 = !fwd2;
      else
        start2 = tempNum;

      // two times as slow
      if (delayC%2 == 0) { 
        tempNum = checkDirS1(fwd0, start0);
        if (tempNum == -1)
          fwd0 = !fwd0;
        else
          start0 = tempNum;

        tempNum = checkDirS1(fwd1, start1);
        if (tempNum == -1)
          fwd1 = !fwd1;
        else
          start1 = tempNum;
      }
      
      delayC++;
      setServo(start5, 5);
      setServo(start0, 0);
      setServo(start2, 2);
      setServo(start1, 1);
      // give processor some time
      delay(1);
      curTimer = millis();
    }
  }
}

// Third sequence initator: rocking back and forth, moderate speed
// bots involved: 3, 4
void seq3Initiator() {
  int tempNum, delayC;
  unsigned long startTimer = millis();
  unsigned long curTimer = millis();
  
  // led3 is on during initiation
  digitalWrite(ledPin3, HIGH);
  while (curTimer < (startTimer + 3000)) {
    tempNum = checkDirS1(fwd4, start4);
      if (tempNum == -1)
    fwd4 = !fwd4;
      else
    start4 = tempNum;

    setServo(start4, 4);
    curTimer = millis();
  }
  startTimer = millis();
  while (curTimer < (startTimer + 3000)) {
    delayC = 0;
    while (delayC < 10) {
      tempNum = checkDirS1(fwd3, start3);
        if (tempNum == -1)
      fwd3 = !fwd3;
        else
      start3 = tempNum;
      delayC++;
      setServo(start3, 3);
      delay(5);
    }
    tempNum = checkDirS1(fwd4, start4);
    if (tempNum == -1)
      fwd4 = !fwd4;
    else
      start4 = tempNum;
    setServo(start4, 4);
    
    delay(50);
    curTimer = millis();
  }
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin3, LOW);
}

// First initiator for the first sequence, done by bot 1, slow movements
// Bots involved: 1
void firstSeqInitiator1() {
  int tempNum;
  unsigned long startTimer = millis();
  unsigned long curTimer = millis();

  // move for 8 seconds
  while (curTimer < (startTimer + 8000)) {
    tempNum = checkDirS1(fwd1, start1);
    if (tempNum == -1)
      fwd1 = !fwd1;
    else
      start1 = tempNum;

    // flicker led1 while moving
    if (start1%10 == 0)  {
      digitalWrite(ledPin1, !digitalRead(ledPin1));
    }
    
    setServo(start1, 1);
    delay(10);
    curTimer = millis();
  }
}

// Second initiator for the first sequence, done by bot 0, slow movements
// Bots involved: 0
void firstSeqInitiator2() {
  int tempNum;
  unsigned long startTimer = millis();
  unsigned long curTimer = millis();

  // move for 6 seconds
  while (curTimer < (startTimer + 6000)) {
    tempNum = checkDirS1(fwd0, start0);
    if (tempNum == -1)
      fwd0 = !fwd0;
    else
      start0 = tempNum;

    // flicker led0 while moving
    if (start0%10 == 0)  {
      digitalWrite(ledPin0, !digitalRead(ledPin0));
    }
    
    setServo(start0, 0);
    delay(10);
    curTimer = millis();
  }
}

// Response two the first sequence initiators, slow movements 
// Bots involved: 2, 3, 4, 5
void firstSeqResponse() {
  int tempNum;
  int delayC;
  unsigned long startTimer = millis();
  unsigned long curTimer = millis();

  // for 8 seconds do
  while (curTimer < (startTimer + 8000)) {
    delayC = 0;
    while (delayC < 5) {
      tempNum = checkDirS1(fwd4, start4);
        if (tempNum == -1)
      fwd4 = !fwd4;
        else
      start4 = tempNum;

      tempNum = checkDirS1(fwd5, start5);
        if (tempNum == -1)
      fwd5 = !fwd5;
        else
      start5 = tempNum;

      // 2 times as slow as bot 4 and 5
      if (delayC%2 == 0) { 
        tempNum = checkDirS1(fwd3, start3);
        if (tempNum == -1)
          fwd3 = !fwd3;
        else
          start3 = tempNum;

        tempNum = checkDirS1(fwd2, start2);
        if (tempNum == -1)
          fwd2 = !fwd2;
        else
          start2 = tempNum;
      }
      
      delayC++;
      setServo(start4, 4);
      setServo(start3, 3);
      setServo(start2, 2);
      setServo(start5, 5);
      delay(2);
    }
    curTimer = millis();
  }
  startTimer = millis();
  
  // continue movement for bot 2, 1.5 secs longer than other bots
  while(curTimer < (startTimer + 1500)) {
    tempNum = checkDirS1(fwd2, start2);
    if (tempNum == -1)
      fwd2 = !fwd2;
    else
      start3 = tempNum;
    setServo(start2, 2);

    delay(10);
    curTimer = millis();
  } 
}

// set new position for servo
void setServo(int start, int port) {
  int angle = map(start, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  int pulse_width = int(float(angle) / 1000000 * SERVO_FREQ * 4096);
  pwm.setPWM(port, 0, pulse_width);
}

// Make sure servo stays between 10 and 170 degrees to prevent damage
// and make the servos go back and forth
int checkDirS1(bool dir, int num) {
  if (dir && num < 170) {
    return num+1;
  }
  else if (!dir && num > 10) {
    return num-1;
  }
  else {
    return -1;
  }
}

// necessary for arduino
// you can put code here if you want continious cycles
void loop() {
}
