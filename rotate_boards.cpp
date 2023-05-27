#include <Servo.h>
Servo servoEngine1;
Servo servoEngine2;
Servo servoEngine3;
int pos;
void setup()
{
    servoEngine1.attach(2);
    servoEngine2.attach(3);
    servoEngine3.attach(4);
}

void loop()
{

    for (pos = 0; pos <= 180; pos++)
    {
        servoEngine1.write(pos);
        servoEngine2.write(pos);
        servoEngine3.write(pos);
        delay(150);
    }
    delay(1000);

    for (pos = 180; pos >= 0; pos--)
    {
        servoEngine1.write(pos);
        servoEngine2.write(pos);
        servoEngine3.write(pos);
        delay(150);
    }
    delay(1000);
}