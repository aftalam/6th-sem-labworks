        CLC
        MOV CX , 0004H
        MOV SI , 1300H
        MOV DI , 130AH
AHEAD:  MOV AX , [SI]
        ADC [DI] , AX
        INC SI
        INC SI
        INC DI
        INC DI
        DEC CX
        JNZ AHEAD
        HLT
