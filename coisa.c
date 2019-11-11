// output motors ports
const int MOTOR_A_0 = 0;
const int MOTOR_A_1 = 1;
const int MOTOR_B_0 = 2;
const int MOTOR_B_1 = 3;
const int MOTOR_C_0 = 4;
const int MOTOR_C_1 = 5;
const int MOTOR_D_0 = 6;
const int MOTOR_D_1 = 7;

const int[8] motors_ports = {
	MOTOR_A_0, MOTOR_A_1, 
	MOTOR_B_0, MOTOR_B_1,
	MOTOR_C_0, MOTOR_C_1,
	MOTOR_D_0, MOTOR_D_1
}


void setup(){
	// setup motors ports to output
	for (int i = 0; i < 8){
		pinMode(motors_ports[i], OUTPUT);
	}

	analogWrite(MOTOR_A_0, 50);
	analogWrite(MOTOR_A_1, 0);
}


void loop(){

}