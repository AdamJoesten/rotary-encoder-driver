#include "pico/stdlib.h"
#include "Encoder.h"

enum RotaryState : uint8_t
{
    R_START = 0x0,
    R_CCW_BEGIN = 0x1,
    R_CW_BEGIN = 0x2,
    R_START_M = 0x3,
    R_CW_BEGIN_M = 0x4,
    R_CCW_BEGIN_M = 0x5,
    R_CW_FINAL = 0x1,
    R_CW_NEXT = 0x3,
    R_CCW_FINAL = 0x5,
    R_CCW_NEXT = 0x6
};

#ifdef HALF_STEP
const unsigned char ttable[6][4] = {
    {R_START_M, R_CW_BEGIN, R_CCW_BEGIN, R_START},
    {R_START_M | DIR_CCW, R_START, R_CCW_BEGIN, R_START},
    {R_START_M | DIR_CW, R_CW_BEGIN, R_START, R_START},
    {R_START_M, R_CCW_BEGIN_M, R_CW_BEGIN_M, R_START},
    {R_START_M, R_START_M, R_CW_BEGIN_M, R_START | DIR_CW},
    {R_START_M, R_CCW_BEGIN_M, R_START_M, R_START | DIR_CCW},
};
#else
const unsigned char ttable[7][4] = {
    {R_START, R_CW_BEGIN, R_CCW_BEGIN, R_START},
    {R_CW_NEXT, R_START, R_CW_FINAL, R_START | DIR_CW},
    {R_CW_NEXT, R_CW_BEGIN, R_START, R_START},
    {R_CW_NEXT, R_CW_BEGIN, R_CW_FINAL, R_START},
    {R_CCW_NEXT, R_START, R_CCW_BEGIN, R_START},
    {R_CCW_NEXT, R_CCW_FINAL, R_START, R_START | DIR_CCW},
    {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};
#endif

Encoder::Encoder(uint8_t _pinClk, uint8_t _pinDt, uint8_t _pinSw)
    : pinClk(_pinClk), pinDt(_pinDt), pinSw(_pinSw), state(R_START)
{
    uint gpioInputMask = (1 << pinClk) | (1 << pinDt) | (1 << pinSw);
    gpio_init_mask(gpioInputMask);
#ifdef ENABLE_PULLUPS
    gpio_pull_up(pinClk);
    gpio_pull_up(pinDt);
    gpio_pull_up(pinSw);
#endif
};