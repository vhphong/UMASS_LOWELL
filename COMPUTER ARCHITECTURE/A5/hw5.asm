start:  lodd on:
        stod 4095			
        call xbsywt: 		
	
		loco str1: 		; prompting str1 to get the 1st number
		call nextw:		 
		call bgndig:		
		lodd binnum:	; loading ac with the 1st number
		stod total:		; storing the 1st number into total, total := number1
		
		loco str1:		; prompting str1 to get the 2nd number
		call nextw:
		call bgndig:
		lodd binnum:	; loading ac with the 2nd number
		addd total:		; adding two numbers, total := total + number2
		stod total:
		stod addRst:	; storing answer in addRst
		
		jneg over:		; if negative then jump to over for overflow handling

		call xbsywt:
		loco str2:		; if not overflow, prompt str2
		call nextw:
		call xbsywt:
		call result:	; call the result
		call xbsywt:
		lodd zero:		; reset ac to zero
		halt			 

over:	loco str3:		; if overflow then prompt str3
		call nextw:		
		lodd num:		; put num(-1) into AC
		halt

nextw:  pshi
        addd c1:
        stod pstr1:
        pop
        jzer crnl:
        stod 4094
        push
        subd c255:
        jneg crnl:
        call sb:
        insp 1
        push
        call xbsywt:
        pop
        stod 4094
        call xbsywt:
        lodd pstr1:
        jump nextw:
crnl:   lodd cr:
        stod 4094
        call xbsywt:
        lodd nl:
        stod 4094
        call xbsywt:
		retn
bgndig:	lodd on:		; mic1 program to print string
		stod 4093		; and scan in a 1-5 digit number
		call rbsywt:	; using CSR memory locations
		lodd 4092
		subd numoff:	; substract the numoff(48)
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
endnum: pop
		stod binnum:
        lodd 4092
        loco 0
		retn
xbsywt: lodd 4095
        subd mask:
        jneg xbsywt:
        retn
rbsywt: lodd 4093
        subd mask:
        jneg rbsywt:
        retn
sb:     loco 8
loop1:  jzer finish:
        subd c1:
        stod lpcnt:
        lodl 1
        jneg add1:
        addl 1
        stol 1
        lodd lpcnt:
        jump loop1:
add1:   addl 1
        addd c1:
        stol 1
        lodd lpcnt:
        jump loop1:
finish: lodl 1
        retn

result:	lodd on:
		stod 4095
		lodd num:		; put num(-1) into ac 
		push 			 
		lodd mask:		; put mask(10) into ac
		push     		

sum:	lodd addRst:	; put addRst into ac
		jzer output:	; call output if zero
		lodd mask:
		push
		lodd addRst:	; put addRst into ac
		push 
		div				; divide addRst by mask(10)
		pop			
		stod addRst:	; store into addRst
		pop				; pop the result
		insp 2			; clear up stack
		addd numoff:	; add numoff(48)
		push
		jump sum:		

output:	pop			
		jneg done:		; jump to done if negative
		stod 4094		
		call xbsywt:		
		jump output:		
done: 	retn 			; Return


numoff: 48
nxtchr: 0
binnum: 0
lpcnt:  0
mask:   10
on:     8
nl:     10
cr:     13
c1:     1
c255:   255
pstr1:  0
num:	-1
total:	0
addRst:	0
zero:	0
str1:   "PLEASE ENTER AN INTEGER BETWEEN 1 AND 32767."
str2:   "THE SUM OF THESE INTEGERS IS: "
str3:   "OVERFLOW, NO SUM POSSIBLE"OVERFLOW, NO SUM POSSIBLE"