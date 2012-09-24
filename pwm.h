#include <inttypes.h>
#include <Arduino.h>

struct pwm_mode {
    unsigned com : 2,
             wgm : 4,
             cs : 3,
             icnc : 1,
             ices : 1;
};

struct pwm_chan {
    volatile uint16_t &OCR;
    unsigned which : 2, // A = 0, B = 1, C = 2
             pin : 6;
             
    const struct pwm_mode &mode;
    volatile uint8_t &TCCRxA;
    volatile uint8_t &TCCRxB;
};

inline void pwmMode(
            volatile uint8_t &TCCRxA,
            volatile uint8_t &TCCRxB,
            const uint8_t which,
            const struct pwm_mode &mode) {
    
    uint8_t wgm_hi = (mode.wgm & 0x0C) << 1;
    uint8_t wgm_lo =  mode.wgm & 0x03;

    uint8_t com_shift = 6 - 2 * which;
    uint8_t com_mask    = 0x3      << com_shift;
    uint8_t com_shifted = mode.com << com_shift;

    TCCRxA = TCCRxA & 0xFC & ~com_mask | wgm_lo | com_shifted;
    TCCRxB = (mode.icnc << 7) | (mode.ices << 6) | wgm_hi | mode.cs;
}

inline void setupPWM(const struct pwm_chan &chan) {
    pinMode(chan.pin, OUTPUT);
    pwmMode(chan.TCCRxA, chan.TCCRxB, chan.which, chan.mode);
}

inline void setPWM(const struct pwm_chan &chan, uint16_t level) {
    chan.OCR = level;
}