#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

__author__ = "@pausanchezv"
__email__ = "info@pausanchezv.com"

'''
Coding Exercise - There is a 2D binary matrix filled with 0’s and 1’s,
your task is to find the largest square containing all 1’s and return its area.
'''

''' Globals & constants '''
MATRIX_FILE = "test.dat"
expected_value = None


def get_matrix_from_file():
    """
    Reads the file and create an array of strings
    :return: String matrix
    """
    try:
        with open(MATRIX_FILE, 'r') as reader:
            lines = filter(lambda x: x != '\n', reader)[1:]
            return map(lambda x: x.split(), lines)

    except IOError:
        sys.exit("File does not exist")


def config_matrix(matrix):
    """
    Converts matrix string to an matrix of integers
    :param matrix: String matrix
    :return: Integer matrix
    """
    matrix = [[int(x) for x in list(row)] for row in matrix]
    return matrix


def get_matrix_size(matrix):
    """
    Returns the matrix size
    :param matrix: Input matrix
    :return: Matrix size
    """
    return len(matrix), len(matrix[0])


def get_matrix_clone(matrix, num_rows, num_cols):
    """
    Clone first row and first column in clone
    :param matrix: Original matrix
    :param num_rows: Number of rows
    :param num_cols: Number of columns
    :return: Clone
    """
    clone = [[0] * len(row) for row in matrix]
    clone[0] = matrix[0]

    for row in range(num_rows):
        for col in range(num_cols):
            if col == 0:
                clone[row][col] = matrix[row][col]

    return clone


def __get_diagonal(matrix, row, col):
    """
    Get diagonal slot
    :param matrix: Matrix clone
    :param row: Number of rows
    :param col: Number of columns
    :return: Diagonal
    """
    return matrix[row - 1][col - 1]


def __get_left(matrix, row, col):
    """
    Get left slot
    :param matrix: Matrix clone
    :param row: Number of rows
    :param col: Number of columns
    :return: Left
    """
    return matrix[row][col - 1]


def __get_top(matrix, row, col):
    """
    Get top slot
    :param matrix: Matrix clone
    :param row: Number of rows
    :param col: Number of columns
    :return: Top
    """
    return matrix[row - 1][col]


def dynamic_solver(matrix, clone, num_rows, num_cols):
    """
    Dynamic binary matrix solver
    :param matrix: Original matrix
    :param clone: Matrix filled with zeros
    :param num_rows: Number of rows
    :param num_cols: Number of columns
    :return: Dynamic matrix solution
    """
    for row in range(1, num_rows):
        for col in range(1, num_cols):

            if matrix[row][col]:

                diagonal = __get_diagonal(clone, row, col)
                top = __get_top(clone, row, col)
                left = __get_left(clone, row, col)

                clone[row][col] = 1 + min(diagonal, top, left)

    return clone


def get_area(matrix, num_rows, num_cols):
    """
    Returns max area
    :param matrix: matrix Result
    :param num_rows: Number of rows
    :param num_cols: Number of columns
    :return: Area
    """
    side = 0

    for row in range(num_rows):
        for col in range(num_cols):
            if matrix[row][col] > side:
                side = matrix[row][col]

    return side ** 2


def show_matrix(matrix):
    """
    Shows the matrix
    :param matrix: Current matrix
    :return: None
    """
    res = "\n"
    for row in matrix:
        res += str(row) + "\n"
    print res


def main():
    """
    Main Function
    :return: None
    """

    ''' Read and config matrix '''
    matrix = get_matrix_from_file()
    matrix = config_matrix(matrix)

    ''' Shows the initial matrix '''
    show_matrix(matrix)

    ''' Matrix size '''
    num_rows, num_cols = get_matrix_size(matrix)

    ''' Clone first row and first column in another matrix '''
    clone = get_matrix_clone(matrix, num_rows, num_cols)

    ''' Dynamic solver algorithm '''
    matrix = dynamic_solver(matrix, clone, num_rows, num_cols)

    ''' Get solution area '''
    area = get_area(matrix, num_rows, num_cols)

    ''' Shows the result '''
    print ">> Result {}".format(area)


if __name__ == "__main__":
    """ Running the program """
    main()
