#include <AccelStepper.h>
#include <AFMotor.h>

char step;
boolean newData = false;
AF_DCMotor port(2); // create motor #2
AF_DCMotor starboard(1); // create motor #1
int time = 100;
int speed = 200;

void setup()
{
 Serial.begin(9600);
 Serial.println("<Arduino is ready>");

  port.setSpeed(speed);     // set the speed to 200/255
  starboard.setSpeed(speed);     // set the speed to 200/255
}

void loop() {
 recvOneChar();
 readDirection();
}

void recvOneChar() {
 if (Serial.available() > 0 && newData == false) {
 step = Serial.read();
 newData = true;
 }
}

void readDirection() {
 if (step=='r')
 {
  Serial.print("Go Right");
  //Right Command
  rotateRight();
  newData = false;
 }
 else if (step=='l')
 {
  Serial.print("Go Left");
  //Left Command
  rotateLeft();
  newData = false;
 }
 else if (step=='f')
 {
  Serial.print("Go Forward");
  //Fwd Command
  forward();
  newData = false;
 }
 else if (step=='b')
 {
  Serial.print("Go Back");
  //Back Command
  back();
  newData = false;
 }
newData = false;
}

void forward()
{
  port.run(RELEASE);
  starboard.run(RELEASE);
  port.run(FORWARD);
  starboard.run(FORWARD);
  //both wheels fwd
  delay(time);
  //coast for set time b/t DDR steps
}

void back()
{
  port.run(RELEASE);
  starboard.run(RELEASE);
  port.run(BACKWARD);
  starboard.run(BACKWARD);
  //both wheels bwd
  delay(time);
  //coast for set time b/t DDR steps
}

void rotateLeft()
{
  port.run(RELEASE);
  starboard.run(RELEASE);
  port.run(FORWARD);
  starboard.run(BACKWARD);
  //tank control style turning
  delay(time);
}

void rotateRight()
{
  port.run(RELEASE);
  starboard.run(RELEASE);
  port.run(BACKWARD);
  starboard.run(FORWARD);
}
