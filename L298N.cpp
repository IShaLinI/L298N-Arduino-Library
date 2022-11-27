/*

  L298N.h - Library for the L298N Motor Driver.

  Created by Andrew C Card, September 12, 2022.

  Released into the public domain.

*/

#include "Arduino.h"
#include "L298N.h"

/// @brief Create Motor Controlled by the L298N
/// @param gpioPin GPIO Pin
/// @param pwmPin  PWM Pin
L298N::L298N(int gpioPin1, int gpioPin2, int pwmPin){

    pinMode(gpioPin1, OUTPUT);
    pinMode(gpioPin2, OUTPUT);
    pinMode(pwmPin, OUTPUT);

    _gpioPin1 = gpioPin1;
    _gpioPin2 = gpioPin2;
    _pwmPin = pwmPin;

}

/// @brief Set motor speed 
/// @param speed Value -1 to 1
void L298N::set(double speed){

    if(_isInverted){
        speed *= -1;
    }

    _lastSet = speed;

    if(speed == 0 && _brakeMode){
        int16_t full_on = 255;  
        digitalWrite(PIN_IN1, LOW);
        digitalWrite(PIN_IN2,LOW);
        analogWrite(PIN_ENA_PWM, full_on);
        return
    }

    uint8_t direct = 0;    // forward
    if (speed < 0){
        direct = 1;        // reverse
    }

    switch (direct) {
        case 0:            // forward
            digitalWrite(PIN_IN1, HIGH);
            digitalWrite(PIN_IN2, LOW);
            analogWrite(PIN_ENA_PWM, speed * 255);
            break;
        case 1:            // reverse
            digitalWrite(PIN_IN1, LOW);
            digitalWrite(PIN_IN2, HIGH);
            analogWrite(PIN_ENA_PWM, -speed * 255);
            break;
    }

}

/// @return Last set value 
double L298N::get(){
    return _lastSet;
}

/// @param isInverted Whether or not to invert the motor
void L298N::setInverted(boolean isInverted){
    _isInverted = isInverted;
}

void L298N::setNeutralMode(boolean isBrake){
    _brakeMode = isBrake;
}

/// @return Motor invert state
boolean L298N::getInverted(){
    return _isInverted;
}

/// @brief Disables the motor
void L298N::disable(){
    set(0);
}

/// @brief Disables the motor
void L298N::stopMotor(){
    disable();
}

/// @return Motor Description 
String L298N::getDescription(){
    return "GPIO Pin1: {_gpioPin1} GPIO Pin2: {_gpioPin2} PWM Pin: {_pwmPin}";
}