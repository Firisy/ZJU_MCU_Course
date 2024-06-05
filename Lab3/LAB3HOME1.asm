ORG 0000H
SJMP START
ORG 0030H

START:
MOV R0,#30H ;取出30H的值
MOV R1,#31H ;取出31H的值
XCH A, @R0  ;交换A和30H的值
SWAP A      ;交换A的高低位，即30H的高低位互换
XCH A,@R1   ;将变换后的30H放到31H的位置，并将31H的值放到A中
SWAP        ;再次交换A的高低位，即31H的高低位互换
XCH A,@R0   ;将变换后的31H放到30H的位置

SJMP $

END
