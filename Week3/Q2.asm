    AREA RESET, DATA, READONLY
    EXPORT __Vectors

__Vectors
    DCD 0x10001000
    DCD Reset_Handler
    ALIGN

    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler
    LDR R0, =NUM1         
    LDR R1, =NUM2         
    LDR R6, =RESULT       
    MOV R7, #0            
    MOV R8, #4
	MSR 

ADD_LOOP
    LDR R2, [R0], #4      
    LDR R3, [R1], #4      
    SBCS R4, R2, R3
	SUB R8, R8, #1
	TEQ R3, #0
    BNE ADD_LOOP          

STOP
    B STOP                

NUM1 DCD 0x22222222, 0x33333333, 0x44444444, 0x55555555
NUM2 DCD 0x11111111, 0x22222222, 0x33333333, 0x44444444

    AREA mydata, DATA, READWRITE
RESULT DCD 0, 0, 0, 0     

    END