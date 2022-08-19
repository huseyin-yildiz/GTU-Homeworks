# Sample MIPS program that writes to a new file. 
# Read from this file and print console.
##############################################
#Question for you:  Why does the string printing part print not only a sentence that read from a file?
##############################################

.data
str2: .space 45 
buffer: .asciiz "The quick brown fox jumps over the lazy dog.\n"
fout: .asciiz "testout.txt" # filename for output

.text
###############################################################
# Open (for writing) a file that does not exist
li $v0, 13 		# system call for open file
la $a0, fout 		# output file name
li $a1, 1 		# Open for writing (flags are 0: read, 1: write)
li $a2, 0		# mode is ignored
syscall 		# open a file (file descriptor returned in $v0)
move $s6, $v0 		# save the file descriptor
###############################################################
# Write to file just opened
li $v0, 15 		# system call for write to file
move $a0, $s6 		# file descriptor
la $a1, buffer 		# address of buffer from which to write
li $a2, 45	        # hardcoded buffer length
syscall 		# write to file
###############################################################
# Close the file
li $v0, 16 		# system call for close file
move $a0, $s6 		# file descriptor to close
syscall 		# close file
###############################################################
# Open (for reading) a file that does not exist
li $v0, 13 		# system call for open file
la $a0, fout 		# output file name
li $a1, 0 		# Open for writing (flags are 0: read, 1: write)
li $a2, 0		# mode is ignored
syscall 		# open a file (file descriptor returned in $v0)
move $s6, $v0 		# save the file descriptor

# Read from file just opened
li $v0, 14 		# system call for write to file
move $a0, $s6 		# file descriptor
la $a1, str2 		# address of buffer from which to write
li $a2, 45		# hardcoded buffer length
syscall 		# write to file

#print for reading part
la $a0, str2
li $v0, 4
syscall
###############################################################
# Close the file
li $v0, 16 		# system call for close file
move $a0, $s6 		# file descriptor to close
syscall 		# close file
