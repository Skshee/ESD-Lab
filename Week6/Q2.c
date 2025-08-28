#include<LPC17xx.h>

int main(){
	LPC_PINCON->PINSEL4 &= 0x03FFFFFF;
	LPC_PINCON->PINSEL5 &= 0xFFFFFC00;
	LPC_GPIO2 -> FIODIR = 0x007F8000;
	while(1){
		LPC_GPIO2 -> FIOSET = 0x007F8000;
		LPC_GPIO2 -> FIOCLR = 0x007F8000;
	}
}





	