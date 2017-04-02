#define laser_sensor 4
int ldr_sensor = A5;
#define red_led 7

int sensor_value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(laser_sensor, OUTPUT);
  pinMode(red_led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(laser_sensor, HIGH);
  sensor_value = analogRead(ldr_sensor);
  Serial.println(sensor_value);
  delay(100);

  
//  if(analogRead(laser_sensor) < 750){
//    digitalWrite(red_led, HIGH);
//  }else{
//    digitalWrite(red_led, LOW);
//  }
}
