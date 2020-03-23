/*
 * Alissa Beckett
 * CS4308/03
 * Deliverable One: Scanner
 * 2/24/2020
 */


#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <fstream>
#include "parser.h"

using namespace std;



int main()
{
	err = fopen_s(&file_open, "basic.b", "r");
	
	if (err == 0)
	{
		getChar();
		do
		{
			lex();
			expr();
		} while (nextToken != EOF);
	}

	else
		printf("ERROR - cannot open input file \n");
}
