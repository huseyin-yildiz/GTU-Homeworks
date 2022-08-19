.data
prompt: .asciiz "\n Please Input a value"
bye: .asciiz "\nBYE!"
		
.globl main
.text
main:
li $v0, 4 		# system call code for Print String
la $a0, prompt 		# load address of prompt into $a0
syscall 		# print the prompt message

li $v0, 5 		# system call code for Read Integer
syscall 		# reads the value into $v0

beq $v0, $zero, endForTakeInput # branch to end if $v0 = 0
move $a0, $v0                   #if you want to use this value, move to another register
#jal add, sub, etc.		#procedure usage
li $v0, 1 		  	# system call code for Print Integer
syscall		          	# print
j main 		        # go to main

#add: 
#.......
#jr

#sub:
#........
#jr

endForTakeInput: 
li $v0, 4 		# system call code for Print String
la $a0, bye 		# load address of msg. into $a0
syscall 		# print the string

exit:
li $v0, 10 		# terminate program run and
syscall 		# return control to system 
