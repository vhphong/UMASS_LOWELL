.data

inArr: .word	0:60
symTab:	.word	0:40
input:	.space	8

LOC:	.word	0x400


	.text
main:
	j getTokens
	
inLoop:	jal	getTokens

li	$t0,0	#ptr
lb	$s0, inArr + 12($0)
bne	$s0, ':'chVar

lw	$a0 , LOC
jal	hex2char

lw	$a0, inArr($0)
lw	$a1,inArr+4($s0)
  # $v0 has hex2char(LOC)
  li	$a2, 0x31
  jal	saveSymTab
  
  addi	$t0, $t0, 24
  
 chVar:
 	li	$t9,1	#isComma
 	addi	$t0, $t0 ,12
 	
 nextTok:
 	lb	$t1,inArr($t0)
 	beq	$t1, '#',dump
 	
 	beq	$t9,$0,noVar
 	lw	$t1,inArr+8($t0)
 	bne	$t1,2,noVar
 	
 	lw	$a0,LOC
 	jal	hex2char
 	
 	lw	$a0, inArr($0)
 	lw	$a1,inArr+4($0)
 	#$v0 has hex2char(LOC)
 	li	$a2, 0x30
 	jal	saveSymTab
 	
 noVar:
 	li	$t9,0
 	lb	$t1, inArr($t0)
 	bne	$t1, ',', noComma
 	li	$t9,1
 
 noComma:
 	addi	$t0,$t0,12
 	b	nextTok	
 dump:
 	jal	printSymTab
 	jal	clearInArr
 	b	inLoop
 	
 	
 getTokens:
 	jr	$ra
 	
 saveSymTab:	
 	jr	$ra
 	
 printSymTab:
 	jr	$ra
 
 clearInArr:
 	jr	$ra
 	
 	
 	.data
 saveReg:	.word	0:3
 
 	.text
 hex2char:
 	#save registers
 	sw	$t0, saveReg($0)	#hex digit to process
 	sw	$t1, saveReg+4($0)	#4-bit mask
 	sw	$t9, saveReg+8($0)
 	
 	li	$t1,0x0000000f	#$t1 : mask of 4bits
 	li	$t9,3		#t9: counter limit
 
 nibble2char:
 	and	$t0,$a0,$t1
 	
 	bgt	$t0,9, hex_alpha
 	addi	$t0,$t0,0x30
 	b	collect
 
 hex_alpha:	
 	addi	$t0,$t0,-10
 	addi	$t0, $t0, 0x61
 	
 collect:
 	sll	$v0,$v0,8
 	or	$v0,$v0,$t0
 	
 	srl	$a0,$a0,4
 	addi	$t9,$t9, -1
 	bgez	$t9, nibble2char
 	
 	sw	$t0,saveReg($0)
 	sw	$t1,saveReg+4($0)
 	sw	$t9,saveReg+8($0)
 	jr	$ra
 	
 exit:
 	li	$v0,10
 	syscall
 
 symACT0:
	lw	$t1, symTab+8($t8)
	sw	$s4, symTab+8($t8)
	b	varRealEnd
symACT1:
	lw	$t1, symTab+8($t8)
	sw	$s4, symTab+8($t8)
	b	varRealEnd
symACT2:
	lw	$t1, symTab+8($t8)
	b	varRealEnd
symACT3:
	la	$a0, error
	li	$v0, 4
	syscall
	li	$t1, -1
	b	varRealEnd
symACT4:
	sw	$s4, symTab+8($t8)
	li	$t1, -1
	b	varRealEnd
symACT5:
	sw	$s4, symTab+8($t8)
	li	$t1, 0
	b	varRealEnd
srchSymTab:
	sw	$t2, saveReg+4
	sw	$t3, saveReg+8
	sw	$t4, saveReg+12
	li	$t2, 0				# i index
	li	$t8, -1
startSearch:	
	bge	$t2, $t7, srchEnd
	lw	$t3, TOKEN
	lw	$t4, symTab($t2)
	bne	$t3, $t4, update
	lw	$t3, TOKEN+4
	lw	$t4, symTab+4($t2)
	bne	$t3, $t4, update
	add	$t8, $zero, $t2
	j	srchEnd
update:
	addi	$t2, $t2, 16
	b	startSearch
srchEnd:
	lw	$t2, saveReg+4
	lw	$t3, saveReg+8
	lw	$t4, saveReg+12
	jr	$ra

ACT1: 
	lb	$a0, inBuf($t5)			# $a0: next char
	jal	lin_search			# $s0: T (char type)
	addi	$t5, $t5, 1			# $t5++
	jr	$v1

ACT2:
	li	$s3, 0				# initialize index to TOKEN char 
	sb	$a0, TOKEN($s3)			# save 1st char to TOKEN
	addi	$t0, $s0, 0x30			# T in ASCII
	sb	$t0, TOKEN+10($s3)		# save T as Token type
	li	$t0, '\n'
	sb	$t0, TOKEN+11($s3)		# NULL to terminate an entry
	addi	$s3, $s3, 1
	jr 	$v1
	
ACT3:
	bgt	$s3, 7, lenError		# TOKEN length error
	sb	$a0, TOKEN($s3)			# save char to TOKEN
	addi	$s3, $s3, 1			# $s3: index to TOKEN
	jr	$v1	
lenError:
	li	$s0, 7				# T=7 for token length error
	jr	$v1
					
ACT4:
	lw	$t0, TOKEN($0)			# get 1st word of TOKEN
	sw	$t0, tokArray($a3)		# save 1st word to tokArray
	lw	$t0, TOKEN+4($0)		# get 2nd word of TOKEN
	sw	$t0, tokArray+4($a3)		# save 2nd word to tokArray
	lw	$t0, TOKEN+8($0)		# get Token Type
	sw	$t0, tokArray+8($a3)		# save Token Type to tokArray
	addi	$a3, $a3, 12			# update index to tokArray
	
	jal	clearTok			# clear 3-word TOKEN
	jr	$v1

RETURN:
	sw	$zero, tokArray($a3)		# force NULL into tokArray
	b	dump				# leave the state table

ERROR:
	la	$a0, st_error			# print error occurrence
	li	$v0, 4
	syscall
	b	dump

clearTok:
	li	$t1, 0x20202020
	sw	$t1, TOKEN($0)
	sw	$t1, TOKEN+4($0)
	sw	$t1, TOKEN+8($0)
	jr	$ra
	
printline:
	la	$a0, inBuf			# input Buffer address
	li	$v0,4
	syscall
	jr	$ra

printTokArray:
	la	$a0, tableHead			# table heading
	li	$v0, 4
	syscall

	la	$a0, tokArray			# print tokArray
	li	$v0, 4
	syscall

	jr	$ra


clearInBuf:
	li	$t0,0
loopInB:
	bge	$t0, 80, doneInB
	sw	$zero, inBuf($t0)		# clear inBuf to 0x0
	addi	$t0, $t0, 4
	b	loopInB
doneInB:
	jr	$ra
	

clearTokArray:
	li	$t0, 0
	li	$t1, 0x20202020			# intialized with blanks
loopCTok:
	bge	$t0, $a3, doneCTok
	sw	$t1, tokArray($t0)		# clear
	sw	$t1, tokArray+4($t0)		#  3-word entry
	sw	$t1, tokArray+8($t0)		#  in tokArray
	addi	$t0, $t0, 12
	b	loopCTok
doneCTok:
	jr	$ra
	


getline: 
	la	$a0, st_prompt			# Prompt to enter a new line
	li	$v0, 4
	syscall

	la	$a0, inBuf			# read a new line
	li	$a1, 80	
	li	$v0, 8
	syscall
	jr	$ra

lin_search:
	li	$t0,0				# index to Tabchar
	li	$s0, 7				# return value, type T
loopSrch:
	lb	$t1, Tabchar($t0)
	beq	$t1, 0x7F, charFail
	beq	$t1, $a0, charFound
	addi	$t0, $t0, 8
	b	loopSrch

charFound:
	lw	$s0, Tabchar+4($t0)		# return char type
charFail:
	jr	$ra


	
	
	.data

STAB:
Q0:     .word  ACT1
        .word  Q1   # T1
        .word  Q1   # T2
        .word  Q1   # T3
        .word  Q1   # T4
        .word  Q1   # T5
        .word  Q1   # T6
        .word  Q11  # T7

Q1:     .word  ACT2
        .word  Q2   # T1
        .word  Q5   # T2
        .word  Q3   # T3
        .word  Q3   # T4
        .word  Q0   # T5
        .word  Q4   # T6
        .word  Q11  # T7

Q2:     .word  ACT1
        .word  Q6   # T1
        .word  Q7   # T2
        .word  Q7   # T3
        .word  Q7   # T4
        .word  Q7   # T5
        .word  Q7   # T6
        .word  Q11  # T7

Q3:     .word  ACT4
        .word  Q0   # T1
        .word  Q0   # T2
        .word  Q0   # T3
        .word  Q0   # T4
        .word  Q0   # T5
        .word  Q0   # T6
        .word  Q11  # T7

Q4:     .word  ACT4
        .word  Q10  # T1
        .word  Q10  # T2
        .word  Q10  # T3
        .word  Q10  # T4
        .word  Q10  # T5
        .word  Q10  # T6
        .word  Q11  # T7

Q5:     .word  ACT1
        .word  Q8   # T1
        .word  Q8   # T2
        .word  Q9   # T3
        .word  Q9   # T4
        .word  Q9   # T5
        .word  Q9   # T6
        .word  Q11  # T7

Q6:     .word  ACT3
        .word  Q2   # T1
        .word  Q2   # T2
        .word  Q2   # T3
        .word  Q2   # T4
        .word  Q2   # T5
        .word  Q2   # T6
        .word  Q11  # T7

Q7:     .word  ACT4
        .word  Q1   # T1
        .word  Q1   # T2
        .word  Q1   # T3
        .word  Q1   # T4
        .word  Q1   # T5
        .word  Q1   # T6
        .word  Q11  # T7

Q8:     .word  ACT3
        .word  Q5   # T1
        .word  Q5   # T2
        .word  Q5   # T3
        .word  Q5   # T4
        .word  Q5   # T5
        .word  Q5   # T6
        .word  Q11  # T7

Q9:     .word  ACT4
        .word  Q1  # T1
        .word  Q1  # T2
        .word  Q1  # T3
        .word  Q1  # T4
        .word  Q1  # T5
        .word  Q1  # T6
        .word  Q11 # T7

Q10:	.word	RETURN
        .word  Q10  # T1
        .word  Q10  # T2
        .word  Q10  # T3
        .word  Q10  # T4
        .word  Q10  # T5
        .word  Q10  # T6
        .word  Q11  # T7

Q11:    .word  ERROR 
	.word  Q4  # T1
	.word  Q4  # T2
	.word  Q4  # T3
	.word  Q4  # T4
	.word  Q4  # T5
	.word  Q4  # T6
	.word  Q4  # T7
	
	
Tabchar: 
	.word ' ', 5
 	.word '#', 6
 	.word '$', 4 
	.word '(', 4
	.word ')', 4 
	.word '*', 3 
	.word '+', 3 
	.word ',', 4 
	.word '-', 3 
	.word '.', 4 
	.word '/', 3 

	.word '0', 1
	.word '1', 1 
	.word '2', 1 
	.word '3', 1 
	.word '4', 1 
	.word '5', 1 
	.word '6', 1 
	.word '7', 1 
	.word '8', 1 
	.word '9', 1 

	.word ':', 4 

	.word 'A', 2
	.word 'B', 2 
	.word 'C', 2 
	.word 'D', 2 
	.word 'E', 2 
	.word 'F', 2 
	.word 'G', 2 
	.word 'H', 2 
	.word 'I', 2 
	.word 'J', 2 
	.word 'K', 2
	.word 'L', 2 
	.word 'M', 2 
	.word 'N', 2 
	.word 'O', 2 
	.word 'P', 2 
	.word 'Q', 2 
	.word 'R', 2 
	.word 'S', 2 
	.word 'T', 2 
	.word 'U', 2
	.word 'V', 2 
	.word 'W', 2 
	.word 'X', 2 
	.word 'Y', 2
	.word 'Z', 2

	.word 'a', 2 
	.word 'b', 2 
	.word 'c', 2 
	.word 'd', 2 
	.word 'e', 2 
	.word 'f', 2 
	.word 'g', 2 
	.word 'h', 2 
	.word 'i', 2 
	.word 'j', 2 
	.word 'k', 2
	.word 'l', 2 
	.word 'm', 2 
	.word 'n', 2 
	.word 'o', 2 
	.word 'p', 2 
	.word 'q', 2 
	.word 'r', 2 
	.word 's', 2 
	.word 't', 2 
	.word 'u', 2
	.word 'v', 2 
	.word 'w', 2 
	.word 'x', 2 
	.word 'y', 2
	.word 'z', 2

	.word 0x7F, 0
