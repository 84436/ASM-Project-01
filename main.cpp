﻿#include "QInt.h"

/*
	Đề bài:
	Định nghĩa lớp QInt, operator= và các ops khác để thao tác trên kiểu này.

	Input:
		base1 base2 num
		base [~ ROL ROR] num
		base num1 [+ - * / & | ^ << >>] num2
		Với:
			base : [2 | 10 | 16]
			num  : số biểu diễn dưới base đã cho
			base1 == base2 thì no-op ("không làm gì")
			<< : LSL
			>> : ASR
	
	Output:
		"không pad 0x0 / 0b0"
 */
