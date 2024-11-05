#include "instructions.h"

void setup(void);

int main(void) {

	setup();
    for (;;) {
        if (p_serialCom->instruction_ready)
        {
			saveBuffer();
            exeInst();
        }
    }
}

void setup(void) {
    cli();
    setupAdc();
    setupIo();
    setup16BitTimer();
    setupUsart();
    sei();
}