#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // pmode for umask
#include <stdbool.h>
#include <ctype.h>

#define KB 1024
#define MB KB * 1000
// this must contain whole char by whole char .. (idk how)!
#define READ_SIZE (sizeof(char) * 100)

// error msg
char msg_file_line[1024];
size_t g_alloc_size = 0;

// read vs fread = speed ?
// take a c file, read through it entirely and spot the functions.
// maybe using treesitter/compiler to find them ?
// mini parser/lexer ?
// TYPES: INT CHAR VOID LONG UNSIGNED * MACROS
// delimited by SPACE or NEWLINE

void
strjoin(char *s1, char *s2, size_t size)
{
	strncat(s1, s2, size);
}

char *
get_file_content(char *fname, size_t *size)
{
	int bytes_r;
	size_t buflen = 0;

	// allocates 1 MB cuz fuck it
	// don't trust calloc to find null terminating byte !
	char *total_buf = calloc(MB, sizeof(char));
	if (!total_buf) { fprintf(stderr, "failed allocating memory!\n"); exit(1); }

	// + 1 to null terminate it
	char buf[READ_SIZE + 1];

	int fd = _open(fname, _O_RDONLY);
	if (fd == -1)
	{
		sprintf(msg_file_line, "[DEBUG] %s: %d",__FILE__, __LINE__);
		perror(msg_file_line);
		exit(1);
	}
	while ((bytes_r = _read(fd, buf, READ_SIZE)) > 0)
	{
		buf[bytes_r] = 0;
		buflen += bytes_r;
		if (buflen >= MB)
		{
			total_buf = realloc(total_buf, buflen * 2);
			if (!total_buf)
			{
				fprintf(stderr, "Failed to realloc!\n");
				exit(1);
			}
		}
		strjoin(total_buf, buf, bytes_r);
	}

	if (bytes_r < 0)
	{
		sprintf(msg_file_line, "[DEBUG] %s: %d",__FILE__, __LINE__);
		perror(msg_file_line);
		_close(fd);
		free(total_buf);
		exit(1);
	}
	_close(fd);
	*size = buflen;
	return total_buf;
}

int
skip_line(char *fcontent, int index)
{
	int i = 0;
	while (fcontent[index + i] && fcontent[index + i] != '\n')
		i++;
	return index + i;
}

bool
is_there_semi_colon(char *line, int id)
{
	int i = 0;
	while (line[id + i] && line[id + i] != '\n')
	{
		if (line[id + i] == ';')
			return true;
		i++;
	}
	return false;
}

#define MAX_PARAM 127 // c standard
#define NAME_LENGTH 256 // arbitrary
#define MAX_FUN 500

// accounts for each space between params, parenthesis and semi-colon
#define ARBITRARY_LENGTH (MAX_PARAM * NAME_LENGTH) + MAX_PARAM + 3

/* 
 * This is sensitive to trailing spaces, two spaces or more in a row just fucks it up
 * Same goes for '{' not after a '\n'
 * Eg:	fn(int a){
 * 		}
 * 		will not work
 */
int
get_functions(char *fcontent, int index)
{
	int i = 0;
	bool fun = false; // found a function
	int check = 0;

	/* char function[MAX_FUN][ARBITRARY_LENGTH]; */
	char **function = malloc(MAX_FUN * (sizeof(char*)));
	for (int i = 0; i < MAX_FUN; i++)
	{
		function[i] = malloc(ARBITRARY_LENGTH * sizeof(char));
	}
	int j = 0;
	int k = 0;

	while (fcontent[index] && !fun)
	{
		if (!isalpha(fcontent[index]))
		{
			index = skip_line(fcontent, index);
		}
		else if (is_there_semi_colon(fcontent, index))
		{
			index = skip_line(fcontent, index);
		}
		else
		{
			// now it MUST be a function
			// if no parenthesis, must be on next line
			while (fcontent[index] && fcontent[index] != '{')
			{
				if (fcontent[index] == '\t' || fcontent[index] == '\n' || fcontent[index] == ' ')
					function[k][j] = ' ';
				else
					function[k][j] = fcontent[index];
				index++;
				j++;
				if (fcontent[index] == '\n'	|| fcontent[index] == '{')
				{
					if (fcontent[index - 1] == ')')
					{
						function[k][j] = ';';
						j++;
						index++;
					}
					else
					{
						function[k][j] = ' ';
						j++;
						index++;
					}
				}
				if (fcontent[index] == '{')
					check++;
				if (check >= 1)
				{
					function[k][j] = 0;
					printf("function[%d]: |%s|\n", k, function[k]);
					k++;
					j = 0;
					check = 0;
					/* break; */
				}
			}
		}
		index++;
	}
	for (int i = 0; i < MAX_FUN; i++)
	{
		free(function[i]);
	}
	free(function);
	return index;
}

int
main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: ./add_header.exe <c_file> <header_file>\n");
		return 0;
	}

	size_t buflen = 0;
	char *content = get_file_content(argv[1], &buflen);
	char *txt_file = "main.txt";

	get_functions(content, 0);
	return 0;
	int fd = _open(txt_file, _O_RDWR | _O_APPEND | _O_CREAT);
	if (fd == -1)
	{
		sprintf(msg_file_line, "[DEBUG] %s: %d",__FILE__, __LINE__);
		perror(msg_file_line);
		_close(fd);
		free(content);
		exit(1);
	}
	// stupid open prevents other process to access if it had to create the file
	// has to be here
	_umask(_S_IREAD | _S_IWRITE);

	for (int i = 0; i < buflen; i++)
	{
		_write(fd, &content[i], 1);
	}
	free(content);
	return 0;
}

void
random(int a, int b, int c, int d, int e, 
		int f, int g, 
		int h, int i)
{
}

void random1(void)
{
}

void
random2(void)
{
}

void
random3(void)
{
}

void random4(void)
{
}

void
random5(void)
{
}

void
random6(void)
{
}
