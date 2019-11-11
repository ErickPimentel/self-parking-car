#include <Ultrasonic.h>

const int A1AD = 2;
const int A1BD = 3;
const int B1AD = 4;
const int B1BD = 5;

const int A1AE = 6;
const int A1BE = 7;
const int B1AE = 8;
const int B1BE = 9;

void setup() {
  pinMode(B1AD,OUTPUT);
  pinMode(B1BD,OUTPUT);
  
  pinMode(A1AD,OUTPUT);
  pinMode(A1BD,OUTPUT);
  
  pinMode(B1AE,OUTPUT);
  pinMode(B1BE,OUTPUT);
  
  pinMode(A1AE,OUTPUT);
  pinMode(A1BE,OUTPUT);
  delay(3000);
}

void motorA(char d){
  if(d =='F'){
    analogWrite(A1AD,0);
    analogWrite(A1BD,100); 
  }else if (d =='B'){
    analogWrite(A1AD,100);
    analogWrite(A1BD,0);    
  }else{
    analogWrite(A1AD,0);
    analogWrite(A1BD,0);    
  }
}

void motorB(char d){
    if(d =='F'){
      analogWrite(B1AD,0);
      analogWrite(B1BD,150); 
    }else if(d =='B'){
      analogWrite(B1AD,150);
      analogWrite(B1BD,0);    
    }else{      
      analogWrite(B1AD,0);
      analogWrite(B1BD,0);     
    }

}

void motorC(char d){
  if(d =='B'){
    analogWrite(A1AE,0);
    analogWrite(A1BE, 150); 
  }else if (d =='F'){
    analogWrite(A1AE,150);
    analogWrite(A1BE,0);    
  }else{
    analogWrite(A1AE,0);
    analogWrite(A1BE,0);    
  }
}

void motorD(char d){
    if(d =='B'){
      analogWrite(B1AE,0);
      analogWrite(B1BE,150); 
    }else if(d =='F'){
      analogWrite(B1AE,150);
      analogWrite(B1BE,0);    
    }else{      
      analogWrite(B1AE,0);
      analogWrite(B1BE,0);     
    }

}

void front(){
  motorA('F');
  motorB('F'); 
  motorC('F');
  motorD('F');
  delay(2000);
}


void back(){
  motorA('B');
  motorB('B'); 
  motorC('B');
  motorD('B');
  delay(2000);
}

void right(){
  motorA('B');
  motorB('B'); 
  motorC('F');
  motorD('F');
  delay(2000);
}

void left(){
  motorA('F');
  motorB('F'); 
  motorC('B');
  motorD('B');
  delay(2000);
}

void loop() {
  motorA('F');
  /*motorB('F'); 
  motorC('F');
  motorD('F');
  delay(2000);*/
}



