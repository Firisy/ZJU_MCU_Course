ORG 0000H
SJMP START
ORG 0030H

START:
MOV R3, #10H   ;R3代表BCD码最高为16位
MOV R0, #40H   ;R0代表第一个BCD码的起始位置
MOV R1, #50H   ;R1代表第二个BCD码的起始位置
MOV R6, #60H   ;R6代表结果的起始位置
MOV R7,#00H    ;R7代表进位

LOOP:
     MOV A,@R0  ;将第一个BCD码的值取出
     ADD A,R7  ;加上进位
     ADD A,@R1 ;加上第二个BCD码的值
     DA A      ;十进制调整，此时的A的范围为#00H~#19H
     SWAP A    ;将A的高低四位进行交换
     MOV 71H,R1     ;将R1的值暂时存入71H
     MOV R1,#30H
     MOV @R1,#00H   ;将30H的值清零
     XCHD A,@R1     ;将结果的进位位存入30H
     SWAP A         ;将A的高低四位进行交换,即将结果的未进位部分放入地位
     MOV R1,71H     ;将R1的值恢复

     MOV 70H,R0     ;将R0的值暂时存入70H
     MOV 72H,A      ;将结果的未进位值暂时存入72H
     MOV A,R6       
     MOV R0,A       ;将R6的值存入R0
     MOV @R0,72H    ;将未进位结果存入R0
     MOV R0,70H     ;将R0的值恢复

     MOV R7,30H     ;将进位位存入R7
     INC R0
     INC R1
     INC R6
     DJNZ R3,LOOP   ;循环

SJMP $

END



