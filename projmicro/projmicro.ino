// output motors ports
const int MOTOR_A_0 = 2;
const int MOTOR_A_1 = 3;
const int MOTOR_B_0 = 4;
const int MOTOR_B_1 = 5;
const int MOTOR_C_0 = 6;
const int MOTOR_C_1 = 7;
const int MOTOR_D_0 = 8;
const int MOTOR_D_1 = 9;

// joystick variables
const int AXIS_X = A0;
const int AXIS_Y = A1;
//const int JOY_BTN = ;


const int motors_ports[8] = {
  MOTOR_A_0, MOTOR_A_1, 
  MOTOR_B_0, MOTOR_B_1,
  MOTOR_C_0, MOTOR_C_1,
  MOTOR_D_0, MOTOR_D_1
};

const byte ledPin = 13;
const byte interruptPin = 20;
volatile byte state = LOW;


void setup(){
  // setup motors ports to output
  for (int i = 0; i < 8; i++){
    pinMode(motors_ports[i], OUTPUT);
  }

  // setup joystick ports to input
  pinMode(AXIS_X, INPUT);
  pinMode(AXIS_Y, INPUT);

  //serial
  Serial.begin(9600);

  //parking interruption
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), park , FALLING);
}


void loop(){
  
  //set led state
  digitalWrite(ledPin, state);

  int y = analogRead(AXIS_Y);
  int x = analogRead(AXIS_X);

  int direita = 100;
  int esquerda = 100;

  if(x < 512){ //esquerda
    direita = 100;
    esquerda = map(x, 511, 0, 100, 0);
  }else{       //direita
    direita = map(x, 512, 1023, 100, 0);
    esquerda = 100;
  }

  Serial.println(y);

  if (y < 490){ //Front (or forward)
    int velocidade = map(y, 511, 0, 0, 255);
     analogWrite(MOTOR_A_0, velocidade * direita / 100);
     analogWrite(MOTOR_A_1, 0);
     
     analogWrite(MOTOR_B_0, velocidade * direita / 100);
     analogWrite(MOTOR_B_1, 0);

     analogWrite(MOTOR_C_0, velocidade * esquerda / 100);
     analogWrite(MOTOR_C_1, 0);

     analogWrite(MOTOR_D_0, velocidade * esquerda / 100);
     analogWrite(MOTOR_D_1, 0);
 
    }
   else if(y > 530){ //back
     int velocidade = map(y, 512, 1023, 0, 255);
     analogWrite(MOTOR_A_0, 0);
     analogWrite(MOTOR_A_1, velocidade * direita / 100);

     analogWrite(MOTOR_B_0, 0);
     analogWrite(MOTOR_B_1, velocidade * direita / 100);
     
     analogWrite(MOTOR_C_0, 0);
     analogWrite(MOTOR_C_1, velocidade * esquerda / 100);

     analogWrite(MOTOR_D_0, 0);
     analogWrite(MOTOR_D_1, velocidade * esquerda / 100); 
     }
    else{
     digitalWrite(MOTOR_A_0, 0);
     digitalWrite(MOTOR_A_1, 0);

     digitalWrite(MOTOR_B_0, 0);
     digitalWrite(MOTOR_B_1, 0);
     
     digitalWrite(MOTOR_C_0, 0);
     digitalWrite(MOTOR_C_1, 0);

     digitalWrite(MOTOR_D_0, 0);
     digitalWrite(MOTOR_D_1, 0); 
    }
    
 
}
void park() {
     state = !state;
     for (int i = 0; i < 5000; i++){
     analogWrite(MOTOR_A_0, 0);
     analogWrite(MOTOR_A_1, 255);

     analogWrite(MOTOR_B_0, 0);
     analogWrite(MOTOR_B_1, 255);
     
     analogWrite(MOTOR_C_0, 0);
     analogWrite(MOTOR_C_1, 0);

     analogWrite(MOTOR_D_0, 0);
     analogWrite(MOTOR_D_1, 0);
      }

     for (int i = 0; i < 2000; i++){
     analogWrite(MOTOR_A_0, 0);
     analogWrite(MOTOR_A_1, 255);

     analogWrite(MOTOR_B_0, 0);
     analogWrite(MOTOR_B_1, 255);
     
     analogWrite(MOTOR_C_0, 0);
     analogWrite(MOTOR_C_1, 255);

     analogWrite(MOTOR_D_0, 0);
     analogWrite(MOTOR_D_1, 255);
      }

     for (int i = 0; i < 7500; i++){
     analogWrite(MOTOR_A_0, 0);
     analogWrite(MOTOR_A_1, 0);

     analogWrite(MOTOR_B_0, 0);
     analogWrite(MOTOR_B_1, 0);
     
     analogWrite(MOTOR_C_0, 0);
     analogWrite(MOTOR_C_1, 255);

     analogWrite(MOTOR_D_0, 0);
     analogWrite(MOTOR_D_1, 255);
      }
  }
