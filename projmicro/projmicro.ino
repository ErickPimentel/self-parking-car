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


void setup(){
  // setup motors ports to output
  for (int i = 0; i < 8; i++){
    pinMode(motors_ports[i], OUTPUT);
  }

  // setup joystick ports to input
  pinMode(AXIS_X, INPUT);
  pinMode(AXIS_Y, INPUT);

  Serial.begin(9600);
  
  
  // analogWrite(MOTOR_B_0, 0);
  // analogWrite(MOTOR_B_1, 0);
}


void loop(){
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

  if (y < 512){
    int velocidade = map(y, 511, 0, 0, 255);
     analogWrite(MOTOR_A_0, velocidade * direita / 100);
     analogWrite(MOTOR_A_1, 0);
     
     analogWrite(MOTOR_B_0, velocidade * direita / 100);
     analogWrite(MOTOR_B_1, 0);

     analogWrite(MOTOR_C_0, velocidade * esquerda / 100);
     analogWrite(MOTOR_C_1, 0);

     analogWrite(MOTOR_D_0, velocidade * esquerda / 100);
     analogWrite(MOTOR_D_1, 0);
 
    }else{
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
    
 
    }
