.data

inputFileName: .asciiz "input.txt"			# Name of the input file
outputFileName: .asciiz "output.txt"			# Name of the output file
nums:	.ascii "0123456789"				# ascii numbers
comma:	.asciiz  ","					# comma

size_txt: .asciiz " size:"				# text of size

buffer: .space 32					# buffer for file reading
array: 
	.align 2
	.space 44					# memory for int array

seq_arr:	.word 1,1,1,1,1,1,1,1,1,1		# memory for seq result array
	
longest_seq:	.word 1,1,1,1,1,1,1,1,1,1		# memory for longest sequence
	
len:	.word						# to hold the length of the longest sequence

tmp:	.space 8					# for int to str operation

				
.text

###### main procedure ######
main:
la $a0,inputFileName	# input file name as parameter to the read_file procedure
jal read_file		# calls read_file procedure

jal str_to_array	# calls str_to_array procedure
move $s0,$v0		# str_to_array procedure returns the size.

jal print_buffer	# prints the buffer from file

move $a0,$s0		# size parameter to the sub_seq_arr procedure
jal sub_seq_arr		# calls sub_seq_arr procedure
move $s1,$v0		# saves the pointer of the array

lw $a0,len		# $a0 = length_of_longestsequence
move $a1,$s0		# $a1 = array size
jal store_longest_seq	# stores longest sequence to the mem.

move $a1,$s1		# size argument of the write_file procedure
jal write_file		# call of write_file procedure

jal print_results	# prints the result to the terminal

jal Exit		# End

###### End of main procedure ######



###### Print Results Procedure ######
print_results:

la $a0,outputFileName			# load address of the label outputFileName

move $t0, $ra				# saves the $ra pointer before procedure call
jal read_file				# reads the output file to the buffer
jal print_buffer			# prints the buffer
move $ra,$t0				# loads the $ra back

jr $ra					# return

###### End Of The Print Results Procedure ######







###### FILE READING procedure ######		
read_file:						# $a0 -> address of file		read string is saved to label named buffer
# open file
li $v0,13		# syscall openfile code 
li $a1,0		# read mode
li $a2,0		# ignore mode
syscall			# opens the file
move $s0, $v0	     	# save file descriptor 

# read from file
li $v0,14		# syscall code for reading
move $a0,$s0		# file descriptor as argument
la $a1,buffer		# setting the buffer
li $a2,50		# max char to read from file
syscall

# Close the file 
li   $v0, 16       # system call for close file
move $a0, $s0      # file descriptor to close
syscall            # close file
jr $ra
###### End of the FILE READING procedure ######




###### Writing the longest sequence to the out file ######
write_file:		# $a0 -> array address $a1 -> size	
move $t0,$a0		# $t0 -> array address
move $s6,$a1		# $s6 -> size


# open file
li $v0,13		# syscall openfile code 
la $a0,outputFileName	# filename
li $a1,1		# write mode
li $a2,0		# ignore mode
syscall			# opens the file
move $s0, $v0	     	# save file descriptor 

# write to file the results

li $s5,0		# $s5 -> i=0
la $s4,longest_seq	# $s4 -> longest_seq[0] pointer

wf_loop:
ble $s6,$s5,wf_exit

lw $t7,0($s4)		# $t7 = arr[i]
move $a0,$t7		# pointer of the array as parameter 
move $s7,$ra		# saves the $ra pointer
jal int_to_str		# calls the int_to_str procedure

move $ra,$s7		# loads back the saved $ra 
move $s7,$v0		# address of str
move $t7,$v1		# $t7 -> size of str

# write str to file 
move $a0,$s0		# $a0 -> file descriptor
move $a1,$s7		# $a1 -> addr. of text buffer
move $a2,$t7		# num. of char to write
li $v0,15		# syscall code for write_file
syscall

# write ','
la $a1,comma		# $a1 -> addr. of comma char
li $a2,1		# num. of char to write (1)
li $v0,15		# syscall code for write_file
syscall


addi $s5,$s5,1
addi $s4,$s4,4
j wf_loop		# jumps to the wf_loop

wf_exit:		# loope exit label

# write size of the longest sequence

move $a0,$s0
la $a1,size_txt		# addr. of text
li $a2,6		# $t7 -> size of str
li $v0,15		# syscall code for write_file
syscall

move $a0,$s6		# saves the size as parameter to the int_to_str procedure
move $s7,$ra		# saves the $ra pointer
jal int_to_str		# calls int_to_str procedure
move $ra,$s7		# loads the $ra pointer back
	
move $a0,$s0		# file descriptor
move $a1,$v0		# addr. of size str
move $a2,$v1		# $t7 -> size of str
li $v0,15		# syscall code for write_file
syscall


# Close the file 
li   $v0, 16		# system call for close file
move $a0, $s0		# file descriptor to close
syscall	           	# close file

jr $ra			# return

###### End of Writing the longest sequence to the out file ######






####### Store Longest Sequence #######
store_longest_seq:		# $a0 -> length_of_longest	$a1 -> array_size	# Stores the longest in the label longest_seq

move $t0,$a0			# $t0 -> current_index_of_longest_seq 	(initially length_of_longest)
move $t1,$a1			# $t1 -> array_size	

addi $t2,$t1,-1			# i = array_size-1
mul $t8,$t2,4			# i*4 (for indexing array)

la $t3,seq_arr			# result[0]
add $t3,$t8,$t3			# $t3 -> result[i] pointer

la $t4,array			# array[0]
add $t4,$t4,$t8			# $t4 -> array[i] pointer

mul $t8,$t0,4			# current_index * 4
la $t5,longest_seq		# longest_seq[0] 
add $t5,$t5,$t8			# $t5 -> longest_seq[index] pointer


sls_loop:
slt $t8,$t2,$zero		# $t8 -> (i < 0) 
beq $t8,1,sls_exit_loop		# loop exit condition

# loop inside

seq $t8,$t0,$a0			# current_index == length_of_longest

lw $t7,0($t5)
lw $t6,0($t4)
slt $t7,$t6,$t7			# path[index] > array[i]
or $t8,$t8,$t7			# current_index == length_of_longest || path[index] > array[i]
lw $t7,0($t3)
seq $t7,$t7,$t0			# result[i] == current_index
and $t8,$t8,$t7			# result[i] == current_index && ( current_index == length_of_longest || path[index] > array[i] )

beq $t8,$zero,sls_else		# if condition
lw $t8,0($t4)			# array[i]
sw $t8,-4($t5)			# path[index-1] = array[i]
addi $t0,$t0,-1			# index--
addi $t5,$t5,-4			# longest_seq[--index] pointer goes back
sls_else:			

# loop branch end commands
addi $t2,$t2,-1			# i--
addi $t3,$t3,-4			# result[--i] pointer goes back
addi $t4,$t4,-4			# array[--i] pointer goes back
j sls_loop			# jumps to the loop branch
sls_exit_loop:

jr $ra

####### End of thre Store Longest Sequence #######	




####### Int To String #######


int_to_str:			# $a0 -> int number  $v0 -> address $v1 -> size	Stores at tmp

move $t0,$a0			# $t0 -> number to convert
li $t1,0			# $t1 -> i=0
la,$t2,tmp+6			# str pointer (to store the string)
la,$t3,nums			# digits in ascii

itos_loop:
beq $t0,$zero,itos_exit		# n !=0 -> exit
li $t8,10			# 10 loading for mod
div $t0,$t8			# n % 10
mfhi $t8			# $t8 = remain(hi) (digit)

add $t8,$t3,$t8			# nums[remain]
lb $t8,0($t8)			
sb $t8,0($t2)
div $t0,$t0,10			# number /= 10
add $t2,$t2,-1			# str pointer decrement
add $t1,$t1,+1			# i++
j itos_loop

itos_exit:
sb $zero,0($t2)			# null pointer to end of str
addi $v0,$t2,1			# returns the address of the string
move $v1,$t1			# returns the size
jr $ra				# return


####### end of Int To String #######






########## sub seq arr procedure ##########	retrurns the sequence table(array)
sub_seq_arr:		# $a0 -> size 		$v0 -> length
move $t0,$a0		# $t0 -> size
li $t1,1		# max_index of sequences (length)
li $t2,0		# index i = 0

la $t5,array		# $t5 -> array[i]  pointer
la $t6,seq_arr		# $t6 -> seq[i] pointer
sub_seq_loop1:
slt $t4,$t2,$t0
beq $t4,$zero,end_loop1	# if i<size -> continues
li $t3,0		# index j = 0

la $t7,array		# $t7 -> array[j]  pointer
la $t8,seq_arr		# $t8 -> seq[j] pointer

sub_seq_loop2:
slt $t4,$t3,$t2			# condition loop2
beq $t4,$zero,end_loop2		# condition loop2 j < i

#first if
lw $s6,0($t7)
lw $s5,0($t5)
slt $s7,$s6,$s5			# array[i] > array[j]

lw $s6,0($t6)			# seq[i]
lw $s5,0($t8)			# seq[j]
sle $s6, $s6,$s5		# seq[j] >= seq[i]

and $s7,$s6,$s7			# anding conditions
beq $s7,$zero,else	# else situation to the sub_seq_loop2
#first if branch(single)
lw $s7,0($t8)			# seq[j]
addi $s7,$s7,1			# seq[j] + 1 
sw $s7,0($t6)			# seq[i] = seq[j] + 1

#second if
lw $s7,0($t6)			# loading seq[i] value to $s7
la $s6,seq_arr			# address of result
mul $t4,$t1,4			# address of max_index to point
add $s6,$s6,$t4			# seq[max_index] pointer
lw $s6,0($s6)
slt $t4,$s6,$s7			# seq[i] > seq[max_index]
beq $t4,$zero,else		# else situation to the end_loop2
lw $t1,0($t6)			# max_index = seq[i]

else:
addi $t3,$t3,1			# j++
addi $t7,$t7,4			# array[j] pointer increment
addi $t8,$t8,4			# seq[j] pointer increment
j sub_seq_loop2			# return to loop2 again


end_loop2:
addi $t2,$t2,1			# i++
addi $t5,$t5,4			# array[i] pointer increment
addi $t6,$t6,4			# seq[i] pointer increment
j sub_seq_loop1			# return to loop1 again


end_loop1:
move $v0,$t1			# returns the length of the longest sequence
sb $t1,len			# stores the length of the longest sequence
jr $ra
######## End of the sub_seq_arr procedure ########





######### Print the buffered text procedure #########
print_buffer:
li $v0,4			# syscall code for print string
la $a0,buffer			# buffered string as parameter
syscall				

li $v0,11			# syscall code to print char
li $a0,'\n'			# new line char to print
syscall				

jr $ra				# return

######### End of Print the buffered text procedure #########



########## String to array procedure ##########						A procedure for parsing string to int array
str_to_array:			# $a0 -> string address at mem.	  $v0 -> size
la $a0,buffer
li $t6,0			# size counter
move $t2,$a0			# string pointer
li $t0,0			# $t0 -> num	
la $t1,array			# $t1 -> int array pointer

strloop:
lb $t4,0($t2)			# $t4 -> fetched value from array pointer	
beq $t4,59,exitStrLoop		# exit when string pointer is at null	 59= ';'
beq $t4,44,strloopElse		# 44 = ','

# if
addi $t3,$t4,-48		# $t3 -> digit  char to digit '0'=-48
mul $t0,$t0,10			# num *= 10
add $t0,$t0,$t3			# num += digit
addi $t2,$t2,1			# index incrementing
j strloop

#else
strloopElse:
sw $t0,0($t1)			# storing the num at int array
addi $t1,$t1,4			# array pointer incrementing
and $t0,$t0,$zero			# num = 0
addi $t2,$t2,1			# index incrementing
addi $t6,$t6,1			# counter++
j strloop

exitStrLoop:
sw $t0,0($t1)			# storing the num at int array
addi $v0,$t6,1			# returns the array size
jr $ra				# return call

########## End of the str_to_array procedure ##########


########## Exit procedure ##########

Exit:
li $v0,10			# syscall code for termination
syscall

########## End of Exit procedure ##########
