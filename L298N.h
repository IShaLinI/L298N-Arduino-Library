/*

  L298N.h - Library for the L298N Motor Driver.

  Created by Andrew C Card, September 12, 2022.

  Released into the public domain.

*/

#ifndef L298N_h
#define L298N_h

#include "Arduino.h"


class L298N

{

  public:

    L298N(int gpioPin, int pwmPin);

    void set(double speed);
    double get();
    void setInverted(boolean isInverted);
    boolean getInverted();
    void disable();
    void stopMotor();
    String getDescription();


  private:
    int _gpioPin;
    int _pwmPin;
    double _lastSet;
    boolean _isInverted = false;

};

#endif
