#include<LPC17xx.h>

int main(){
	int i = 0;
	LPC_PINCON -> PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0 -> FIODIR = 0x00000FF0;
while(1){
	LPC_GPIO0 -> FIOSET = 0x00000FF0;
	for(; i<1000; i++);		
	LPC_GPIO0 -> FIOCLR = 0x00000FF0;
	for(; i<1000; i++);
	}
}
	
