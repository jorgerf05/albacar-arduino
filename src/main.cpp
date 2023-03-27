#include <Arduino.h>
#include <AFMotor.h>

#define US_TRIGGER 5
#define US_ECHO 6

// Motors
AF_DCMotor motor(1);
AF_DCMotor motor2(2);


int serial_input;


void setup()
{
  // Iniciamos comunicacion
  Serial.begin(9600);

  // Comunicacion del ultrasonico
  pinMode(US_TRIGGER, OUTPUT);
  pinMode(US_ECHO, INPUT);
  digitalWrite(US_TRIGGER, LOW);
}

void reversearObstaculo()
{
  // Reversa a 1/4 de velocidad hasta que lleguemos a 40 cm
  motor.run(BACKWARD);
  motor.setSpeed(150);
  delay(500);
  motor.run(RELEASE);
}

void handleInput(int input)
{

  Serial.println(input);

  switch (input)
  {

  case 0: // se deja de presionar los botones de acelaracion/reversa
    motor.run(RELEASE);
    break;

  case 1: // se deja de presionar los botones de direccion
    motor2.run(RELEASE);
    break;

  case 2: // Aceleracion
    motor.run(FORWARD);
    motor.setSpeed(150);
    break;

  case 5: // Reversa
    motor.run(BACKWARD);
    motor.setSpeed(150);
    break;

  case 4: // izquierda
    motor2.run(FORWARD);
    motor2.setSpeed(200);
    break;

  case 3: // dirección
    motor2.run(BACKWARD);
    motor2.setSpeed(200);
    break;

  case 6:
    motor.run(BACKWARD);
    motor.setSpeed(255);
    break;

  default: // si se recibe un byte desconocido se apagan los motores
    motor.run(RELEASE);
    motor2.run(RELEASE);
    break;
  }
}

long getDistance(){

  digitalWrite(US_TRIGGER, LOW);
  delayMicroseconds(10); // Enviamos un pulso de 10us
  digitalWrite(US_TRIGGER, HIGH);
  return pulseIn(US_ECHO, HIGH) / 59;
}

void loop()
{

  /*if (getDistance() <= 30){
    reversearObstaculo();
  } */

  // Traps until something is being received
  while (Serial.available() == 0){} 

  serial_input = Serial.read();
  handleInput(serial_input);
}