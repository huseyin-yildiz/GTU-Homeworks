/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 20 "gpp_yacc.y" /* yacc.c:1909  */
                            // CODE AREA FOR BOTH LEXER FILE AND YAC FILE
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

#line 79 "y.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    KW_AND = 258,
    KW_OR = 259,
    KW_NOT = 260,
    KW_EQUAL = 261,
    KW_LESS = 262,
    KW_NIL = 263,
    KW_LIST = 264,
    KW_APPEND = 265,
    KW_CONCAT = 266,
    KW_SET = 267,
    KW_DEFFUN = 268,
    KW_FOR = 269,
    KW_WHILE = 270,
    KW_IF = 271,
    KW_EXIT = 272,
    KW_LOAD = 273,
    KW_DISP = 274,
    KW_TRUE = 275,
    KW_FALSE = 276,
    OP_PLUS = 277,
    OP_MINUS = 278,
    OP_DIV = 279,
    OP_DBLMULT = 280,
    OP_MULT = 281,
    OP_OP = 282,
    OP_CP = 283,
    OP_CC = 284,
    OP_OC = 285,
    OP_COMMA = 286,
    COMMENT = 287,
    KW_DEFVAR = 288,
    INTVALUE = 289,
    IDENTIFIER = 290,
    NEW_IDENTIFIER = 291,
    QMARK = 292
  };
#endif
/* Tokens.  */
#define KW_AND 258
#define KW_OR 259
#define KW_NOT 260
#define KW_EQUAL 261
#define KW_LESS 262
#define KW_NIL 263
#define KW_LIST 264
#define KW_APPEND 265
#define KW_CONCAT 266
#define KW_SET 267
#define KW_DEFFUN 268
#define KW_FOR 269
#define KW_WHILE 270
#define KW_IF 271
#define KW_EXIT 272
#define KW_LOAD 273
#define KW_DISP 274
#define KW_TRUE 275
#define KW_FALSE 276
#define OP_PLUS 277
#define OP_MINUS 278
#define OP_DIV 279
#define OP_DBLMULT 280
#define OP_MULT 281
#define OP_OP 282
#define OP_CP 283
#define OP_CC 284
#define OP_OC 285
#define OP_COMMA 286
#define COMMENT 287
#define KW_DEFVAR 288
#define INTVALUE 289
#define IDENTIFIER 290
#define NEW_IDENTIFIER 291
#define QMARK 292

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 55 "gpp_yacc.y" /* yacc.c:1909  */

    intList intLst;
    int integer;
    bool boolean;
    char string[max_word_length];
    

#line 173 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
