#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#define HALF_STEP
#define ENABLE_PULLUPS
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Counter-clockwise step.
#define DIR_CCW 0x20

class Encoder
{
public:
    Encoder(uint8_t _pinClk, uint8_t _pinDt, uint8_t _pinSw);

private:
    const uint8_t pinClk, pinDt, pinSw, state;
};

#endif // ENCODER_H
