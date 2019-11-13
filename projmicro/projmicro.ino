// output motors ports
const int MOTOR_A_0 = 2;
const int MOTOR_A_1 = 3;
const int MOTOR_B_0 = 4;
const int MOTOR_B_1 = 5;
const int MOTOR_C_0 = 6;
const int MOTOR_C_1 = 7;
const int MOTOR_D_0 = 8;
const int MOTOR_D_1 = 9.;

const int motors_ports[8] = {
  MOTOR_A_0, MOTOR_A_1, 
  MOTOR_B_0, MOTOR_B_1,
  MOTOR_C_0, MOTOR_C_1,
  MOTOR_D_0, MOTOR_D_1
};


void setup(){
  for (int i = 0; i < 8; i++){
    pinMode(motors_ports[i], OUTPUT);
  }      
}


void loop(){

}
