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
const int JOY_BTN = 20;

// motors batch
const int motors_ports[8] = {
  MOTOR_A_0, MOTOR_A_1, 
  MOTOR_B_0, MOTOR_B_1,
  MOTOR_C_0, MOTOR_C_1,
  MOTOR_D_0, MOTOR_D_1
};

// buzzer output
const int BUZZER_PORT = 12; // must be PWM 

// 7 segment display
int display_mask_value[10] = {0b11000000, 0b11111001, 0b10100100,
                  0b10110000, 0b10011001, 0b10010010,
                  0b10000010, 0b11111000 ,0b10000000, 0b10010000};

int letters_mask[2] = {0b10001110, 0b10000110}; // 0: F, 1: E

int past_values[1500][2];

const byte ledPin = 13;
const byte interruptPin = JOY_BTN;
volatile byte state = LOW;


void setup(){
  DDRL = 0xFF;
  PORTL = 0b11111111;

  // setup motors ports to output
  for (int i = 0; i < 8; i++){
    pinMode(motors_ports[i], OUTPUT);
  }

  // setup joystick ports to input
  pinMode(AXIS_X, INPUT);
  pinMode(AXIS_Y, INPUT);

  // serial
  Serial.begin(9600);

  // buzzer output
  pinMode(BUZZER_PORT, OUTPUT);

  // parking interruption
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
  PORTL = letters_mask[0];
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

    display_number(registred_values / 100);
    
    if (registred_values > 999) {
      Serial.println("Maximum exedeed.");
      state = 2;
      break;
    }
  }

 } else if (state == 2){
  // executing
  blink_output_references();
  PORTL = letters_mask[1];
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

void display_number(int number) {
  if (number < 10) {
    PORTL = display_mask_value[number];
  }
}


void blink_output_references() {
  int last_value = PORTL;
  for (int i = 0; i < 5; i++){
    PORTL = 0xFF;
    analogWrite(BUZZER_PORT, 52);
    delay(100);
    analogWrite(BUZZER_PORT, 0);
    PORTL = last_value;
    delay(100);
  }
}
 
