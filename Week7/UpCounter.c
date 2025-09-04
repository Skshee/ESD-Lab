#include<stdio.h>
#include<LPC17xx.h>

int main(){
	unsigned char x=0;
	LPC_PINCON -> PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0 -> FIODIR |= 0x00000FF0;
	
	while(1){
		LPC_GPIO0 -> FIOPIN = x<<4;
		x = (x+1) % 256;
	}
}
