;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 50H 51H 时钟
; 53H 54H 分钟
; 56H 57H 秒钟
; #00H 设置秒钟（10秒钟）
; #01H 设置分钟（1分钟）
; #02H 设置时位（10分钟）
; #08H 归零
; 22H 记录是否50H~57H被归零
;   有数据：1   无数据：0
; #0BH 开始/暂停
; 30H 按键次数
; 42H 储存P2口的值(点亮的灯)
; 44H 记录当前状态
;       0FH 暂停
;       FFH 倒计时
;       00H 正计时
;       F0H 息屏模式
;       AAH DINGDINGDING
; 45H 记录10s息屏
; 46H 记录当倒计时结束以后，亮灯与否
; R0 记录当前指针位置，除去显示以外，使用R0进行记录
; R1 使用R1指针进行显示
; 0~9  0~9
; D  -
; 0 1 2 3 4 5 6 7
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ORG 0000H

SJMP MAIN
ORG 000BH
AJMP TIME0
ORG 001BH
AJMP TIME1
ORG 0080H

MAIN:
    MOV R1,#53H
    LOOP_MAIN:
    MOV @R1,#00H
    INC R1
    CJNE R1,#58H,LOOP_MAIN
    MOV R1,#53H
    MOV 42H,#0F7H
    ; MOV 52H,#0DH
    MOV 55H,#0DH
    CLR 22H

    MOV P2,#0FFH ;灯全灭
    MOV P0,#0FFH;P0口的显示值
    SETB P3.4
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


    MOV 44H,#0F0H
    MOV 45H,#00H
    MOV 46H,#0FFH
    MOV 4AH,#0CH
    MOV 4BH,#0FEH
    MOV DPTR,#TABLE
LOOP_SJMP:
    MOV A,44H
    CJNE A,#0AAH,NEXT_SJMP
	    CPL	P3.4      ;取反小喇叭（p3.3)
	    LCALL	DELAY     ;调用延时   ;反复循环
    NEXT_SJMP:
SJMP LOOP_SJMP

DELAY:                    ;延时子程序
    MOV	R7,#00H
    LLA:
        DJNZ R7,LLA
RET


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

; 处理按键编码
OPERATE:
    MOV 30H,#00H
    MOV A,44H
    MOV 45H,#00H
    CJNE A,#0AAH,NEXTXX_OPERATE
        MOV 44H,#0FH
        LJMP T0_END
    NEXTXX_OPERATE:
    CJNE A,#0F0H,NEXTX_OPERATE
    ; 息屏模式下
        MOV 44H,#0FH    ;调整为暂停模式
        SETB ET1
        SETB TR1
        MOV 42H,#0F7H ;P2口的值
        MOV R1,#53H
        LJMP T0_END
    NEXTX_OPERATE:
    MOV A, 31H
    ;判断31H的值
    ; 08H 归零
    CJNE A,#08H,OPERATE1
        CLR 22H
        MOV 44H,#0FH
        MOV R0,#53H
        LOOP_OPERATE:
        MOV @R0,#00H
        INC R0
        CJNE R0,#58H,LOOP_OPERATE
        MOV R0,#53H
        ; MOV 52H,#0DH
        MOV 55H,#0DH
        LJMP T0_END

    ; 0BH 开始/暂停
    OPERATE1:CJNE A,#0BH,OPERATE2
        MOV A,44H
        CJNE A,#0FH,NEXT1_OPERATE1
        ; 如果是暂停状态下
            JB 22H,NEXT2_OPERATE1
            MOV 44H,#00H
            SJMP CONTINUE_OPERATE1
            NEXT2_OPERATE1:
            MOV 44H,#0FFH
            CONTINUE_OPERATE1:
            MOV TH1,#0F8H
            MOV TL1,#030H
            LJMP T0_END
        ; 如果是计时状态下
        NEXT1_OPERATE1:
            MOV 44H,#0FH
            LJMP T0_END

    OPERATE2:
        SETB 22H
        CJNE A,#00H,OPERATE3
        MOV A,56H
        INC A
        MOV 56H,A
        CJNE A,#06H,T0_END
        MOV 56H,#00H
        SJMP JUDGEM1_OPERATE
    OPERATE3:CJNE A,#01H,OPERATE4
        JUDGEM1_OPERATE:
        MOV A,54H
        INC A
        MOV 54H,A
        CJNE A,#0AH,T0_END
        MOV 54H,#00H
        SJMP JUDGEM2_OPERATE
    OPERATE4:CJNE A,#02H,T0_END
        JUDGEM2_OPERATE:
        MOV A,53H
        INC A
        MOV 53H,A
        CJNE A,#0AH,T0_END
        MOV 53H,#00H
T0_END:
    POP PSW
    POP A
    RETI

;扫描显示数码管
TIME1:
    PUSH A
    PUSH PSW
    ;扫描显示数码管，一个灯亮2ms
    MOV TH1,#0F8H
    MOV TL1,#030H

    MOV A,4AH
    ADD A,#01H
    MOV 4AH,A
    MOV A,4BH
    ADDC A,#00H
    MOV 4BH,A
    ;如果进位了，说明1S已经到了
    MOV A,#00H
    MOV ACC.0,C
    PUSH A
    ; 此时栈顶是标志位C
    JNC NEXT8_TIME1
    MOV 4AH,#0CH
    MOV 4BH,#0FEH

    NEXT8_TIME1:
    ;数码管左移
    MOV A,42H
    RL A
    CJNE A,#0FEH,NEXT1_TIME1
        MOV  A,#0F7H
    NEXT1_TIME1:
    MOV 42H,A
    MOV P2,A
    ;P0显示R1指向的值
    INC R1
    CJNE R1,#58H,NEXT_TIME1
    MOV R1,#53H

    NEXT_TIME1:
    MOV A,44H
    CJNE A,#0AAH,NEXT6_TIME1
        POP A
        JZ NEXT7_TIME1
        MOV A,46H
        CPL A
        MOV 46H,A
        NEXT7_TIME1:
        MOV A,46H
        JZ NEXTY_TIME1
        MOV P2,#0FFH
        NEXTY_TIME1:
        LJMP DISPLAY
    NEXT6_TIME1:
    CJNE A,#0FH,NEXT2_TIME1
        POP A
        JZ NEXT3_TIME1
        MOV A,45H
        INC A
        MOV 45H,A
        CJNE A,#0AH,NEXT3_TIME1
        MOV 45H,#00H
        MOV 44H,#0F0H
        MOV P0,#0FFH
        MOV P2,#0FFH
        CLR TR1
        CLR ET1
        AJMP T1_END
        NEXT3_TIME1:
        SJMP DISPLAY
    ; 当前状态为倒计时
    NEXT2_TIME1:
    POP A
    ; 如果没进位
    JZ DISPLAY
    MOV A,44H
    ; 当前状态为正计时
    JZ ZHENG_OPERATE
    ; 当前状态为倒计时
    SJMP FU_OPERATE

    ZHENG_OPERATE:
        LCALL ZHENG_TIME1
        SJMP DISPLAY

    FU_OPERATE:
        LCALL FU_TIME1

    DISPLAY:
        MOV A,@R1
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
ZHENG_TIME1:
    MOV A,57H
    INC A
    MOV 57H,A
    CJNE A,#0AH,ZHENG_RET
    MOV 57H,#00H
    MOV A,56H
    INC A
    MOV 56H,A
    CJNE A,#06H,ZHENG_RET
    MOV 56H,#00H
    MOV A,54H
    INC A
    MOV 54H,A
    CJNE A,#0AH,ZHENG_RET
    MOV 54H,#00H
    MOV A,53H
    INC A
    MOV 53H,A
    CJNE A,#0AH,ZHENG_RET
    MOV 53H,#00H
ZHENG_RET:
    RET

FU_TIME1:
    MOV A,57H
    DEC A
    MOV 57H,A
    CJNE A,#0FFH,FU_RET
    MOV 57H,#09H
    MOV A,56H
    DEC A
    MOV 56H,A
    CJNE A,#0FFH,FU_RET
    MOV 56H,#05H
    MOV A,54H
    DEC A
    MOV 54H,A
    CJNE A,#0FFH,FU_RET
    MOV 54H,#09H
    MOV A,53H
    DEC A
    MOV 53H,A
    CJNE A,#0FFH,FU_RET
    MOV 53H,#00H
    MOV 54H,#00H
    MOV 55H,#0DH
    MOV 56H,#00H
    MOV 57H,#00H
    DINGDINGDING:
        MOV R1,#53H
        MOV 42H,#0F7H
        CLR P3.4
        MOV 44H,#0AAH
        CLR 22H
        MOV 46H,#0FFH
FU_RET:
    RET

TABLE:
DB 28H,7EH,0A2H,62H,74H
DB 61H,21H,7AH,20H,60H,
DB 30H,25H,
DB 0A9H,0F7H,0A1H,0B1H

END
