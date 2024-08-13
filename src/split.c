#include "split.h"

static int
ft_check_del(char c, char *del, int del_size)
{
	int i = 0;
	while (i < del_size)
	{
		if (c == del[i])
			return 1;
		i++;
	}
	return 0;
}

static int
ft_count_word(char *str, char *del, int del_size)
{
	int i = 0;
	int count = 0;
	while (str[i])
	{
		if (ft_check_del(str[i], del, del_size))
		{
			while (str[i] && ft_check_del(str[i], del, del_size))
				i++;
			if (str[i] && !ft_check_del(str[i], del, del_size))
				count++;
			continue;
		}
		i++;
	}
	return count;
}

void
free_str(char **str, int len)
{
	int i = 0;
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void
ft_strncpy(char *dst, char *src, int size)
{
	int i = 0;
	while (src[i] && i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

/**
 * Assuming here NULL terminated strings
 *
 * Non NULL !
 * No NULL check for malloc cuz fuck you
*/
char **
ft_split(char *str, char *del)
{
	int				i = 0;
	int 			j = 0;
	int 			word_begin = 0;
	size_t			del_size = strlen(del);
	size_t			str_size = strlen(str);
	int 			count_word = ft_count_word(str, del, del_size);
	char			**str_split = malloc((sizeof(char *) * (count_word + 1)));

	while (i < str_size && j < count_word)
	{
		// skips delimiters
		while (str[i] && ft_check_del(str[i], del, del_size))
		{
			i++;
			word_begin++;
		}
		// gets the "word"
		while (str[i] && !ft_check_del(str[i], del, del_size))
			i++;

		str_split[j] = malloc(sizeof(char) * (i - word_begin + 1));
		ft_strncpy(str_split[j], str + word_begin, i - word_begin);
		word_begin = i;
		j++;
	} 
	str_split[j] = 0;
	return str_split;
}
