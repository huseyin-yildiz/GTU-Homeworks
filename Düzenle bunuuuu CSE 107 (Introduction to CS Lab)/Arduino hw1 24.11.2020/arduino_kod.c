void setup()
{
  Serial.begin(9600);		
  pinMode(13,OUTPUT);
}
void loop()
{
  char name[] = "Mehmet Huseyin YILDIZ";
  char greeting[] = "Hello world this is not my first arduino project :) ";	
  
  Serial.println(greeting);
  Serial.print("My name is ");
  Serial.write(name);

  while(true)
  {
    digitalWrite(13,HIGH);
    delay(200);
    digitalWrite(13,LOW);
    delay(200);
  }
  
}
