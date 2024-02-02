//#include <HUSKYLENS.h>
// coding by : magy El Banhawy ,Rawan Abd ElGhafar
#include <HCSR04.h>
char command;
//Motor Driver Right pins
int F_ENR = 2;
int bluetooth = 3;
int B_ENR = 4;
int F_PWM_R = 5;
int B_PWM_R = 6;
//Motors Driver Left pins
int F_ENL = 7;
int B_ENL = 8;
int F_PWM_L = 9;
int B_PWM_L = 10;
int motors_delay = 50;
int delay_time = 0;
UltraSonicDistanceSensor distanceSensor1(13, 12);  //(Trig,Echo)   forward
const int DISTANCE_THRESHOLD = 20;
int distance_1 = 100;
//HUSKYLENS huskylens;
void setup() {
  Serial.begin(9600);
  pinMode(F_ENR, OUTPUT);
  pinMode(B_ENR, OUTPUT);
  pinMode(F_PWM_R, OUTPUT);
  pinMode(B_PWM_R, OUTPUT);
  pinMode(F_ENL, OUTPUT);
  pinMode(B_ENL, OUTPUT);
  pinMode(F_PWM_L, OUTPUT);
  pinMode(B_PWM_L, OUTPUT);
  pinMode(bluetooth, OUTPUT);
  digitalWrite(bluetooth, LOW);
  //Set HIGH Enable pins motors
  digitalWrite(F_ENR, HIGH);
  digitalWrite(B_ENR, HIGH);
  digitalWrite(F_ENL, HIGH);
  digitalWrite(B_ENL, HIGH);
 /* while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  //huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);  //Switch the algorithm to object tracking.*/
  //stop_fast();
}  //end setup
/*int widthLevel = 50;
int xLeft = 160 - 40;
int xRight = 160 + 40;
bool isTurning = false;
bool isTurningLeft = true;
bool isInside(int value, int min, int max) {
  return (value >= min && value <= max);
}*/

void loop() {
  distance_1 = distanceSensor1.measureDistanceCm();
  Serial.print("Ultrasonic 1 from forward == ");
  Serial.println(distance_1);
  //end distance
// /* backward_fast();
//  delay(10000);
//  stop_fast();
//   delay(1000);
  long duration, distance;
  digitalWrite(13, LOW);
  delayMicroseconds(2);
  digitalWrite(13, HIGH);
  delayMicroseconds(10);
  digitalWrite(13, LOW);
  duration = pulseIn(12, HIGH);
  distance = duration * 0.034 / 2;
//-------1-------
  forward_fast();
  delay(53000);
  stop_fast();
  delay(1000);
  right();
  delay(2400);
  stop_fast();
  delay(1000);
//--------2------
  forward_fast();
  delay(60000);
  stop_fast();
  delay(1000);
  right();
  delay(2400);
  stop_fast();
  delay(1000);
//--------3-------
  forward_fast();
  delay(55000);
  stop_fast();
  delay(1000);
  right();
  delay(2400);
  stop_fast();
  delay(1000);
//-------4-----
  forward_fast();
  delay(60000);
  stop_fast();
  delay(1000);
  right();
  delay(2400);
  stop_fast();
  delay(1000);
//-------------
  forward_fast();
  delay(4000);
  left();
  delay(2000);
  stop_fast();
  delay(1000);
  forward_fast();
  delay(4000);
//  -----------
  stop_fast();
  delay(10000);
  while (delay_time < 10000 && (distanceSensor1.measureDistanceCm() >= 20 && distanceSensor1.measureDistanceCm() != -1)) {
    delay_time = delay_time + 100;
    Serial.println(delay_time);
    forward_fast();
    delay(100);
  }
  stop_fast();
  //delay(5000);
  //continuo delay
  if (delay_time != 10000) {
    while (delay_time < 10000 && (distanceSensor1.measureDistanceCm() >= 20 && distanceSensor1.measureDistanceCm() != -1)) {
      delay_time = delay_time + 100;
      Serial.println(delay_time);
      forward_fast();
      delay(100);
    }
  }
  if (delay_time == 10000){
delay_time = 0;
stop_backward_slow();
delay(5000);
  }
  
  //bluetooth
  if (Serial.available() > 0) {
    command = Serial.read();
    Serial.print("bluetooth command=   ");Serial.println(command);
    switch (command) {
      case 'U':
        forward_fast();
        break;
      case 'D':
        backward_fast();
        break;
      case 'L':
        left();
        break;
        case 'R':
        right();
        break;
      case '1':
        forwrd_slow();
        break;
      case '3':
        backward_slow();
        break;
      case 'S':
        stop_fast();
        break;
      case 'M':
        digitalWrite(bluetooth, HIGH);
        delay(1000);
        digitalWrite(bluetooth, LOW);
        break;
    }
  }//end bluetooth

}//end loop
/*void driveBot(HUSKYLENSResult result) {
  if (result.xCenter <= 140) {
    //left();
  }
  else if (result.xCenter >= 200) {
    //right();
  }
  else if ((result.xCenter >= 140) && (result.xCenter <= 200)) {
    if (result.width <= 20) {
      //forward();
    }
    else if (result.width > 20) {
      //stop();
    }
  }
} */// end driveBot
void forwrd_slow() {
  Serial.println("forwrd_slow");
  for (int i = 0; i <= 255; i = i + 5) {
    analogWrite(F_PWM_R, i);
    analogWrite(B_PWM_R, 0);
    analogWrite(F_PWM_L, i);
    analogWrite(B_PWM_L, 0);
    delay(motors_delay);
  }
} //end  forwrd_slow
void forward_fast() {
  Serial.println("forward_fast");
  analogWrite(F_PWM_R, 255);
  analogWrite(B_PWM_R, 0);
  analogWrite(F_PWM_L, 255);
  analogWrite(B_PWM_L, 0);
}//end  forward_fast
void right() {
  Serial.println("right");
  analogWrite(F_PWM_R, 0);
  analogWrite(B_PWM_R, 255);
  analogWrite(F_PWM_L, 255);
  analogWrite(B_PWM_L, 0);
}//end  right
void left() {
  Serial.println("left");
  analogWrite(F_PWM_R, 255);
  analogWrite(B_PWM_R, 0);
  analogWrite(F_PWM_L, 0);
  analogWrite(B_PWM_L, 255);
}//end  left
void stop_forward_slow() {
  Serial.println("stop_forward_slow");
  for (int i = 255; i >= 0; i = i - 5) {
    analogWrite(F_PWM_R, i);
    analogWrite(B_PWM_R, 0);
    analogWrite(F_PWM_L, i);
    analogWrite(B_PWM_L, 0);
    delay(motors_delay);
  }
}//end  stop_forward_slow
void stop_fast() {
  Serial.println("stop_fast");
  analogWrite(F_PWM_R, 0);
  analogWrite(B_PWM_R, 0);
  analogWrite(F_PWM_L, 0);
  analogWrite(B_PWM_L, 0);
}//end  stop_forward_slow
void backward_fast() {
  Serial.println("backward_fast");
  analogWrite(F_PWM_R, 0);
  analogWrite(B_PWM_R, 255);
  analogWrite(F_PWM_L, 0);
  analogWrite(B_PWM_L, 255);
}//end  backward_fast
void backward_slow() {
  Serial.println("backward_slow");
  for (int i = 0; i <= 255; i = i + 5) {
    analogWrite(F_PWM_R, 0);
    analogWrite(B_PWM_R, i);
    analogWrite(F_PWM_L, 0);
    analogWrite(B_PWM_L, i);
    delay(motors_delay);
  }
}//end  backward_slow
void stop_backward_slow() {
  Serial.println("stop_backward_slow");
  for (int i = 255; i >= 0; i = i - 5) {
    analogWrite(F_PWM_R, 0);
    analogWrite(B_PWM_R, i);
    analogWrite(F_PWM_L, 0);
    analogWrite(B_PWM_L, i);
    delay(motors_delay);
  }
}//end  stop_backward_slow
/*void printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
  } else if (result.command == COMMAND_RETURN_ARROW) {
    Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
  } else {
    Serial.println("Object unknown!");
  }
}  //printResult*/
