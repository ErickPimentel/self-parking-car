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

int past_values[1000][2];

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
  attachInterrupt(digitalPinToInterrupt(interruptPin), state_changer , FALLING);
}


int registred_values = 0; // array counter

void loop(){
  
  //Serial.println(state);
  digitalWrite(ledPin, state);

  int x = analogRead(AXIS_X);
  int y = analogRead(AXIS_Y);

 if (state == 0){
   // free mode control
  Serial.println("Free mode!");
  control(x, y);

 } else if (state == 1){
  // recording
  
  while (state == 1) {
    Serial.println("Recording!");
    past_values[registred_values][0] = analogRead(AXIS_X); //set x
    past_values[registred_values][1] = analogRead(AXIS_Y); //set y
    control(past_values[registred_values][0], past_values[registred_values][1]);

    registred_values++;
    
    if (registred_values > 999) {
      Serial.println("Maximum exedeed.");
      state = 2;
      break;
    }
  }

 } else if (state == 2){
  // executing

  for (int i = 0; i < registred_values; i++){
    Serial.println("Execunting.");
    control(past_values[i][0], past_values[i][1]);
  }

  registred_values = 0;

  state = 0;

 }
 
}

void control(int x, int y){
  
  int direita = 100;
  int esquerda = 100;

  if(x < 512){ //esquerda
    direita = 100;
    esquerda = map(x, 511, 0, 100, 0);
  }else{       //direita
    direita = map(x, 512, 1023, 100, 0);
    esquerda = 100;
  }

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
      //end engine noise
      for(int i = 0; i < 8; i++){
        digitalWrite(motors_ports[i], 0);
        }
    }
    
  
  }
void state_changer() {
     if (state == 0) {
      state = 1;
     } else if (state == 1) {
      state = 2;
     }

 }
