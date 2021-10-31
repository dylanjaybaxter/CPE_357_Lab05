/*
CPE 357 Lab05
Author: Dylan Baxter (dybaxter)
File: dir.h
Description: This file contains functions relating to Directory
operations
*/
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

/*Checks if the current working directory is the root*/
int isBaseDir();

/*Checks the equivalence of 2 stat objects */
int statEquals(struct stat sb1, struct stat sb2);

/*Personal Implementation of strncat functinoality*/
void limitConcat(char* dest, char* lim, int destSize);

/*Personal Implementation of strdup functinoality*/
char* mystrdup(char* pt);