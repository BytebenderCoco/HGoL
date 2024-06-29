#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#if defined(__WIN32)
#define SysClr "cls"
#elif defined(__unix__) || (__APPLE__) || (__linux__)
#define SysClr "clear"
#endif

int row = 10;
int col = 10;
int refreshTime = 0;
int generations = 0;


void initalizeRandomGrid(int grid[row][col]){
    srand(time(NULL));
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            grid[i][j] = rand()%2;              //Random Number. Either 0 or 1 because of mod2
        }
    }
}
int is_alive(int nr, int nc, int grid[row][col]){
    if (grid[nr][nc] == 1){                     //Checks if cell is alive(1) or dead(0).
        return 1;
    } else {
        return 0;
    }
}

int is_within_bounds(int nr, int nc){    //Checks if the cell is within the bounds of the array
    if (nr >= 0 && nc >= 0 && nr < row && nc < col){    //nr = neighbor-row; nc = neighbor-col
        return 1;
    }else{
        return 0;
    }
}

void printGrid(int grid[row][col]) {

    for (int i = 0; i < row; i++) {

        if (i % 2 == 1) {                       //Second Row Space for hexagonal grid
            printf(" ");
        }

        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 1){
                printf("0 ");      //Space after character to create grid
            }else{
                printf(". ");      //Adjustment of characters by preference
            }
        }
        printf("\n");
    }
}

void count_live_neighbour_cells(int grid[row][col], int neighbor_counts[row][col]) {
    // Set offsets for neighboring cells
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            neighbor_counts[r][c] = 0;
        }
    }
    int potential_neighbours = 6;
    // Potential position of neighboring cells. Depending on parity
    int delta_row_even[] = {-1, -1, 0, 0, 1, 1};
    int delta_column_even[] = {0, -1, -1, 1, -1, 0};
    int delta_row_uneven[] = {-1, -1, 0, 0, 1, 1};
    int delta_column_uneven[] = {0, 1, 1, -1, 1, 0};

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            int count = 0;
            // Check if the row is even or odd and calculate neighbors accordingly
            if (r % 2 == 0) {
                for (int i = 0; i < potential_neighbours; i++) {
                    int nr = r + delta_row_even[i];
                    int nc = c + delta_column_even[i];

                    if (is_within_bounds(nr, nc) && is_alive(nr, nc, grid)) {
                        count++;
                    }
                }
            } else {
                for (int i = 0; i < potential_neighbours; i++) {
                    int nr = r + delta_row_uneven[i];
                    int nc = c + delta_column_uneven[i];

                    if (is_within_bounds(nr, nc) && is_alive(nr, nc, grid)) {
                        count++;
                    }
                }
            }
            // Set the count for the current cell
            neighbor_counts[r][c] = count;
        }
    }
    for(int y = 0; y < row; y++){               //Overwrite each cell according to rules
        for(int x = 0; x < col; x++){
            if(neighbor_counts[y][x] == 2) {     //Game rules used to preserve glider-structure of the original game of life
                if(grid[y][x] == 0) {
                    grid[y][x] = 1;
                }else{
                    grid[y][x] = 0;
                }
            }
            if(neighbor_counts[y][x] == 0 || neighbor_counts[y][x] == 1 || neighbor_counts[y][x] == 4 || neighbor_counts[y][x] == 6){
                grid[y][x] = 0;
            }
        }
    }
}


void parameterAdjustment(){
    //manipulation of global game-variables
    printf("Enter number of rows(5-50):");
    fflush(stdin);
    scanf("%d", &row);
    system(SysClr);
    printf("Enter number of columns(5-50):");
    fflush(stdin);
    scanf("%d", &col);
    system(SysClr);
    printf("Enter refreshtime:");
    fflush(stdin);
    scanf("%d", &refreshTime);
    system(SysClr);
    printf("Enter number of generations:");
    fflush(stdin);
    scanf("%d", &generations);
    system(SysClr);
}

void print_save(FILE *file, int grid[row][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fprintf(file, "%d", grid[i][j]);
        }
        fprintf(file, "\n");
    }
}

int save_file(int grid[][100]) {
    char path[90] = "../saves/";
    char file_name[20];

    printf("Type Save-Name...\n");
    scanf("%19s", file_name); // Limit input to avoid buffer overflow

    strcat(path, file_name); // Concatenate the directory path and the file name

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }

    print_save(file, grid); // Pass grid and its dimensions

    fclose(file);

    printf("Grid saved successfully to %s\n", path);
    return 0;
}

int read_file(int grid[row][col]) {
    char filename[20];
    char path[70] = "../saves/";  // Adjusted the path size for safety
    int save_grid[row][col];

    printf("What save, would you like to upload?\n");
    scanf("%19s", filename);  // Read input into filename

    strcat(path, filename);  // Concatenate "saves/" and filename

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Error reading the file.\n");
        return 1;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (fscanf(file, "%1d", &save_grid[i][j]) != 1) {
                printf("Error reading the file.\n");
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            grid[i][j] = save_grid[i][j];
        }
    }

    return 0;
}


int main() {
    //Rows, Columns, Refreshtime and Iterations get set
    parameterAdjustment();
    int grid[row][col];
    int neighbor_counts[row][col];

    int choice;
    printf("Choose to read file or use random grid(0/1):\n");
    fflush(stdin);
    scanf("%d", &choice);
    if(choice == 0){
        read_file(grid);
    }else if(choice == 1){
        initalizeRandomGrid(grid);
    }else{
        exit(1);
    }
    system(SysClr);
    for(int i = 0; i < generations; i++) {
        printGrid(grid);
        count_live_neighbour_cells(grid, neighbor_counts);
        usleep(refreshTime*100000);
        system(SysClr);
    }

    printf("Choose to save file or exit(0/1):\n");
    fflush(stdin);
    scanf("%d", &choice);
    if(choice == 0){
        save_file(grid);
    }else{
        exit(1);
    }
    return 0;
}