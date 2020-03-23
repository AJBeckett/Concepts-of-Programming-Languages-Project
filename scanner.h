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
#include <set>

using namespace std;

int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;

FILE *file_open;
errno_t err;

fstream file;
string word, filename;

void addChar();
void getChar();
void getString();
void getNonBlank();
int lex();

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

#define INT_LIT 10
#define IDENT 11
#define KEYWORD 12
#define ASSIGN_OP 20
#define ADD_OP 21
#define MULTI_OP 22
#define GREATER_THAN 23

enum KeyWords
{
	INVALID = -1,
	PROGRAM = 0,
	Let = 1,
	Print = 2,
	END = 100
};

static std::set<std::string> gKeyWords =
{
	"PROGRAM",
	"Let",
	"Print",
	"END"
};

int GetKeyword(char* pwzToken)
{
	auto it = gKeyWords.find(pwzToken);
	if (it != gKeyWords.end())
	{
		if (*it == "PROGRAM")
			return KeyWords::PROGRAM;
		if (*it == "Let")
			return KeyWords::Let;
		if (*it == "Print")
			return KeyWords::Print;
		if (*it == "END")
			return KeyWords::END;
	}
	return KeyWords::INVALID;
}

int lookup(char ch)
{
	switch (ch)
	{
	case '=':
		addChar();
		nextToken = ASSIGN_OP;
		break;

	case '+':
		addChar();
		nextToken = ADD_OP;
		break;

	case '*':
		addChar();
		nextToken = MULTI_OP;
		break;

	case '>':
		addChar();
		nextToken = GREATER_THAN;
		break;

	default:
		addChar();
		nextToken = EOF;
		break;
	}
	return nextToken;
}

void addChar()
{
	if (lexLen <= 98)
	{
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else
		printf("Error - lexeme is too long \n");
}

void getChar()
{
	if ((nextChar = getc(file_open)) != EOF)
	{
		if (isalpha(nextChar))
		{
			charClass = LETTER;
		}
		else if (isdigit(nextChar))
			charClass = DIGIT;
		else charClass = UNKNOWN;
	}
	else
		charClass = EOF;
}


void getNonBlank()
{
	while (isspace(nextChar))
		getChar();
}

int lex()
{
	KeyWords keyWord = KeyWords::INVALID;
	lexLen = 0;
	getNonBlank();
	switch (charClass)
	{
	case LETTER:
		addChar();
		getChar();
		while (charClass == LETTER || charClass == DIGIT)
		{
			addChar();
			getChar();
		}


		nextToken = IDENT;
		break;

	case DIGIT:
		addChar();
		getChar();
		while (charClass == DIGIT)
		{
			addChar();
			getChar();
		}
		nextToken = INT_LIT;
		break;

	case UNKNOWN:
		lookup(nextChar);
		getChar();
		break;

	case EOF:
		nextToken = EOF;
		lexeme[0] = 'E';
		lexeme[1] = 'O';
		lexeme[2] = 'F';
		lexeme[3] = 0;
		break;
	}

	if (keyWord == KeyWords::INVALID)
	{
		if (nextToken == IDENT)
		{
			printf("Next Token is: %d, Next lexeme is USER DEFINED %s \n", nextToken, lexeme);
		}
		else if (nextToken == INT_LIT)
		{
			int value = atoi(lexeme);
			printf("Next Token is: %d, Next lexeme is literal %d \n", nextToken, value);
		}
		else
		{
			char* pzOperator = nullptr;
			switch (nextToken)
			{
			case ASSIGN_OP:
				pzOperator = (char*)"Assignment";
				break;
			case ADD_OP:
				pzOperator = (char*)"Add";
				break;
			case MULTI_OP:
				pzOperator = (char*)"Multiply";
				break;
			case GREATER_THAN:
				pzOperator = (char*)"Greater Than";
				break;
			}
			printf("Next Token is: %d, Next lexeme is %s \n", nextToken, lexeme);
		}

	}
	else
	{
		printf("Next Token is: %d, Next lexeme is KEYWORD %s, %d \n", nextToken, lexeme, keyWord);
	}
	return nextToken;

}