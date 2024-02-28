#ifndef THOMAS_SHELLBY_H
#define THOMAS_SHELLBY_H

/* 
 * Below are the various header files to be imported and used throughout the program.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

/*
 * Here are prototype functions that are called here for ease of coding.
 */

void prompt_ly(void);
void read_er(char *user_input, size_t volume);
void execut_er(char *user_input);
void i_print(const char *on_screen);

#endif
