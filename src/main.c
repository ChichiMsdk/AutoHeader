#include "main.h"
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
just_write(char *txt_file, char *content, int buflen);

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
		strncat(total_buf, buf, bytes_r);
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

char *types[] = {"void", "char", "int", "float", "double", "size_t"};
int types_len = 6;

bool
is_type(char *str)
{
	int i = 0;
	while (i < types_len)
	{
		if (strcmp(str, types[i]) == 0)
			return true;
		i++;
	}
	return false;
}

/* 
 * This is sensitive to trailing spaces, two spaces or more in a row just fucks it up
 * Same goes for '{' not after a '\n'
 * Eg:	fn(int a){
 * 		}
 * 		will not work
 */
int
get_functions(char **tokens, int len)
{
	
	return 1;
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

	char **tokens = ft_split(content, " \v\r\t\n");
	int i = 0;
	while (tokens[i])
	{
		/* printf("%s\n", str[i]); */
		printf("str[%d]: |%s|\n", i, tokens[i]);
		i++;
	}
	get_functions(tokens, 0);
	just_write(txt_file, content, buflen);
	free(content);
	return 0;
}

void
just_write(char *txt_file, char *content, int buflen)
{
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
