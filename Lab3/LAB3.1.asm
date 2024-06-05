ORG 0000H  
SJMP START  
ORG 0080H  
  
START:
MOV R1,#70H
MOV R4,#08H

MOV 0H, #01H

LOOP:
     MOV A, @R1
     INC A
     MOV R6,A
     MOV A, @R1
     ADD A, R6
     INC R1
     MOV @R1,A
DJNZ R4, LOOP 
     
END    
     


