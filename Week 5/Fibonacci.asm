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
    LDR     R0, =SRC
    LDR     R0, [R0]
    BL      FibonacciStack

    LDR     R1, =RESULT
    STR     R0, [R1]         ; Store result at RESULT

STOP
    B       STOP

FibonacciStack
    PUSH    {LR}
    CMP     R0, #0
    BEQ     FibZero
    CMP     R0, #1
    BEQ     FibOne

    MOV     R1, #0
    MOV     R2, #1
    MOV     R3, #2

FibLoop
    CMP     R3, R0
    BGT     FibDone

    ADD     R4, R1, R2
    PUSH    {R1, R2}
    MOV     R1, R2
    MOV     R2, R4
    POP     {R1, R2}

    ADD     R3, R3, #1
    B       FibLoop

FibDone
    MOV     R0, R2
    POP     {LR}
    BX      LR

FibZero
    MOV     R0, #0
    POP     {LR}
    BX      LR

FibOne
    MOV     R0, #1
    POP     {LR}
    BX      LR

SRC     DCD 10
RESULT  DCD 0             ; Memory location to store Fibonacci result

    AREA mydata, DATA, READWRITE

    END
