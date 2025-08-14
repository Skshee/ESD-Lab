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
    LDR R0, =SRC
    MOV R2, #5
    LDR R1, =SRC + 36
	
Rev_Loop
	LDR R3, [R0]
	LDR R4, [R1]
	STR R3, [R1], #-4
	STR R4, [R0], #4
	SUBS R2, #1
	BNE Rev_Loop
	
STOP
    B STOP

	AREA mydata, DATA, READWRITE
SRC DCD 0x12345678, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF, 0x9ABCDEF1, 0xABCDEF12
    END
