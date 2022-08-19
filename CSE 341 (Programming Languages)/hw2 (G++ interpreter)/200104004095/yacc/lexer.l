%{

#include <stdio.h>
#include <string.h>
#include "y.tab.h"

short op_started = 0;







%}

%%

and		{ 		return KW_AND;		}
or		{ 		return KW_OR;		}
not		{ 		return KW_NOT;		}
equal	{		return KW_EQUAL;	}
less	{ 		return KW_LESS;		}
nil		{ 		return KW_NIL;		}
list	{		return KW_LIST;		}
append	{		return KW_APPEND;	}
concat	{		return KW_CONCAT;	}
set		{ 		return KW_SET;		}
deffun	{		return KW_DEFFUN;	}
defvar	{		return KW_DEFVAR;	}
for		{ 		return KW_FOR;		}
while	{ 		return KW_WHILE;	}
if 		{ 		return KW_IF;		}
exit	{ 		return KW_EXIT;		}
load	{ 		return KW_LOAD;		}
disp	{		return KW_DISP;		}
true	{ 		return KW_TRUE;		}
false	{ 		return KW_FALSE;	}
"+"		{ 		return OP_PLUS;		}
"-"		{ 		return OP_MINUS;	}
"/"		{ 		return OP_DIV;		}
"**"	{		return OP_DBLMULT;	}
"*"		{ 		return OP_MULT;		}
"("		{ 		return OP_OP;		}
")"		{ 		return OP_CP;		}
"“"		{	if(op_started)
			{ 
				op_started=0;
				return OP_CC;
			}
			else{
					op_started=1; 
					return OP_OC;
				} 
		}

"'"							{ 	 return QMARK;	}
","							{	return OP_COMMA;	}
;;.*\n? 					{	return COMMENT;		}

[1-9][0-9]*  				{	sscanf(yytext, "%d", &yylval.integer); 	return INTVALUE; 		}
[a-zA-Z][0-9a-zA-Z]*		{	strcpy(yylval.string, yytext);  return IDENTIFIER;     }
\t		{;}
" "		{;}	
\n	    {;}
.		{ fprintf(yyout,"SYNTAX_ERROR Expression not recognized\n>>"); }

[1-9][0-9]*\.[0-9]+ 		{	 sscanf(yytext, "%d", &yylval.integer);		return INTVALUE; 		}

%%

extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE *yyin,*yyout;

int yywrap(void){
	return 1;
}
/*
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
}*/