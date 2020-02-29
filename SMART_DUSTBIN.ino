#include<ESP8266WiFi.h>
#include<Servo.h>
Servo myservo;
const char*ssid="Vijayshri";
const char*password="NNNOOO!!!";
WiFiServer server(80);
const int trigPin=D0;
const int echoPin=D1;
long duration;
int distance;
//const char*s="ALERT!!!DUSTBIN FULL!!";
//const char*str="CLEARENCE NOT REQUIRED ...DUSTBIN IS STILL IN USABLE CONDITION";
void setup() {
  // put your setup code here, to run once:
  
myservo.attach(D2);
pinMode(D3,INPUT);
pinMode(D0,OUTPUT);
pinMode(D1,INPUT);
Serial.begin (9600);
WiFi.begin(ssid,password);
while(WiFi.status()!=WL_CONNECTED)
{
  Serial.println("_");
  delay(100);
  }
  IPAddress ip;
Serial.println("WiFi connected");
Serial.println("ssid");
Serial.println("WiFi address");
Serial.print("https://www.");
ip=WiFi.localIP();
Serial.println(ip);
server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client=server.available();
digitalWrite(trigPin,LOW);
delayMicroseconds(2);
digitalWrite(trigPin,HIGH);
delayMicroseconds(10);
digitalWrite(trigPin,LOW);

duration=pulseIn(D1,HIGH);
distance=duration*0.034/2;
client.println("HTTP/1.1 200 OK");
  client.println("content-type:text/html");
  client.println("connection:close");
  client.println("refresh:2");
   client.println();
if(distance<=5)
{
  
  client.println("<DOCTYPE HTML>");
     client.println("<HTML>");
      client.print("<P STYLE='TEXT-ALIGN:LEFT;'><SPAN STYLE='COLOR:#FF0000'><STRONG STYLE='FONT SIZE:LARGE;'>distance=</STRONG></SPAN></P>");
      client.println(distance);
      
      client.print("<P STYLE='TEXT-ALIGN:LEFT;'><SPAN STYLE='COLOR:#FF0000'><STRONG STYLE='FONT SIZE:LARGE;'>CONDITION=ALERT!!!DUSTBIN FULL!!...CLEARANCE REQUIRED</STRONG></SPAN></P>");
      client.print("</p>");
      client.print("</html>");
      delay(3000);
}
else
{
  
  client.println("<DOCTYPE HTML>");
     client.println("<HTML>");
      client.print("<P STYLE='TEXT-ALIGN:LEFT;'><SPAN STYLE='COLOR:#00FF00'><STRONG STYLE='FONT SIZE:LARGE;'>distance=</STRONG></SPAN></P>");
      client.println(distance);
      
      client.print("<P STYLE='TEXT-ALIGN:LEFT;'><SPAN STYLE='COLOR:#00FF00'><STRONG STYLE='FONT SIZE:LARGE;'>CONDITION=CLEARANCE NOT REQUIRED ...DUSTBIN IS STILL IN USABLE CONDITION</STRONG></SPAN></P>");
      client.print("</p>");
      client.print("</html>");
      if(digitalRead(D3)==LOW)
      {
        myservo.write(45);
  Serial.println("Open");
   Serial.print("Distance: ");
    Serial.println(distance);
    delay(7000);
  myservo.write(0);
  Serial.println("Close");
      }
      else
      {
        myservo.write(0);
        Serial.println("Close");
        delay(3000);
      }     
}
}
