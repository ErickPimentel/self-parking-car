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
    digitalWrite(A1AD,LOW);
    digitalWrite(A1BD,HIGH); 
  }else if (d =='B'){
    digitalWrite(A1AD,HIGH);
    digitalWrite(A1BD,LOW);    
  }else{
    digitalWrite(A1AD,LOW);
    digitalWrite(A1BD,LOW);    
  }
}

void motorB(char d){
    if(d =='F'){
      digitalWrite(B1AD,LOW);
      digitalWrite(B1BD,HIGH); 
    }else if(d =='B'){
      digitalWrite(B1AD,HIGH);
      digitalWrite(B1BD,LOW);    
    }else{      
      digitalWrite(B1AD,LOW);
      digitalWrite(B1BD,LOW);     
    }

}

void motorC(char d){
  if(d =='B'){
    digitalWrite(A1AE,LOW);
    digitalWrite(A1BE,HIGH); 
  }else if (d =='F'){
    digitalWrite(A1AE,HIGH);
    digitalWrite(A1BE,LOW);    
  }else{
    digitalWrite(A1AE,LOW);
    digitalWrite(A1BE,LOW);    
  }
}

void motorD(char d){
    if(d =='B'){
      digitalWrite(B1AE,LOW);
      digitalWrite(B1BE,HIGH); 
    }else if(d =='F'){
      digitalWrite(B1AE,HIGH);
      digitalWrite(B1BE,LOW);    
    }else{      
      digitalWrite(B1AE,LOW);
      digitalWrite(B1BE,LOW);     
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
  front();
  delay(2000);
  back();
  delay(2000);
  right();
  delay(2000);
  left();
  delay(2000);
   
}


