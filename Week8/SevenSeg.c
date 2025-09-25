#include <LPC17xx.h>
#include <stdio.h>

unsigned char seven_seg[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

int main() {
    int i, j, n, number = 0, counter = 0;

    LPC_PINCON->PINSEL0 = 0;
    LPC_PINCON->PINSEL3 = 0;

    LPC_GPIO0->FIODIR |= 0xFF << 4;
    LPC_GPIO1->FIODIR |= 0x0F << 23;

    while (1) {
        n = number;
        for (i = 0; i < 4; i++) {
            LPC_GPIO1->FIOPIN = (i << 23);
            LPC_GPIO0->FIOPIN = (seven_seg[n % 10] << 4);
            n = n / 10;
            for (j = 0; j < 10000; j++);
        }
        counter++;
        if (counter == 250) {
            counter = 0;
            number = (number + 1) % 10000;
        }
    }
    return 0;
}
