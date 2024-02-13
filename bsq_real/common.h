#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_BUFFER_SIZE 1024

static int	ft_strlen(const char *str);
int	ft_err_log(char *str);
int	ft_atoi(char *str);