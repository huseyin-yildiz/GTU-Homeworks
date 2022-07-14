%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int yylex(void);
    void yyerror(char *);

    #ifndef MYBOOLEAN_H
        #define MYBOOLEAN_H
        #define false 0
        #define true 1
        typedef short bool; // or #define bool int
    #endif

    bool isList = 0;
    typedef struct intList intList;
%}

%code requires {                            // CODE AREA FOR BOTH LEXER FILE AND YAC FILE
#ifndef SHARED
    #define SHARED
    typedef struct intList{
        int* list;
        int len;
        int max;
    }intList;        // first is length 

    intList list;

    typedef short bool;
    
   #define max_word_length 30

    #define max_reserved_word_size 50
    #define max_word_length 30

    typedef struct {
        int size;
        char reservedWords[max_reserved_word_size][max_word_length];
        int valueTable[max_reserved_word_size];                     // Variable Table
        bool isFunc[max_reserved_word_size];                        // to determine if its a func or variable
        int paramSize[max_reserved_word_size];                      // to hold size of func parameter
    }identifiers;

    void newIntList(intList* intlist);
    void addItem(intList* intlist, int item);

    identifiers ids;


#endif
}

 %union {
    intList intLst;
    int integer;
    bool boolean;
    char string[max_word_length];
    
}

// tokens

%token KW_AND
%token KW_OR		
%token KW_NOT
%token KW_EQUAL
%token KW_LESS
%token KW_NIL
%token KW_LIST
%token KW_APPEND
%token KW_CONCAT
%token KW_SET
%token KW_DEFFUN
%token KW_FOR
%token KW_WHILE
%token KW_IF
%token KW_EXIT
%token KW_LOAD
%token KW_DISP
%token KW_TRUE
%token KW_FALSE
%token OP_PLUS
%token OP_MINUS
%token OP_DIV
%token OP_DBLMULT
%token OP_MULT
%token OP_OP
%token OP_CP
%token OP_CC
%token OP_OC
%token OP_COMMA
%token COMMENT
%token KW_DEFVAR
%token<integer> INTVALUE
%token<string> IDENTIFIER
%token<string> NEW_IDENTIFIER
%token QMARK

// types of non-terminals
%type<integer> EXPI
%type<boolean> EXPB
%type<intLst> VALUES LISTVALUE EXPLISTI IDENTIFIERS IDLIST



%%  // BNF
START: 
    | START INPUT                            {printf("\n>>");}       
    ;

INPUT:
    EXPI                    { if(!isList) printf("Syntax OK.\nResult: %d",$1); else {isList=false; printf("Syntax OK.\nResult:("); for(int i=0; i<list.len-1; i++)printf("%d ",list.list[i]); printf("%d)",list.list[list.len-1]);} }
    | EXPLISTI              { printf("Syntax OK.\nResult:("); for(int i=0; i<$1.len-1; i++)printf("%d ",$1.list[i]); printf("%d)",$1.list[$1.len-1]);  }
    | EXPB                  { char *str="false"; if($1)str="true"; printf("Syntax OK.\nResult: %s",str); }
    ;


LISTVALUE :
      QMARK OP_OP VALUES OP_CP                         { $$=$3; }
    | QMARK OP_OP OP_CP                               { newIntList(&$$); }
    | OP_OP KW_LIST VALUES OP_CP                     { $$ = $3; }
    ;

VALUES :
    VALUES EXPI                            { addItem(&$1,$2); $$ = $1; printf("val:%d",$2); }
    | EXPI                                 { newIntList(&$$); addItem(&$$,$1); printf("val:%d",$1);}
    ;


EXPI :                                      
    OP_OP OP_PLUS EXPI EXPI OP_CP           {$$ = $3 + $4;}
    | OP_OP OP_MINUS EXPI EXPI OP_CP        {$$ = $3 - $4;}
    | OP_OP OP_MULT EXPI EXPI OP_CP         {$$ = $3 * $4;}
    | OP_OP OP_DIV EXPI EXPI OP_CP          {$$ = $3 / $4;}
    | IDENTIFIER                            { $$=0; int index = lookup(&ids,$1); if(index==-1) printf("%s is not declared\n",$1 ); else  $$=ids.valueTable[index]; }
    | INTVALUE /* IntegerValue  */          {$$ = $1; printf("expi");}
    //| EXPI EXPI

//  ASSIGNMENT
    | OP_OP KW_SET IDENTIFIER EXPI OP_CP    { setId(&ids,$3,$4,false); $$=$4; }

// FUNCTIONS
    | OP_OP KW_DEFFUN IDENTIFIER IDLIST EXPLISTI OP_CP      { int i; if(i=lookup(&ids,$3)==-1){ setId(&ids,$3,$5,true); $$=0; ids.paramSize[i]=$4.len; }  else { printf("!! %s is defined before !\n",$3); $$=ids.valueTable[i];}  } // DEFINITION
    | OP_OP IDENTIFIER EXPLISTI OP_CP                       { int i; if(i=lookup(&ids,$2)==-1 ){ printf("!! %s is not defined\n",$2); }else if(!ids.isFunc[i]) printf("!! %s is not defined as a function\n",$2); else if($3.len != ids.paramSize[i]) printf("!! The function %s takes %d argument.\n",$2,ids.paramSize[i]);    } // CALL                   PREDEFINEDS MUST BE ADDED

    

// CONTROL STATEMENTS
    | OP_OP KW_IF EXPB EXPLISTI OP_CP                                       { if($3) { isList=true; list =$4; } else $$=0; }
    | OP_OP KW_IF EXPB EXPLISTI EXPLISTI OP_CP                              { isList=true; if($3)list =$4;  else list =$5;}
    | OP_OP KW_WHILE OP_OP EXPB OP_CP EXPLISTI OP_CP                        {  if($4) {isList=true;  list =$6; } $$=0; }
    | OP_OP KW_FOR OP_OP IDENTIFIER EXPI EXPI OP_CP EXPLISTI OP_CP      { isList=true; list = $8; }

//    OP_OP defvar Id EXPI OP_CP                // defining a variable
    | OP_OP KW_DEFVAR IDENTIFIER EXPI OP_CP                         { int i; if(i=lookup(&ids,$3)==-1){ setId(&ids,$3,$4,false); $$=$4; }  else { printf("%s is defined before !\n",$3); $$=ids.valueTable[i];} }                  // setting a variable
    ;

EXPB : 
    OP_OP KW_AND EXPB EXPB OP_CP            {$$ = $3 & $4;}
    | OP_OP KW_OR EXPB EXPB OP_CP           {$$ = $3 | $4;}
    | OP_OP KW_NOT EXPB OP_CP               {$$ = !($3); }
    | OP_OP KW_EQUAL EXPI EXPI OP_CP        {$$ = $3 == $4;}
    | OP_OP KW_EQUAL EXPB EXPB OP_CP        {$$ = $3 == $4;}
    
    //| BinaryValue
    | KW_TRUE                               {$$ = 1;}
    | KW_FALSE                              {$$ = 0;}
    ;

EXPLISTI :
    OP_OP KW_CONCAT EXPLISTI EXPLISTI OP_CP { for(int i=0; i<$4.len; i++) addItem(&$3,$4.list[i]); $$=$3;  }
    | OP_OP KW_APPEND EXPI EXPLISTI OP_CP   { addItem(&$4,$3); $$=$4; }
    | LISTVALUE                             { $$=$1; }
    | KW_NIL
    ;

IDLIST:
    OPENIDLIST OP_CP
    | OP_OP OP_CP
    ;

OPENIDLIST: 
     OPENIDLIST IDENTIFIER
    | OP_OP IDENTIFIER
    ;


%%

void yyerror(char *s) {
    fprintf(stderr, "SYNTAX_ERROR Expression not recognized\n");
}


 int lookup(identifiers* _identifiers,char identifier[]){        
        for(int i=0; i<_identifiers->size; i++)
        {
            if(strcmp(identifier,_identifiers->reservedWords[i]) == 0 )
                return i;
        }
        return -1;
    }

 int setId(identifiers *_identifiers,char identifier[],int value, int isFunc){
        int index = lookup(_identifiers,identifier);
        if(index == -1){
            index = _identifiers->size++;
            strcpy(_identifiers->reservedWords[index],identifier);
        }
        _identifiers->valueTable[index] = value;
        _identifiers->isFunc[index] = isFunc;
        return index;
 }


extern int yy_flex_debug;
int main(void) {
    printf(">>");
    //yy_flex_debug=1;
    yyparse();
    return 0;
}

void newIntList(intList* intlist){
        intlist->list = calloc(5, sizeof(int));
        intlist->max = 5;
        intlist->len = 0;
    }

    void addItem(intList* intlist, int item){
        if(intlist->max == intlist->len)
            {
                intlist->max *= 2;
                intlist->list = realloc(intlist->list,sizeof(int)*intlist->max);
            }

        intlist->list[intlist->len++] = item;
    }