// units: time --> mille sec, distance --> cm

const int trigPin1 = 2;//front sensor
const int echoPin1 = 4;

const int trigPin2 = 10; //left sensor
const int echoPin2 = 11;

const int trigPin3 = 13;// right sensor
const int echoPin3 = 12;

const int motor1livepin= 6;  // right motor pins
const int motor1groungpin = 7;

const int motor2livepin = 9; // left motor pins
const int motor2groungpin = 8;

const int engineleft = 3;
const int engineright = 5;

char previousdirection;



#define DIS 19 //distance



void setup()
{
Serial.begin(9600);
pinMode(trigPin1, OUTPUT); //pins of the sensors
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);

pinMode (motor1livepin, OUTPUT);   // pins of the motors
pinMode (motor1groungpin, OUTPUT);
pinMode (motor2livepin, OUTPUT);
pinMode (motor2groungpin, OUTPUT);
pinMode(engineleft, OUTPUT);
pinMode(engineright, OUTPUT);

}



void loop()
{
  stop();
  analogWrite(engineleft , 77);
  analogWrite(engineright , 88);
  
  // no obstacle in all 3 sides
  if (FrontSensor() > DIS && RightSensor() > DIS && LeftSensor() > DIS)
  {
    forward();
    delay(960);
    previousdirection = 's';
  }
  
  // obstacle on left & right sides
  else if ( FrontSensor () > DIS && RightSensor () < DIS && LeftSensor ()< DIS) 
  {
    forward();  
    delay(960);
    previousdirection = 's';
  }
    
  // obstacle infront of all 3 sides
  else if ( FrontSensor() < DIS && RightSensor() < DIS && LeftSensor() < DIS)
  {
    reverse ();
    delay(960);
    stop();
      if(previousdirection == 'l'){
        if (RightSensor () >DIS){
          turn_right (); 
          delay(680);
          stop();
          forward();
          delay(960);
          previousdirection = 'r';
        }
        else{
          turn_left (); 
          delay(680);
          stop();
          forward();
          delay(960);
          previousdirection = 'l';
        }
      }
      else {          // if(previousdirection == 'r')
        if (LeftSensor () >DIS){
          turn_left (); 
          delay(680);
          stop();
          forward();
          delay(960);
          previousdirection = 'l';
        }
        else{
          turn_right (); 
          delay(680);
          stop();
          forward();
          delay(960);
          previousdirection = 'r';
        }
      }
  }
  
  // obstacle on right and front sides
  else if (FrontSensor() <DIS && RightSensor () <DIS && LeftSensor ()>DIS) 
    {
      turn_left (); 
      delay(680);
      stop();
      forward();
      delay(960);
      previousdirection = 'l';
    }
  
  // obstacle on left and front sides
  else if (FrontSensor() <DIS && RightSensor () >DIS && LeftSensor ()<DIS) 
    {
      turn_right (); 
      delay(680);
      stop();
      forward();
      delay(960);
      previousdirection = 'r';
    }
  
  // obstacle on front side only
  else if (FrontSensor() <DIS && RightSensor () >DIS && LeftSensor ()>DIS) 
    {
      turn_left (); 
      delay(680);
      stop();
      forward();
      delay(960);
      previousdirection = 'l';
    }
  
  // obstacle on left side
  else if (FrontSensor() >DIS && RightSensor () >DIS && LeftSensor ()<DIS) 
    {
      forward();
      delay(960);
      previousdirection = 's';
    }
  
  // obstacle on right sides
  else if (FrontSensor() >DIS && RightSensor () <DIS && LeftSensor ()>DIS)
    {
      turn_left ();
      delay(680);
      stop();
      forward();
      delay(960);
      previousdirection = 'l';
    }

  // nothing happpened..
  else
    {
      stop();
      //forward();
      //delay(700);
      //previousdirection = 's';
    }

}


//Directions Functions

//Forward Direction
void forward ()
  {
    // right motor go on
    digitalWrite(motor1livepin, HIGH); 
    digitalWrite(motor1groungpin, LOW);
    // left motor go on
    digitalWrite(motor2livepin, HIGH);
    digitalWrite(motor2groungpin, LOW);
  }

//Turn Left Direction
void turn_left ()
  {
    // right motor go on
    digitalWrite(motor1livepin, HIGH);
    digitalWrite(motor1groungpin, LOW);
    // left motor off
    digitalWrite(motor2livepin, LOW);
    digitalWrite(motor2groungpin, LOW);
   
  }

//Turn Right Direction
void turn_right ()
  {
    // right motor go
    digitalWrite(motor1livepin, LOW);
    digitalWrite(motor1groungpin, LOW);
    // left motor off
    digitalWrite(motor2livepin, HIGH);
    digitalWrite(motor2groungpin, LOW);
    
  }
  
//REVERSE -- BACKWARD
void reverse ()
  {
    // right motor go back
    digitalWrite(motor1livepin, LOW);
    digitalWrite(motor1groungpin, HIGH);
    // left motor go back
    digitalWrite(motor2livepin, LOW);
    digitalWrite(motor2groungpin, HIGH);
  }

// STOP
void stop()
  {
    // all motors off
    digitalWrite(motor1livepin, LOW);
    digitalWrite(motor1groungpin, LOW);
    digitalWrite(motor2livepin, LOW);
    digitalWrite(motor2groungpin, LOW);
    delay(3000);
  }



//sensors Functions

 
long FrontSensor ()
  {
    long dur, cm;
    // Clears the trigPin condition
    digitalWrite(trigPin1, LOW);
    // keep this state for 5 microseconds
    delayMicroseconds(5);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds [transmit]
    digitalWrite(trigPin1, HIGH);
    //keep this state for 10 microseconds
    delayMicroseconds(10);
    // stop transmitting
    digitalWrite(trigPin1, LOW);
    // pulse in returns the time from transmitting to receiving in microseconds
    // so, duration is this time
    dur = pulseIn(echoPin1, HIGH);
    
    // distance in centimeters.
    cm = (dur / 2.0) / 29.1;
    Serial.print("Front ");
    Serial.println(cm);
    
    return cm;
  }

long LeftSensor ()
  {
    long dur, cm;
    // Clears the trigPin condition
    digitalWrite(trigPin2, LOW);
    // keep this state for 5 microseconds
    delayMicroseconds(5);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds [transmit]
    digitalWrite(trigPin2, HIGH);
    //keep this state for 10 microseconds
    delayMicroseconds(10);
    // stop transmitting
    digitalWrite(trigPin2, LOW);
    // pulse in returns the time from transmitting to receiving in microseconds
    // so, duration is this time
    dur = pulseIn(echoPin2, HIGH);
    
    // distance in centimeters.
    cm = (dur / 2.0) / 29.1;
    Serial.print("Left ");
    Serial.println(cm);
    
    return cm;
  }

  
long RightSensor ()
  {
    long dur, cm;
    // Clears the trigPin condition
    digitalWrite(trigPin3, LOW);
    // keep this state for 5 microseconds
    delayMicroseconds(5);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds [transmit]
    digitalWrite(trigPin3, HIGH);
    //keep this state for 10 microseconds
    delayMicroseconds(10);
    // stop transmitting
    digitalWrite(trigPin3, LOW);
    // pulse in returns the time from transmitting to receiving in microseconds
    // so, duration is this time
    dur = pulseIn(echoPin3, HIGH);
    
    // distance in centimeters.
    cm = (dur / 2.0) / 29.1;
    Serial.print("Right ");
    Serial.println(cm);
    
    return cm;
  }
