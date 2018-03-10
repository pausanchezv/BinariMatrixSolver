//
// Created by pausanchezv on 21/06/16.
//

#include <stdio.h>
#include <stdlib.h>

#define FILENAME "/media/pausanchezv/DiskData/Languages/C/BinaryMatrixArea/test.dat"

/**
 * Method declarations
 */
void showMatrix(int **, int, int);
void exitIfNullPointer(void *);
int ** getMatrixFromFile(FILE *, int, int);
int ** getDynamicMatrix(int **, int, int);
int dynamicSolver(int **, int **, int, int);
int getMinimum(int, int, int);

/**
 * Main function
 */
int main(void) {

    //Declare local variables
    FILE *file;
    int ** matrix, ** dynamicMatrix;
    int numRows, numCols;
    int solution;

    //Open file descriptor
    file = fopen(FILENAME, "r");
    exitIfNullPointer(file);

    //Get number of rows and number of columns
    fscanf(file, "%d %d", &numRows, &numCols);

    //Get original matrix
    matrix = getMatrixFromFile(file, numRows, numCols);
    showMatrix(matrix, numRows, numCols);

    //Get dynamic matrix
    dynamicMatrix = getDynamicMatrix(matrix, numRows, numCols);

    //Algorithm solver
    solution = dynamicSolver(matrix, dynamicMatrix, numRows, numCols);

    //Shows the result
    printf("Maximum area is: %d\n", solution);

    //Liberation memory
    free(matrix);
    free(dynamicMatrix);

    return (EXIT_SUCCESS);
}


/**
 * Get min cost
 */
int getMinimum(int top, int left, int diagonal) {

    int minimum;

    minimum = top;
    minimum = (left < minimum) ? left : minimum;
    minimum = (diagonal < minimum) ? diagonal : minimum;

    return minimum;
}


/**
 * Dynamic programming algorithm
 */
int dynamicSolver(int ** matrix, int ** dynamicMatrix, int numRows, int numCols) {

    int row, col, top, left, diagonal, side = 0;

    for (row = 1; row < numRows; row++) {
        for (col = 1; col < numCols; col++) {

            if (matrix[row][col] == 1) {

                top = dynamicMatrix[row - 1][col];
                left = dynamicMatrix[row][col - 1];
                diagonal = dynamicMatrix[row - 1][col - 1];

                dynamicMatrix[row][col] = 1 + getMinimum(top, left, diagonal);

                if (dynamicMatrix[row][col] > side) {
                    side = dynamicMatrix[row][col];
                }
            }
        }
    }

    return side * side;
}


/**
 * Get original matrix from file
 */
int ** getMatrixFromFile(FILE * file, int numRows, int numCols) {

    int row, col;
    int ** matrix;

    //Allocate matrix memory
    matrix = (int **) malloc(numRows * sizeof(int *));
    exitIfNullPointer(matrix);

    //Allocate items memory
    for (row = 0; row < numRows; row++) {
        matrix[row] = malloc(numCols * sizeof(int));
        exitIfNullPointer(matrix[row]);
    }

    //Fill memory with binary numbers
    for (row = 0; row < numRows; row++) {
        for (col = 0; col < numCols; col++) {
            fscanf(file, "%d", &matrix[row][col]);

        }
    }

    return matrix;
}


/**
 * Get dynamic matrix
 */
int ** getDynamicMatrix(int ** matrix, int numRows, int numCols) {

    int row, col;
    int ** dynamicMatrix;

    //Allocate matrix memory
    dynamicMatrix = (int **) malloc(numRows * sizeof(int *));
    exitIfNullPointer(dynamicMatrix);

    for (row = 0; row < numRows; row++) {
        dynamicMatrix[row] = calloc((size_t) numCols, sizeof(int));
        exitIfNullPointer(dynamicMatrix[row]);
    }

    //Fill first row and column
    for (row = 0; row < numRows; row++) {
        for (col = 0; col < numCols; col++) {
            if(row == 0 || col == 0) {
                dynamicMatrix[row][col] = matrix[row][col];
            }

        }
    }

    return dynamicMatrix;
}


/**
 * Shows the matrix
 */
void showMatrix(int ** matrix, int numRows, int numCols) {

    int row, col;

    printf("\nThe original matrix is\n \n");

    //Traverse matrix and print their items
    for (row = 0; row < numRows; row++) {
        for (col = 0; col < numCols; col++) {
            printf("%d ", matrix[row][col]);

        }
        printf("\n");
    }
    printf("\n");
}


/**
 * Exit if can't allocate dynamic memory
 */
void exitIfNullPointer(void * pointer) {

    //Exit with failure flag if can't allocate dynamic memory
    if (pointer == NULL) {
        exit(EXIT_FAILURE);
    }
}
