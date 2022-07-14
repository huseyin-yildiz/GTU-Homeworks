%{

#include <stdio.h>
#include <string.h>

short op_started = 0;

void print_write(char str[]){
    fprintf(yyout,"%s",str);
	printf("%s",str);
}




%}

%%

and		{print_write("KW_AND\n");  }
or		{print_write("KW_OR\n"); }
not		{print_write("KW_NOT\n"); }
equal	{print_write("KW_EQUAL\n");}
less	{print_write("KW_LESS\n"); }
nil		{print_write("KW_NIL\n"); }
list	{print_write("KW_LIST \n");}; 
append	{print_write("KW_APPEND\n");}
concat	{print_write("KW_CONCAT\n");}
set		{print_write("KW_SET\n"); }
deffun	{print_write("KW_DEFFUN\n");}
for		{print_write("KW_FOR\n"); }
if 		{print_write("KW_IF\n"); }
exit	{print_write("KW_EXIT\n"); }
load	{print_write("KW_LOAD\n"); }
disp	{print_write("KW_DISP\n");}
true	{print_write("KW_TRUE\n"); }
false	{print_write("KW_FALSE\n"); }
"+"		{print_write("OP_PLUS\n"); }
"-"		{print_write("OP_MINUS\n"); }
"/"		{print_write("OP_DIV\n"); }
"**"	{print_write("OP_DBLMULT\n"); }
"*"		{print_write("OP_MULT\n"); }
"("		{print_write("OP_OP\n"); }
")"		{print_write("OP_CP\n"); }
"“"		{if(op_started)
			{ 
				print_write("OP_CC\n");
				op_started=0;
			}
			else{
				op_started=1; 
				print_write("OP_OC\n");
				} 
		}


","		{print_write("OP_COMMA\n"); }
;;.*\n? {print_write("COMMENT\n"); }
[1-9][0-9]*\.[0-9]+ {print_write("VALUE\n");}
[1-9][0-9]*  	{print_write("VALUE\n"); }
[a-zA-Z][0-9a-zA-Z]*		{print_write("IDENTIFIER\n"); }
\t		{;}
" "		{;}	
\n	    {;}
.		{ printf("SYNTAX_ERROR %s cannot be tokenized\n", yytext);  fprintf(yyout,"SYNTAX_ERROR %s cannot be tokenized\n", yytext);}

%%

extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE *yyin,*yyout;

int yywrap(void){
	return 1;
}
int main(int argc, char const *argv[])
{

	if(argc == 1)
	{
		yyout=fopen("results.txt","w");
		while(yylex()){}
		
	}

	else
	{

		yyin = fopen(argv[1],"r");
		if(!yyin){
			printf("The file with this name can not found.\n");
		}
        else{
		    yyout=fopen("results.txt","w");
	
		    while(yylex()){}
		}
			
	}
	return 0;
}