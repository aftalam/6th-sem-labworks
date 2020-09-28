        MOV SI , 1700H
        MOV CX , 0010H
        MOV AH , 00H
AHEAD1: CMP AH , [SI]
        JNB AHEAD
        MOV AH , [SI]
AHEAD:  INC SI
        LOOPNZ AHEAD1
        MOV [SI] , AH
        HLT
      