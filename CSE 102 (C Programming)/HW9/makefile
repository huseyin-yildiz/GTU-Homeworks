target:	hw9

hw9_lib:	hw9_lib.h hw9_lib.c
			gcc -ansi -pedantic-errors -c hw9_lib.c

hw9_io:		hw9_lib hw9_io.c
			gcc -ansi -pedantic-errors -c hw9_io.c

hw9_main:	hw9_io hw9_main.c
			gcc -ansi -pedantic-errors -c hw9_main.c


hw9:	hw9_main hw9_lib hw9_io
		gcc hw9_lib.o hw9_io.o hw9_main.o -o hw9

clean:
		rm hw9