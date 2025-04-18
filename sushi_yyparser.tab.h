/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     YY_SUSHI_AMP = 258,
     YY_SUSHI_BANG = 259,
     YY_SUSHI_BAR = 260,
     YY_SUSHI_CD = 261,
     YY_SUSHI_EXIT = 262,
     YY_SUSHI_HISTORY = 263,
     YY_SUSHI_JOBS = 264,
     YY_SUSHI_LESS = 265,
     YY_SUSHI_MORE = 266,
     YY_SUSHI_MOREMORE = 267,
     YY_SUSHI_PWD = 268,
     YY_SUSHI_SET = 269,
     YY_SUSHI_UNKNOWN = 270,
     YY_SUSHI_TOK = 271
   };
#endif
/* Tokens.  */
#define YY_SUSHI_AMP 258
#define YY_SUSHI_BANG 259
#define YY_SUSHI_BAR 260
#define YY_SUSHI_CD 261
#define YY_SUSHI_EXIT 262
#define YY_SUSHI_HISTORY 263
#define YY_SUSHI_JOBS 264
#define YY_SUSHI_LESS 265
#define YY_SUSHI_MORE 266
#define YY_SUSHI_MOREMORE 267
#define YY_SUSHI_PWD 268
#define YY_SUSHI_SET 269
#define YY_SUSHI_UNKNOWN 270
#define YY_SUSHI_TOK 271




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 7 "sushi_yyparser.y"
{
  bool b;
  int i;
  std::string *s;
  std::vector <std::string*> *s_vec;
  Program *p;
  Redirection redir;
}
/* Line 1529 of yacc.c.  */
#line 90 "sushi_yyparser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

