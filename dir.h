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

int isBaseDir();

int statEquals(struct stat sb1, struct stat sb2);