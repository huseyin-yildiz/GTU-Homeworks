target:	hw5

hw5_lib:	hw5_lib.h hw5_lib.c
			gcc -ansi -pedantic-errors -c hw5_lib.c

hw5_main:	hw5_lib.h hw5_main.c
			gcc -ansi -pedantic-errors -c hw5_main.c


hw5:	hw5_main hw5_lib
		gcc hw5_lib.o hw5_main.c -lm -o hw5

clean:
		rm hw5