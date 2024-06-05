org	0000h
	ajmp	main
	org	0080h
main:
	CPL	P3.3      ;取反小喇叭（p3.3)
	lcall	delay     ;调用延时
	ajmp	main      ;反复循环
delay:                    ;延时子程序
	mov	r7,#00h
LLA:	DJNZ	R7,LLA
	ret
end
