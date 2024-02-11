#include "common.h"


// void print_map(char **map, int max_index) {
//     int i = 0;
//     while (i < max_index) {
//         int j = 0;
//         while (j < max_index) {
//             write(1, &map[i][j], 1);
//             j++;
//         }
//         char newline = '\n';
//         write(1, &newline, 1);
//         i++;
//     }
// }


// void paint_map(char **map, int x, int y, int n, char full) {
//     int i = y;
//     while (i < y + n) {
//         int j = x;
//         while (j < x + n) {
//             map[i][j] = full;
//             j++;
//         }
//         i++;
//     }
// }


// void solve(char **map, int n, int min_n, char obs, char full, int max_index)
// {
//     int found = 0;
//     while (n >= min_n && !found) {
//         int y = 0;
//         while (y <= max_index - n && !found) { 
//             int x = 0;
//             while (x <= max_index - n && !found) {
//                 int empty = 1;
//                 int h = 0;
//                 while (h < n && empty) {
//                     int w = 0;
//                     while (w < n && empty) {
//                         if (map[y + h][x + w] == obs) {
//                             empty = 0;
//                         }
//                         w++;
//                     }
//                     h++;
//                 }
//                 if (empty) {
//                     paint_map(map, x, y, n, full);
//                     print_map(map, max_index);
//                     found = 1;
//                 }
//                 x++;
//             }
//             y++;
//         }
//         n--;
//     }
// }

// Function to check if a square of size n starting from coordinates (x, y) is empty
int is_empty(char **map, int x, int y, int n, char obs) {
    int i = y;
    while (i < y + n) {
        int j = x;
        while (j < x + n) {
            if (map[i][j] == obs) {
                return 0; // Not empty if an obstacle is found
            }
            j++;
        }
        i++;
    }
    return 1; // Square is empty
}

// Function to paint a square of size n starting from coordinates (x, y) with a given character
void paint_square(char **map, int x, int y, int n, char full) {
    int i = y;
    while (i < y + n) {
        int j = x;
        while (j < x + n) {
            map[i][j] = full;
            j++;
        }
        i++;
    }
}

void print_map(char **map, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            write(1, &map[i][j], 1);
        }
        char newline = '\n';
        write(1, &newline, 1);
    }
}

// Main function to solve the problem
int solve(char **map, int n, int min_n, char obs, char full, int max_index) {
    int found = 0;
    while (n >= min_n && !found) {
        int y = 0;
        while (y <= max_index - n && !found) {
            int x = 0;
            while (x <= max_index - n && !found) {
                if (is_empty(map, x, y, n, obs)) {
                    paint_square(map, x, y, n, full);
                    found = 1;
                    return found;
                }
                x++;
            }
            y++;
        }
        n--;
    }
    return 0;
}

void fill_map(char ***map, int rows, int cols, char buf[MAX_BUFFER_SIZE]) {
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (buf[k] != '\n') {
                (*map)[i][j] = buf[k++];
            } else {
                k++;
            }
        }
    }
}

void create_map(char ***map, int rows, int cols) {
    *map = (char **)malloc(rows * sizeof(char *));
    if (*map == NULL) {
        ft_err_log("Memory allocation failed for rows.\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        (*map)[i] = (char *)malloc(cols * sizeof(char));
        if ((*map)[i] == NULL) {
            ft_err_log("Memory allocation failed for columns.\n");
            exit(1);
        }
    }
}

int init_map(char ***map, char *file_name, char *full_chr, char *obs_chr, int *rows, int *cols) //initialize the map, get ready
{
    int fd; //file descriptor for map.txt
    int ret;
    int n;
    int i = 0;
    int first_newline_encountered = 0;
    char buffer[MAX_BUFFER_SIZE] = {0};
    fd = open(file_name,0); //open the .txt file, 0 flag means read only
    ret = read(fd, buffer, MAX_BUFFER_SIZE); //read the file  referred to by the fd and store them up to MAX_BUFFER_SIZE inside the buffer
    while (buffer[i] != '\0')
    {9iii
        write(1,&buffer[i],1);
        i++;
    }write(1,"\n",1);
    
    // Find the dimensions in the buffer
    i=0;
    while (buffer[i] != '\0') {
        if (buffer[i] == '\n') {
            if (!first_newline_encountered) {
                first_newline_encountered = 1;
            }
            (*rows)++; // Increment the row count for each newline , y, uzunluk?
            if (*cols == 0) {
                (*cols) = i; // Record the column count for the first row, x, karakter sayin, sayfanin enine boyutu
            }
        }
        i++;
    }

    n = ft_atoi(buffer); //n -> bulunabilecek en buyuk karenin kenari = iki kenardan kisa olani
    printf("burada n=%d",n);
    ret -= (*rows)*(*cols)+1;
    printf("burada rows=%d, cols=%d",*rows, *cols);
    
    *full_chr = buffer[ret-2];
    *obs_chr = buffer[ret-1];
    printf("burada full=%c, obs=%c",*full_chr, *obs_chr);

    create_map(map, *rows, *cols);
    fill_map(map, *rows, *cols, &buffer[ret]);
    return n;
}

int main(int arc, char **arv)
{
    char **map; //mapin ta kendisi 2 boyutlu matrix
    int ret = 0; //return value
    int rows = 0, cols = 0; //mapin eni ve boyu
    char obs_chr,full_chr; //obstacle ve full(paint) karakterleri
    ret = init_map(&map, "map.txt", &obs_chr, &full_chr, &rows, &cols); //addressleriyle gonderiyoruz, mutator function
    ret = solve(map, ret, 0, obs_chr, full_chr, ret);
    if(ret)
    {
        print_map(map, rows, cols);
    }
    else
        ft_err_log("Something went wrong.\n");
    return 0;
}