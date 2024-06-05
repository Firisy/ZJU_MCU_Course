ORG 0000H
SJMP START
ORG 0030H
START:
MOV 30H,#63H    ;存储数据A
MOV 31H,#82H    ;存储数据B
MOV 32H,#0C5H   ;存储数据C
MOV 33H,#36H    ;存储数据D

MOV A,32H
CPL A       ;对C取反
ANL A,31H   ;C反 与 B 相与
XRL A,30H   ;与A异或
CPL A       ;取反
MOV 40H,A
MOV A,33H   
ORL A,30H   ;D或A
CPL A       ;取反
ANL A,40H   ;与40H相与
MOV 40H,A

HTOB:       ;十六进制表示转二进制
MOV R3,#08H
MOV R0,#50H
LOOP:
RLC A    ;取A的最高位
MOV R6,A
MOV A,R3
JNB ACC.0,SETHIGH   ;如果R3的最低位为0，跳转到SETHIGH，设置结果字节的高位
MOV A,#00H  ;设置结果字节的低位
MOV ACC.0,C ;将进位标志位C存入ACC.0
ORL A,@R0   ;将结果字节的低位与已经处理过高位的结果字节相或
MOV @R0,A
INC R0      ;指向下一个结果字节
SJMP NEXT
SETHIGH:
MOV A,#00H  ;设置结果字节的高位
MOV ACC.4,C ;将进位标志位C存入ACC.4
MOV @R0,A

NEXT:
MOV A,R6
DJNZ R3,LOOP


SJMP $
END


