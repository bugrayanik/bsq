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

// // Function to check if a square of size n starting from coordinates (x, y) is empty
// int is_empty(char **map, int x, int y, int n, char obs) 
// {
//     int i = y;
//     while (i < y + n) 
//     {
//         //printf("girdi 1\n");
//         int j = x;
//         while (j < x + n) 
//         {
//             printf("map[%d][%d] = %c\n", i,j,map[i][j]);
//             if (map[i][j] == obs)
//             {
//                 return 0; // Not empty if an obstacle is found
//             }
//             j++;
//         }
//         i++;
//     }
//     return 1; // Square is empty
// }

// // Function to paint a square of size n starting from coordinates (x, y) with a given character
// void paint_square(char **map, int x, int y, int n, char full) 
// {
//     int i = y;
//     while (i < y + n) 
//     {
//         int j = x;
//         while (j < x + n) 
//         {
//             map[i][j] = full;
//             j++;
//         }
//         i++;
//     }
// }

int is_empty(char **map, int y, int x, int n, char obs) 
{
    int i = y;
    while (i < y + n) 
    {
        int j = x;
        while (j < x + n) 
        {
            //printf("map[%d][%d] = %c\n", i, j, map[i][j]);
            if (map[i][j] == obs)
            {
                return 0; // Not empty if an obstacle is found
            }
            j++; // Move to the next column
        }
        i++; // Move to the next row
    }
    return 1; // Square is empty
}

void paint_square(char **map, int y, int x, int n, char full) 
{
    int i = y;
    while (i < y + n) 
    {
        int j = x;
        while (j < x + n) 
        {
            map[i][j] = full;
            j++; // Move to the next column
        }
        i++; // Move to the next row
    }
}



void print_map(char **map, int rows, int cols) 
{
    int i = 0;
    while (i < rows) 
    {
        int j = 0;
        while (j < cols) 
        {
            write(1, &map[i][j], 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
    write(1, "\n", 1);
}

// Main function to solve the problem
// int solve(char **map, int n, int min_n, char obs, char full, int rows, int cols) {
//     int found = 0;
//     while (n >= min_n && !found) {
//         int y = 0;
//         while (y <= cols - n && !found) {  //max index ==> bu mape cizebilecegim en buyuk karenin sideinin uzunlugu
//             int x = 0;
//             while (x <= rows - n && !found) { //(0,0), (0,1), (0,2) --> hangi cellden deneyecegini dolasmak icin
//                 printf("(%d,%d) -->%d\n", x,y,n);
//                 if (is_empty(map, x, y, n, obs)) {
//                     paint_square(map, x, y, n, full);
//                     found = 1;
//                     return found;
//                 }
//                 x++;
//             }
//             y++;
//         }
//         n--; // n denenen karenin side boyutu (kenar uzunlugu), giderek daha kucuk kenarli kare deniyoruz.
//             // ilk en buyuk kenarli kareyi cizmeye calisacagiz, n = maximum squares side len
//     }
//     return 0;
// }

int solve(char **map, int n, int min_n, char obs, char full, int rows, int cols) {
    int found = 0;
    while (n >= min_n && !found) {
        int x = 0;
        while (x <= rows - n && !found) {
            int y = 0;
            while (y <= cols - n -1&& !found) {
                //printf("(%d,%d) -->%d\n", x, y, n);
                if (is_empty(map, x, y, n, obs)) {
                    paint_square(map, x, y, n, full);
                    found = 1;
                    return found;
                }
                y++;
            }
            x++;
        }
        n--;
    }
    return 0;
}


void fill_map(char ***map, int rows, int cols, char buf[MAX_BUFFER_SIZE], int k) {

    int i = 0;
    while (i < rows) {
        int j = 0;
        while (j < cols) 
        {
            if (buf[k] != '\n')
            {
                (*map)[i][j] = buf[k];
            }
            k++;
            j++;
        }
        i++;
    }
}


void create_map(char ***map, int rows, int cols) {
    *map = (char **)malloc(rows * sizeof(char *));
    if (*map == NULL) {
        ft_err_log("Memory allocation failed for rows.\n");
        exit(1);
    }

    int i = 0, j;
    while (i < rows) 
    {
        (*map)[i] = (char *)malloc(cols * sizeof(char));
        if ((*map)[i] == NULL) 
        {
            ft_err_log("Memory allocation failed for columns.\n");
            exit(1);
        }

        // Initialize each element in the row to zero
        for (j = 0; j < cols; j++) 
        {
            (*map)[i][j] = 0;
        }
        i++;
    }
}


int init_map(char ***map, char *file_name, char *full_chr, char *obs_chr, int *rows, int *cols) //initialize the map, get ready
{
    int fd; //file descriptor for map.txt
    int ret;
    int n;
    int i , k= 0;
    int first_newline_encountered = 0;
    char buffer[MAX_BUFFER_SIZE] = {0};
    fd = open(file_name, O_RDONLY); //open the .txt file, 0 flag means read only
    ret = read(fd, buffer, 1024); //read the file  referred to by the fd and store them up to MAX_BUFFER_SIZE inside the buffer

    // Find the dimensions in the buffer
    while (buffer[k] != '\n') 
        k++; // ilk satirda kac karakter var.
    while (buffer[i+k] != '\0') 
    {
        if (buffer[i+k] == '\n') 
        {
            (*rows)++; // Increment the row count for each newline , y, uzunluk?
            if (*cols == 0) //if cols was empty
            { 
                (*cols) = i; // Record the column count for the first row, x, karakter sayin, sayfanin enine boyutu
            }
        }
        i++;
    }

    n = ft_atoi(buffer); //n -> bulunabilecek en buyuk karenin kenari
    *full_chr = buffer[k-1];
    *obs_chr = buffer[k-2];
    printf("rows =%d, cols =%d, obs =%c, full =%c\n", *rows, *cols, *obs_chr, *full_chr);
    create_map(map, *rows, *cols);
    fill_map(map, *rows, *cols, buffer, k);
    return n;
}

int main(int arc, char **arv)
{
    char **map = NULL; //mapin ta kendisi 2 boyutlu matrix DUZLEM
    int ret = 0; //return value
    int rows = 0, cols = 0; //mapin eni ve boyu
    char obs_chr,full_chr; //obstacle ve full(paint) karakterleri
    ret = init_map(&map, "map.txt", &full_chr, &obs_chr, &rows, &cols); //addressleriyle gonderiyoruz, mutator function
    print_map(map, rows, cols);
    ret = solve(map, ret, 0, obs_chr, full_chr, rows, cols);
    if(ret)
    {
        print_map(map, rows, cols);
    }
    else
        ft_err_log("Something went wrong.\n");
    return 0;
}