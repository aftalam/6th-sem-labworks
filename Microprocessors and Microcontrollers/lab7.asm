        MOV SI , 1600H
        MOV BX , [SI]        
        DEC BX
AHEAD1: MOV CX , [SI]        
        DEC CX
        MOV SI , 1602H
AHEAD:  MOV AL , [SI]
        INC SI
        CMP AL , [SI]
        JNB AHEAD2
        XCHG AL , [SI]
        DEC SI
        MOV [SI] , AL
        INC SI
AHEAD2: LOOP AHEAD
        DEC BX
        MOV SI , 1600H
        JNZ AHEAD1
        HLT
