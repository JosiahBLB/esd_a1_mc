#include "instructions.h"

int main(void) {
    // setup
    cli(); // clear interrupts
    setupAdc();
    setupIo();
    setup16BitTimer();
    setupUsart();
    sei(); // set interrupts

    // main loop
    for (;;) {
        if (p_serialCom->instruction_ready) {
            saveBuffer();
            exeInst();
        }
    }
}
