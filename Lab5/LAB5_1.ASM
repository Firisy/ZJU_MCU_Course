ORG 0030H
SJMP MAIN
ORG 0080H

MAIN:
MOV DPTR,#TABLE
LCALL KEY
MOVC A,@A+DPTR  ;将A指向的数据加上DPTR的值，将结果赋给A
MOV P0,A    ;将A的值赋给P0口,P0口的值就是A指向的数据
CLR P2.1    ;将P2.1口清零
LJMP MAIN

KEY:
LCALL KS
JNZ K1  ;如果有按键按下，跳转到K1
LCALL DELAY2
AJMP KEY

K1:
LCALL DELAY2
LCALL DELAY2
LCALL KS    ;再次检测是否有按键按下
JNZ K2      ;如果有按键按下，跳转到K2
AJMP KEY

K2:
MOV R2,#0EFH    ;将R2赋值为0EFH,即判断H1列的按键
MOV R4,#00H     ;将R4赋值为00H

K3:
MOV P1,R2       ;将R2的值赋给P1口

L0:
JB P1.0,L1    ;如果P1.0口的值为1，跳转到L1
MOV A,#00H     ;将A赋值为00H
AJMP LK

    L1:
    JB P1.1,L2
    MOV A,#04H
    AJMP LK

    L2:
    JB P1.2,L3
    MOV A,#08H
    AJMP LK

    L3:
    JB P1.3,NEXT
    MOV A,#0BH

    LK:
    ADD A,R4
    PUSH ACC

    K4:
    LCALL DELAY2    ;延时
    LCALL KS    ;再次判断是否
    JNZ K4      ;如果有键再次被按下，就再次重新判断，没有说明被松开
    POP ACC
    RET         ;跳回到main函数

KS:
MOV P1,#0FH ;将P1口的低四位设置为高电平
MOV A,P1    ;将P1口的值赋给A,如果在这个瞬间有按键按下，A的值会改变
XRL A,#0FH  ;将A与0FH异或，如果有按键按下，A的值不再是#01FH,最后结果A不为0
RET

NEXT:
INC R4
MOV A,R2
JNB ACC.7,KEY
RL A
MOV R2,A
AJMP K3

DELAY2:
MOV R5,#08H
L7:
MOV R6,#0FAH
L8:
DJNZ R6,L8
DJNZ R5,L7
RET

TABLE:
DB 28H,7EH,0A2H,62H
DB 74H,61H,21H,7AH,
DB 20H,60H,61H,74H,
DB 30H,62H,0A2H,7EH

END







