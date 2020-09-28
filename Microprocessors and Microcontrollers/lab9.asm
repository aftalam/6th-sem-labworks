ORG 00H				;start from location 00H
MOV A , 00H			;	A = 00H
MOV R2 , #15		;	R2 = 15
MOV R3 , #10		;	R3 = 10
HERE: ADD A , R2	;	A = A + R2
DJNZ R3 , HERE		;decrement R3 & jump to label HERE
MOV 40H , A			;acumulator value stored at location 47H
END					;end of program
