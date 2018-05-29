# Get_Next_Line

## Project Overview

This project's goal is to create a function that reads the next line from a given file descriptor
A line is defined as a sequence of character ended either by a newline character or by the EOF (end of file)
This function returns 1, 0 or -1 depending on wether a line has been read, if EOF has been reached or if an error has happened respectively

## Usage

int get_next_line(int fd, char **line);

Function should be provided with a valid file descriptor and the address of a char pointer to store the line
