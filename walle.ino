#define IN_1  16          // L298N in1 motors Rightx          GPIO15(D0)
#define IN_2  5          // L298N in2 motors Right           GPIO13(D1)
#define IN_3  0           // L298N in3 motors Left            GPIO2(D2)
#define IN_4  4           // L298N in4 motors Left            GPIO0(D4)

#define SP3 14   // Servo pin 1                    GPIO12(D5)
#define SP4 12   // Servo pin 2                    GPIO13(D6)

#define SP1 13   // Servo pin 1                    GPIO12(D7)left hand
#define SP2 15   // Servo pin 2                    GPIO13(D8)Right Hand

#define LED 2    //LED eyes GPIO2 (D4)



#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

Servo myservo1;
Servo myservo2;

Servo myservo3;
Servo myservo4;

String command;  // String to store app command state.
int angle1 = 90;  // Initial angle for servo 1 left
int angle2 = 90;  // Initial angle for servo 2 right

int angle3 = 100;
int angle4 = 100;

const char* ssid = "Wall-E";
ESP8266WebServer server(80);

void setup() {
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  pinMode(LED,OUTPUT);

  myservo1.attach(SP1);
  myservo1.write(angle1);

  myservo2.attach(SP2);
  myservo2.write(angle2);

  myservo3.attach(SP3);
  myservo3.write(angle3);


  myservo4.attach(SP4);
  myservo4.write(angle4);


  Serial.begin(115200);

  // Connecting WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Starting WEB-server
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
}

void moveservo(Servo &servo, int targetAngle) {
  int currentAngle = servo.read();
  if (currentAngle < targetAngle) {
    for (int angle = currentAngle; angle <= targetAngle; angle += 10) {
      servo.write(angle);
      
    }
    // Ensure the final position is reached
    servo.write(targetAngle);
  } else {
    for (int angle = currentAngle; angle >= targetAngle; angle -= 10) {
      servo.write(angle);
     
    }
    // Ensure the final position is reached
    servo.write(targetAngle);
  }
}





void gloweyes(){
   
  digitalWrite(LED, HIGH);
  
}

void closeeyes(){
  digitalWrite(LED, LOW);
  
}


void goAhead() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  Serial.print("forward");
}

void goBack() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  Serial.print("backward");
}

void goRight() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  Serial.print("right");
}

void goLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  Serial.print("left");
}

void goAheadRight() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  Serial.print("right forward");
}

void goAheadLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  Serial.print("left forward");
}

void goBackRight() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  Serial.print("right backward");
}

void goBackLeft() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  Serial.print("left backward");
}

void stopRobot() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

void righthandup() {
   
    moveservo(myservo1, 180);  // Set the new angle
  

}

void righthandmid() {
   myservo1.write(90);

}

void righthanddown() {

    moveservo(myservo1, 30);  // Set the new angle
  
}



void lefthandup() {
    
      moveservo(myservo2, 0);  // Set the new angle
}

void lefthandmid() {
      moveservo(myservo2, 90);

}

void lefthanddown() {
  
   moveservo(myservo2, 150);
  
}





void headup() {
    moveservo(myservo3, 0);
}

void headVmid(){
    moveservo(myservo3, 100);
}

void headdown() {
    moveservo(myservo3, 180);
}


void headleft() {
  moveservo(myservo4, 180);
}

void headHmid(){
    moveservo(myservo4, 100);
}

void headright() {
    moveservo(myservo4, 0);
}

void sayHi(){
  stopRobot();
  headHmid();
  headVmid();
  delay(200);
  righthandup();
  
}



void loop() {
  server.handleClient();

  command = server.arg("State");
  if (command == "F") goAhead();
  else if (command == "B") goBack();
  else if (command == "L") goLeft();
  else if (command == "R") goRight();
  else if (command == "FR") goAheadRight();
  else if (command == "FL") goAheadLeft();
  else if (command == "BR") goBackRight();
  else if (command == "BL") goBackLeft();

  else if (command == "RHU") righthandup();
  else if (command == "RHM") righthandmid();
  else if (command == "RHD") righthanddown();

  else if (command == "LHU") lefthandup();
  else if (command == "LHM") lefthandmid();
  else if (command == "LHD") lefthanddown();

  else if (command == "HL") headleft();
  else if (command == "HVM") headVmid();
  else if (command == "HR") headright();

  else if (command == "HU") headup();
  else if (command == "HHM") headHmid();
  else if (command == "HD") headdown();

  else if (command == "GLOW") gloweyes();
  else if (command == "GLOW") closeeyes();

  else if (command == "SAYHI") sayHi();
  else if (command == "SAYHI") sayHi();
  

  
  else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}
