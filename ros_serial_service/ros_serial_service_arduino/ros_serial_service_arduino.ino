void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    char a = Serial.read();
    if(a == 'a'){
      digitalWrite(13, HIGH);
    }else if(a == 'b'){
      digitalWrite(13, LOW);
    }
  }
}
