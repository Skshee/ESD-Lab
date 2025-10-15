// -----------------------------------------------------------------------------
// PROJECT: Proximity Detection Analyzer (LPC1768)
// -----------------------------------------------------------------------------
#include <LPC17xx.h>
#include <stdio.h>

// --- PIN DEFINITIONS ---
#define TRIG_PORT 1
#define TRIG_PIN  (1 << 20)
#define ECHO_PORT 1
#define ECHO_PIN  (1 << 21)
#define LED_PORT  1
#define LED_PIN   (1 << 22)

// --- CONSTANTS ---
#define THRESHOLD_CM 15.0f 
#define SPEED_OF_SOUND_CM_PER_US 0.0343f 

// --- EXTERNAL FUNCTIONS ---
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void LCD_init(void);
void LCD_print_line(int line, const char *str);
void LCD_clear(void);

// --- GPIO INITIALIZATION ---
void GPIO_init(void) {
    LPC_GPIO[TRIG_PORT]->FIODIR |= TRIG_PIN;
    LPC_GPIO[LED_PORT]->FIODIR  |= LED_PIN;
    LPC_GPIO[ECHO_PORT]->FIODIR &= ~ECHO_PIN; 
    LPC_GPIO[TRIG_PORT]->FIOCLR = TRIG_PIN;
    LPC_GPIO[LED_PORT]->FIOCLR  = LED_PIN;
}

// --- DISTANCE CALCULATION ---
float calculate_distance_cm(void) {
    uint32_t echo_start, echo_end, echo_duration;
    
    LPC_GPIO[TRIG_PORT]->FIOCLR = TRIG_PIN;
    delay_us(2);
    
    LPC_GPIO[TRIG_PORT]->FIOSET = TRIG_PIN;
    delay_us(10);
    LPC_GPIO[TRIG_PORT]->FIOCLR = TRIG_PIN;
    
    while(!(LPC_GPIO[ECHO_PORT]->FIOPIN & ECHO_PIN));
    echo_start = LPC_TIM0->TC;
    
    while(LPC_GPIO[ECHO_PORT]->FIOPIN & ECHO_PIN);
    echo_end = LPC_TIM0->TC;
    
    echo_duration = echo_end - echo_start;
    
    return (echo_duration * SPEED_OF_SOUND_CM_PER_US) / 2.0f;
}

// --- MAIN FUNCTION ---
int main(void) {
    float distance_cm;
    char lcd_buffer[17]; 
    
    GPIO_init();
    LCD_init(); 
    
    while (1) {
        distance_cm = calculate_distance_cm();
        
        sprintf(lcd_buffer, "Dist: %.1f cm", distance_cm);
        LCD_print_line(0, lcd_buffer);
        
        if (distance_cm > THRESHOLD_CM) { 
            sprintf(lcd_buffer, "STATUS: SAFE >%.0f", THRESHOLD_CM);
            LCD_print_line(1, lcd_buffer);
            LPC_GPIO[LED_PORT]->FIOCLR = LED_PIN; 
            delay_ms(500); 
        } else {
            LPC_GPIO[LED_PORT]->FIOSET = LED_PIN;
            sprintf(lcd_buffer, "WARNING! <=%.0f cm", THRESHOLD_CM);
            LCD_print_line(1, lcd_buffer);
            delay_ms(200); 
        }
    }
    return 0; 
}
