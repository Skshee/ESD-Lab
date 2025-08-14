    AREA RESET, CODE, READONLY
    EXPORT __Vectors

__Vectors
    DCD 0x10001000
    DCD Reset_Handler
    ALIGN
    AREA myCode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

Reset_Handler
    LDR R2, =NUM1
    LDR R3, =NUM2
    LDR R0, [R2]
    LDR R1, [R3]

Loop
    CMP R0, R1
    BEQ Storing
    SUBPL R0, R0, R1
    SUBMI R1, R1, R0
    B Loop

Storing
	LDR R5,= RESULT
	STR R0, [R5]
	
STOP 
	B STOP

NUM1 DCD 9
NUM2 DCD 15
	AREA mydata, DATA, READWRITE
RESULT DCD 0