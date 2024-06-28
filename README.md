# Hexagonal Game of Life

This project is an implementation of Conway's Game of Life on a hexagonal grid. The game simulates the life and death of cells based on predefined rules and allows for saving and loading grid states.

## Features

- Hexagonal grid representation

- Random grid initialization

- Save and load grid states to/from files

- Adjustable parameters (grid size, refresh time, number of generations)

## Requirements

- C compiler (GCC recommended)

## Compilation

To compile the program, use the following command:

gcc -o HGoL HGoL.c

## Usage

Run the compiled programm:

./HGoL

**Program Flow**

1. **Parameter Adjustment**:

  • Enter the number of rows (5-50)

  • Enter the number of columns (5-50)

  • Enter the refresh time (in seconds)

  • Enter the number of generations

2. **Grid Initialization**:

  • Choose to read a grid from a file or initialize a random grid (0 for file, 1 for random)
3. **Simulation**:

  • The grid is displayed and updated for the specified number of generations with the specified refresh time.
4. **Save or Exit**:

  • Choose to save the final grid state to a file or exit the program (0 to save, 1 to exit)

**File Structure**

• HGoL.c**: Main program file containing all functions and logic

• **saves/**: Directory for saving and loading grid states

**Functions**

• void initalizeRandomGrid(int grid[row][col]): Initializes the grid with random values (0 or 1)

• int is_alive(int nr, int nc, int grid[row][col]): Checks if a cell is alive

• int is_within_bounds(int nr, int nc): Checks if a cell is within grid bounds

• void printGrid(int grid[row][col]): Prints the grid to the console

• void count_live_neighbour_cells(int grid[row][col], int neighbor_counts[row][col]): Counts live neighbor cells and updates the grid according to the rules

• void parameterAdjustment(): Adjusts global game variables based on user input

• void print_save(FILE *file, int grid[row][col]): Saves the grid to a file

• int save_file(int grid[][100]): Handles file saving operations

• int read_file(int grid[row][col]): Reads a grid from a files 

**Notes**
• Ensure the saves directory exists in the same location as the executable for saving and loading grid states.
