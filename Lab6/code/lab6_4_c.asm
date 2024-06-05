ORG 0000H
SJMP MAIN
ORG 000BH
AJMP TIME0
ORG 001BH
AJMP TIME1
ORG 0080H

MAIN:
    ; 初始化
    ; 启用定时器T0, 定时器T1
    MOV TMOD,#11H
    MOV TH0,#0XXH
    MOV TL0,#0XXH
    SETB EA
    SETB ET0
    SETB TR0

    MOV TH1,#0XXH
    MOV TL1,#0XXH

    SETB ET1
    SETB TR1

    MOV DPTR,#TABLE
SJMP $

TIME0:
    PUSH A
    PUSH PSW
    ;如果有按键按下，跳转到K1
    JNZ K1  
    ;如果没有按键按下，判断是什么情况下没有按下
    MOV A,30H   ;30H存储按键按下的次数
    JZ T0_END1   ;如果30H为0，则说明是没按过键，直接返回中断
    ;如果30H不为0，则判断30H的值，如果多次判断按下过按键，则开始进行Operate操作
    CJNE A,#02H,OPERATE 
    LJMP T0_END1
K1:
    ; 按键按下之后的操作
    INC 30H
    MOV A,30H

LK:
    ; 得到按键编号

T0_END1:
    POP PSW
    POP A
    RETI

OPERATE:
    MOV 30H,#00H    ;清零按键按下的次数
    ; 判断按键的值
    MOV A, 31H
    ;判断31H的值
    CJNE A,#08H,OPERATE1
    ; 取消键操作

    OPERATE1:CJNE A,#0BH,OPERATE2
    ; 确认键操作

    OPERATE2:CJNE A,#0CH,OPERATE3
    ; 左移键操作

    OPERATE3:CJNE A,#0FH,OPERATE4
    ; 右移键操作

T0_END:     ;Operate仍在T0中，所以需要返回中断
    POP PSW
    POP A
    RETI

;扫描显示数码管，
TIME1:
    PUSH A
    PUSH PSW
    ;扫描显示数码管，确定灯亮时间
    MOV TH1,#0XXH
    MOV TL1,#0XXH

    ;数码管左移
    MOV A,42H
    RL A
    MOV 42H,A
    MOV P2,A
    ;P0显示R1指向的值
    INC R1
    ;44H记录当前状态：FFH为计时;其他, 为调整界面状态 如0000 1000 调整 P2.3的显示管
    ;如果当前状态是计时,则需要时时更新时间
    ;使用函数ADJUST_TIME1，调整显示数据:
    MOVC A,@A+DPTR
    MOV P0, A
    LJMP ADJUST_TIME1
    ; 特殊状况，当前为调试模式，且R1指向被调整的位置
    ; 执行指针（一闪一闪）操作
    INC 43H ; 43H计时器
    CJNE A,#03EH,NEXT2_TIME1    ;如果等于3EH次，重新记次数
    MOV 43H,#00H
    SJMP COUNT
    NEXT2_TIME1:CJNE A,#01FH,NEXT3_TIME1    ;如果等于1FH次，灭灯
    MOV P0,#0FFH
    SJMP T1_END
    

T1_END:
    POP PSW
    POP A
    RETI

KS:
    MOV P1,#0FH ;将P1口的低四位设置为高电平
    MOV A,P1    ;将P1口的值赋给A,如果在这个瞬间有按键按下，A的值会改变
    XRL A,#0FH  ;将A与0FH异或，如果有按键按下，A的值不再是#01FH,最后结果A不为0
    RET
    ;2*
ADJUST_TIME1:
    ;时间进位操作
    MOV A,57H
    INC A
    MOV 57H,A
    CJNE A,#0AH,ADJUST_RET
    MOV 57H,#00H
    MOV A,56H
    INC A
    MOV 56H,A
    ; .......
    RET

TABLE:
DB 7EH,0A2H,62H,74H
DB 61H,21H,7AH,20H
DB 30H,60H,28H,25H,
DB 0A9H,0F7H,0A1H,0B1H

END