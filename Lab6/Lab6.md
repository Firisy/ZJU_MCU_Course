# Lab 6 定时器显示

## 一、 实验目的

## 二、

### 200Hz下

如果选择50us为时间间隔，则容易出现实际为64us

![image-20240421174108871](./assets/image-20240421174108871.png)

   MOV TH0,#0FFH
   MOV TL0,#0CEH



选择

   MOV TH0,#0FFH
   MOV TL0,#0DBH

刚好为50us

![scope_0](./assets/scope_0.png)

32 50%

4B 75%



![image-20240421182510216](./assets/image-20240421182510216.png)

![image-20240421182547265](./assets/image-20240421182547265.png)

