/*
 * Alissa Beckett
 * CS4308/03
 * Deliverable Two: Parser
 * 3/20/2020
 */


#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <fstream>
#include "scanner.h"

using namespace std;

void expr();
void term();


//<term> -> <factor> * <factor>
void expr()
{
	printf("Enter <term>\n");

	term();
	while (nextToken == MULTI_OP)
	{
		lex();
		term();
	}

	printf("Exit <term>\n");

}

//<factor> -> id | int_constant | (<expr>)
void term()
{
	printf("Enter <factor>\n");

	if (nextToken == IDENT || nextToken == INT_LIT)
		lex();
	else
		printf("Error\n");

	printf("Exit <factor>\n");
}
