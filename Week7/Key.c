#include<stdio.h>
#include<LPC17xx.h>

int main(){
	unsigned char x = 0;	
	int count = 0;
	LPC_PINCON -> PINSEL0 &= 0xFF0000FF;
	LPC_PINCON -> PINSEL3 &= 0 << 23;
	LPC_GPIO0 -> FIODIR |= 0xFF << 4;
	LPC_GPIO1 -> FIODIR |= 0 << 23;
	
	while(1){
		x = LPC_GPIO1 -> FIOPIN & 1<<23;
		if (!x){
			count = (count + 1)%256;
			LPC_GPIO0 -> FIOPIN = count << 4; 
		}
	}
}