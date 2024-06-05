ORG 0000H
SJMP MAIN
ORG 0080H

MAIN:
MOV R0,#8H     ;一共8位数据
MOV 30H,#00H   ;30H存储结果的低二位BCD码
MOV 31H,#00H   ;31H存储结果的高一位BCD码

LOOP:
     MOV A, R1   ;R1存储的是待转换的二进制码
     RLC A       ;取出最高位，在CY中
     MOV R1,A    
     MOV A,30H      ;30H存储结果的低二位BCD码(已经计算的部分)
     ADDC A,ACC     ;相当于将原BCD码×2，并加上CY中的新数据
     DA A           ;将结果转换为BCD码
     MOV 30H,A      ;存储新的低二位BCD码

     MOV A, 31H     ;31H存储结果的高一位BCD码(已经计算的部分)
     ADDC A,ACC     ;相当于将高位数据×2
     MOV 31H,A      ;存储新的高一位BCD码

     DJNZ R0,LOOP   ;循环8次

SJMP $

END



