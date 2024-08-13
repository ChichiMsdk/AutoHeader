#ifndef TYPES_H
#define TYPES_H

#define MAX_TOKEN_SIZE 120

typedef enum TYPES
{
	VOID,
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	SIZE_T
}TYPES;

typedef struct t_token
{
	char str[MAX_TOKEN_SIZE];
	TYPES type;
}t_token;

#endif
