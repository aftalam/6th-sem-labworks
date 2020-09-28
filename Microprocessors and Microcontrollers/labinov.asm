		ORG 0000H
		LJMP MAIN
		ORG 40H
MAIN:	MOV R0 , #40H
		MOV R3 , #08
		MOV R1 , #00H
		MOV @R0 , #00H
		INC R0
		MOV @R0 , #01H
		MOV R2 , #01H
LABEL2:	INC R0
		MOV A , R1
		ADD A , R2
		MOV @R0 , A
		MOV B , R2
		MOV R1 , B
		MOV R2 , A
		DJNZ R3 , LABEL2
		END
