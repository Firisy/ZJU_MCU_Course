ORG 0000H  
SJMP START  
ORG 0030H  
  
START:
MOV R0,#8H
MOV 30H,#00H
MOV 31H,#00H

LOOP:
     MOV A, 30H
     SETB CY
     ADDC A,ACC
     DA A
     MOV 30H,A
     
     MOV A, 31H
     ADDC A,ACC
     MOV 31H,A
     
     DJNZ R0,LOOP

SJMP $
     
END    
     


