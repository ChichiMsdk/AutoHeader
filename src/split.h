#ifndef SPLIT_H
#define SPLIT_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char		**ft_split(char *str, char *del);
void		free_str(char **str, int len);
void		ft_strncpy(char *dst, char *src, int size);

#endif
