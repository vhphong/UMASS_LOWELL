bgndig:	lodd on:		; mic1 program to print string
	stod 4093		; and scan in a 1-5 digit number
	call rbsywt:		; using CSR memory locations
	lodd 4092
	subd numoff:		; substract the numoff(48)
	push
nxtdig:	call rbsywt:
	lodd 4092
	stod nxtchr:
	subd nl:
        jzer endnum:
	mult 10
	lodd nxtchr:
	subd numoff:
	addl 0
	stol 0
	jump nxtdig:
