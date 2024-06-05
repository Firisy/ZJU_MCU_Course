;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 30H存储按键按下的次数，31H存储按键按下的值
; 0~7: 1~8
; 9: 9
; 10/0AH: 0
; 8: 取消
; 11/0BH: 确认
; 12/0CH: 左移
; 15/0FH: 右移
; 4H:如果是FFH，则是计数，否则是调整界面
; 43H:用作调整界面时的灯的计数，500微秒周期10个以后，
; 1S计时器
; 4AH,记录次数
; 4BH,记录1S钟的上限
; 单个小灯亮4ms
; 按键以2ms的时间间隔扫描
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ORG 0000H
SJMP MAIN
ORG 000BH
AJMP TIME0
ORG 001BH
AJMP TIME1
ORG 0080H

MAIN:
    MOV R1,#50H
    LOOP_MAIN:
    MOV @R1,#00H
    INC R1
    CJNE R1,#58H,LOOP_MAIN
    MOV R1,#50H
    MOV 52H,#0DH
    MOV 55H,#0DH

    MOV P2,#0FFH ;灯全灭
    MOV P0,#0FFH;P0口的显示值
    MOV 30H,#00H
    MOV 31H,#0FFH
    MOV TMOD,#11H
    MOV TH0,#0DAH
    MOV TL0,#0B4H
    SETB EA
    SETB ET0
    SETB TR0

    MOV TH1,#0F8H
    MOV TL1,#050H
    MOV 42H,#0FEH ;P2口的值
    MOV 43H,#00H
    MOV 44H,#01H
    MOV R0,#50H
    MOV 4AH,#0CH
    MOV 4BH,#0FEH
    SETB ET1
    SETB TR1
    MOV DPTR,#TABLE
SJMP $

;定时器0中断，扫描按键
TIME0:
    PUSH A
    PUSH PSW
    MOV TH0,#0DAH
    MOV TL0,#0B4H
    LCALL KS
    JNZ K1  ;如果有按键按下，跳转到K1
    ;如果没有按键按下，判断是什么情况下没有按下
    MOV A,30H
    JZ T0_END1   ;如果30H为0，返回中断
    CJNE A,#01H,OPERATE   ;如果30H不等于1，跳转到操作NEXT1_TIME0
    ;如果30H等于1，则将30H清零，返回中断
    MOV 30H,#00H
    LJMP T0_END1
K1:
    INC 30H
    MOV A,30H
    CJNE A,#02H,T0_END1  ;如果30H没两次，则返回中断
    ;30H判断按下两次，开始判断是哪一个被按下
    MOV P1,#0FH
    MOV A,P1
    CPL A
    ANL A,#0FH
    PUSH A

    MOV P1,#0F0H
    MOV A,P1
    CPL A
    ANL A,#0F0H
    MOV R4,A
    POP A
    ORL A,R4

LK:
    MOV R4,#00H
    PUSH A
LOOP:
    RRC A
    JC NEXT1
    INC R4
    CJNE R4,#04H,LOOP
    NEXT1:PUSH ACC
    MOV A,R4
    MOV B,#04H
    MUL AB
    MOV R5,A
    POP ACC

    POP ACC
    SWAP A
    MOV R4,#0H
LOOP2:
    RRC A
    JC NEXT2
    INC R4
    CJNE R4,#04H,LOOP2

    NEXT2:MOV A,R5
    ADD A,R4
    MOV 31H,A
    ; 返回中断

T0_END1:
    POP PSW
    POP A
    RETI

OPERATE:
    MOV 30H,#00H
    MOV 43H,#00H
    MOV A,44H
    CJNE A,#0FFH,NEXTX_OPERATE
    MOV R0,#50H
    MOV 44H,#01H

    NEXTX_OPERATE:
    MOV A, 31H
    ;判断31H的值
    CJNE A,#08H,OPERATE1
    MOV 44H,#01H
    MOV R0,#50H
    LOOP_OPERATE:
    MOV @R0,#00H
    INC R0
    CJNE R0,#58H,LOOP_OPERATE
    MOV R0,#50H
    MOV 52H,#0DH
    MOV 55H,#0DH
    LJMP T0_END
    OPERATE1:CJNE A,#0BH,OPERATE2
    MOV 44H,#0FFH
    MOV 4AH,#0CH
    MOV 4BH,#0FEH
    MOV TH1,#0F8H
    MOV TL1,#030H
    LJMP T0_END
    OPERATE2:CJNE A,#0CH,OPERATE3
    PUSH A
    MOV A,44H
    DEC R0
    RR A
    CJNE R0,#4FH,NEXT_OPERATE
    MOV R0,#57H
    SJMP CONTINUE_OPERATE
    NEXT_OPERATE:CJNE R0,#52H,NEXT2_OPERATE
    DEC R0
    RR A
    SJMP CONTINUE_OPERATE
    NEXT2_OPERATE:CJNE R0,#55H,CONTINUE_OPERATE
    DEC R0
    RR A
    CONTINUE_OPERATE:
    MOV 44H,A
    POP A
    LJMP T0_END

    OPERATE3:CJNE A,#0FH,OPERATE4
    PUSH A
    MOV A,44H
    INC R0
    RL A
    CJNE R0,#58H,NEXT_OPERATE2
    MOV R0,#50H
    SJMP CONTINUE_OPERATE2
    NEXT_OPERATE2:CJNE R0,#52H,NEXT2_OPERATE2
    INC R0
    RL A
    SJMP CONTINUE_OPERATE2
    NEXT2_OPERATE2:CJNE R0,#55H,CONTINUE_OPERATE2
    INC R0
    RL A
    CONTINUE_OPERATE2:
    MOV 44H,A
    POP A
    LJMP T0_END

    OPERATE4:CJNE A,#0AH,OPERATE5
    MOV @R0,#00H
    LJMP T0_END

    OPERATE5:JNC T0_END
    CJNE A,#04H,OPERATE7
    SJMP OPERATE6
    OPERATE7:
    JC OPERATE8
    CJNE R0,#53H,OPERATE10
    SJMP T0_END
    OPERATE10:
    CJNE R0,#56H,OPERATE8
    SJMP T0_END
    OPERATE8:
    CJNE A,#09H,OPERATE6
    MOV @R0,#09H
    LJMP T0_END
    OPERATE6:
    INC A
    MOV @R0,A

T0_END:
    POP PSW
    POP A
    RETI

;扫描显示罢了
TIME1:
    PUSH A
    PUSH PSW
    ;扫描显示数码管，一个灯亮2ms
    MOV TH1,#0F8H
    MOV TL1,#030H

    ;数码管左移
    MOV A,42H
    RL A
    MOV 42H,A
    MOV P2,A
    ;P0显示R1指向的值
    INC R1
    CJNE R1,#58H,NEXT_TIME1
    MOV R1,#50H
    ;如果当前状态是计数，且不是当前指针指向的位置，显示R1指向的值
    NEXT_TIME1:
    ANL A,44H
    JNZ  COUNT0
    ;特殊状况，当前为调试模式，且要显示被调试数43H在0~31之间，P0为R1指向的值，否则P0为FFH
    ;2*8*62=1 1s亮一下
    INC 43H
    MOV A,43H
    CJNE A,#03EH,NEXT2_TIME1
    MOV 43H,#00H
    SJMP COUNT
    NEXT2_TIME1:CJNE A,#01FH,NEXT3_TIME1
    MOV P0,#0FFH
    SJMP T1_END

    NEXT3_TIME1:JC COUNT
    MOV P0,#0FFH
    SJMP T1_END

    COUNT0:
    MOV A,44H
    CJNE A,#0FFH,COUNT
    LCALL ADJUST_TIME1
    COUNT:
    MOV A,@R1
    CJNE A,#00H,COUNT1
    MOV A,#0AH
    SJMP COUNT3
    COUNT1:
    CJNE A,#09H,COUNT2
    MOV A,#09H
    SJMP COUNT3
    COUNT2:
    CJNE A,#0DH,COUNT4
    MOV A,#0DH
    SJMP COUNT3
    COUNT4:
    DEC A
    COUNT3:
    MOVC A,@A+DPTR
    MOV P0, A

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
    MOV A,4AH
    ADD A,#01H
    MOV 4AH,A
    MOV A,4BH
    ADDC A,#00H
    MOV 4BH,A
    ;如果进位了，说明1S已经到了
    JC NEXT_ADJUST_TIME1
    RET
    NEXT_ADJUST_TIME1:
    MOV 4AH,#0CH
    MOV 4BH,#0FEH
    MOV A,57H
    INC A
    MOV 57H,A
    CJNE A,#0AH,ADJUST_RET
    MOV 57H,#00H
    MOV A,56H
    INC A
    MOV 56H,A
    CJNE A,#06H,ADJUST_RET
    MOV 56H,#00H
    MOV A,54H
    INC A
    MOV 54H,A
    CJNE A,#0AH,ADJUST_RET
    MOV 54H,#00H
    MOV A,53H
    INC A
    MOV 53H,A
    CJNE A,#06H,ADJUST_RET
    MOV 53H,#00H
    MOV A,51H
    INC A
    MOV 51H,A
    CJNE A,#04,NEXT_ADJUST
    MOV A,50H
    CJNE A,#02,ADJUST_RET
    MOV 50H,#00H
    MOV 51H,#00H
    NEXT_ADJUST:
    CJNE A,#0AH,ADJUST_RET
    MOV 51H,#00H
    ; MOV A,50H
    ; INC A
    ; MOV 50H,A
    ; CJNE A,#0AH,ADJUST_RET
    ; MOV 50H,#00H
ADJUST_RET:
    RET

TABLE:
DB 7EH,0A2H,62H,74H
DB 61H,21H,7AH,20H
DB 30H,60H,28H,25H,
DB 0A9H,0F7H,0A1H,0B1H

END