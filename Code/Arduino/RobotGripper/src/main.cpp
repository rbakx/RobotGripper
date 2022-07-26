////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This is a demo program for the RobotGripper using the 'Arduino Uno' board.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <Servo.h>

const int NOF_ROBOTGRIPPER_SERVOS = 4;
const int ROBOTGRIPPER_SERVO_PINS[4] = {5, 6, 10, 11};

Servo robotGripperServo_0;
Servo robotGripperServo_1;
Servo robotGripperServo_2;
Servo robotGripperServo_3;

Servo robotGripperServos[4] = {robotGripperServo_0, robotGripperServo_1, robotGripperServo_2, robotGripperServo_3};

char message[80]; // To receive incomming messages.

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start of RobotGripper demo program!");

  for (int i = 0; i < NOF_ROBOTGRIPPER_SERVOS; i++)
    robotGripperServos[i].attach(ROBOTGRIPPER_SERVO_PINS[i]); // Attaches the servo to the servo object.
}

void loop()
{
  // put your main code here, to run repeatedly:
  int servoIndex;
  int servoAngle;
  static int messageIndex = 0; // Index of incoming message
  if (Serial.available() > 0)
  {
    char received = Serial.read();

    if (received == '\n') // Message is finished, so process message.
    {
      message[messageIndex] = '\0';                           // End of string.
      Serial.println("Message Received: " + String(message)); // Only for debugging.
      // TODO: Below fill in your own message handling.
      if (sscanf(message, "s%d %d", &servoIndex, &servoAngle) == 2)
      {
        robotGripperServos[servoIndex].write(servoAngle);
      }
      else
      {
        Serial.println("Unknown message: " + String(message));
      }
      messageIndex = 0; // Message is processed, so clear message.
    }
    else // Message is not finished yet, so add the received character to message.
    {
      message[messageIndex++] = received;
    }
  }
}