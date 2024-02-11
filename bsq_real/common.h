#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_BUFFER_SIZE 4096

static int	ft_strlen(const char *str);
int	ft_err_log(char *str);
int find_sqrt(int number);
int	ft_atoi(char *str);