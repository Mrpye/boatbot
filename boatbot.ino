/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/

#include <Servo.h>
// defines pins numbers
const int right_trigPin = 2;
const int right_echoPin = 3;

const int left_trigPin = 4;
const int left_echoPin = 5;

// defines variables
int left_distance[3];
int right_distance[3];

int left_avg_distance;
int right_avg_distance;
int pos = 0;


Servo myservo;  // create servo object to control a servo

void setup() {
  pinMode(left_trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(left_echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(right_trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(right_echoPin, INPUT); // Sets the echoPin as an Input
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);              // tell servo to go to position in variable 'pos'
  delay(15); 
  Serial.begin(9600); // Starts the serial communication
}

int getDistance(int trigPin,int echoPin){
  int distance;
  long duration;
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  return distance;
}


void loop() {
int mode=0;
int walldist=5;
int straight_at=4;
int dist_constraint=50;
int turn_intensity=10;

  if(mode==0){
    //this make go straight down middle
    left_distance[0]=getDistance(left_trigPin,left_echoPin);
    right_distance[0]=getDistance(right_trigPin,right_echoPin);
    left_distance[1]=getDistance(left_trigPin,left_echoPin);
    right_distance[1]=getDistance(right_trigPin,right_echoPin);
    left_distance[2]=getDistance(left_trigPin,left_echoPin);
    right_distance[2]=getDistance(right_trigPin,right_echoPin);

    left_avg_distance=(left_distance[0]+left_distance[1]+left_distance[2])/2;
    right_avg_distance=(right_distance[0]+right_distance[1]+right_distance[2])/2;

    
    long n=(constrain(left_avg_distance,0,dist_constraint)-constrain(right_avg_distance,0,dist_constraint));
    int walldist=10;
    
    //n=constrain(n,-40,40);
    if(n>=(-straight_at)&&n<=straight_at){
      myservo.write(90);  
    }else{
      int val = map(-1*n, -(dist_constraint+turn_intensity), (dist_constraint+turn_intensity), 0, 200); 
      myservo.write(val);   
    }
  }else if(mode=1){
     
      
  }
  
  delay(10);
}

