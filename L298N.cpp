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
L298N::L298N(int gpioPin, int pwmPin){

    pinMode(gpioPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);

    _gpioPin = gpioPin;
    _pwmPin = pwmPin;

}

/// @brief Set motor speed 
/// @param speed Value -1 to 1
void L298N::set(double speed){

    _lastSet = constrain(speed,-1,1);

    int _speed = round(_lastSet * 1000);
    _speed = (_isInverted) ? -_speed : _speed;

    map(_speed, -1000, 1000, -256, 255);
    
    uint8_t spd_bytes[2];

    spd_bytes[0] = (_speed >> 8) & 0x01;    // strip off direction bit (using 9th bit)
    spd_bytes[1] = _speed & 0xFF;           // obtain speed value from lower bits

    digitalWrite(_gpioPin,spd_bytes[0]);  // direction
    analogWrite(_pwmPin,spd_bytes[1]);   // speed value for PWM

}

/// @return Last set value 
double L298N::get(){
    return _lastSet;
}

/// @param isInverted Whether or not to invert the motor
void L298N::setInverted(boolean isInverted){
    _isInverted = isInverted;
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
    return "GPIO Pin: {_gpioPin}  PWM Pin: {_pwmPin}";
}