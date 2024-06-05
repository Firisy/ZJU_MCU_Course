ORG 0030H
SJMP START
ORG 0080H

START:

MOV DPTR,#TABLE ;DPTR指针指到TABLE位置
MOV P2,#0FFH ;设定P2为关机状态
MOV P0,#0FFH ;设定P0为关机状态
MOV R7,#020H ;设定R7为数据存储起始位置指针

LOOP2:
MOV A,R7
MOV R1,A      ;将R7的值赋给R1
MOV R2,#07FH  ;选择最高位为0，其余均为1，即只有最高位亮

MOV R5,#020H  ;设定R5为LOOP1循环次数，即一个数字排列亮灯的次数，R5，R6是双重循环，一个数字排列的亮灯次数为R5×R6
LOOP1:
MOV R6,#005H  ;设置LOOP3的次数，也就是说一个数字排列亮灯的次数
LOOP3:
MOV A,@R1     ;先设置亮灯的数字
MOVC A,@A+DPTR;从TABLE中取出对应的数字
MOV P0,A      ;亮灯数字
MOV A,R2      ;将要点亮的赋给A
RL A          ;A左移，代表现在设置亮灯的数字
MOV P2,A      ;亮灯
MOV R2,A      ;保存亮灯的数字
INC R1
CALL DELAY1   ;单独一个数字亮灯的时间
CJNE R1,#28H,CHANGED ;若R1增加到28H，则顺序执行
MOV R1,#20H          ;重新设置R1为20H
CHANGED:
DJNZ R6,LOOP3        ;LOOP3循环
DJNZ R5, LOOP1       ;LOOP1循环

INC R7               ;数字排列起始位置加1，则数字排列左移
CJNE R7,#28H,CHANGED2
MOV R7,#20H
CHANGED2:
SJMP LOOP2


DELAY1:
       MOV R3,#40H
       D1:
       MOV R4,#10H
       DJNZ R4,$
       DJNZ R3,D1
RET

TABLE:
DB 28H,7EH,0A2H,62H,74H,61H,21H,7AH,20H,60H

END
