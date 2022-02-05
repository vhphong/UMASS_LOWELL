start:  lodd on:
        stod 4095			
        call xbsywt: 		
	
	loco str1: 		; print out the first string
	call nextw:		 
	call bgndig:		
        lodd binnum:		; put first number into ac
	stod total:		; store the first number into total
	
	loco str1:		; print out the first string to get the second number
	call nextw:		
	call bgndig:		
	lodd binnum:		; put second number into ac
	addd total:		; add two numbers
	stod total:
	stod addRst:		; Store answer in addRst
	
	jneg over:		; If negative we got an overflow

	call xbsywt:	         
	loco str2:		; if not overflow, print out the second string	
	call nextw:		
	call xbsywt:	        
	call result:		; call the result
	call xbsywt:		
	lodd zero:		; put zero into AC
	halt			 

over:	loco str3:		; print out the third string for overflow result
	call nextw:		
	lodd num:		; put num(-1) into AC
	halt 			

finish: lodl 1			
        retn

result:	lodd on:
	stod 4095
	lodd num:		; put num(-1) into ac 
	push 			 
	lodd mask:		; put mask(10) into ac
	push     		

sum:	lodd addRst:		; put addRst into ac
	jzer output:		; call output if zero
	lodd mask:
	push			
	lodd addRst:		; put addRst into ac
	push 
	div			; divide addRst by mask(10)
	pop			
	stod addRst:		; store into addRst
	pop			; pop the result
	insp 2			; clear up stack
	addd numoff:		; add numoff(48)
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
str1:   "Please enter an integer between 1 and 32767."
str2:   "The sum of these integers is: "
str3:   "Overflow no sum possible"