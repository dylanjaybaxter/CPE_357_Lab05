/*
CPE 357 Lab05
Author: Dylan Baxter (dybaxter)
File: dir.c
Description: This file contains functions relating to Directory
operations
*/
#include"dir.h"

/*Checks is the current directory is the root directory*/
int isBaseDir(){
    struct stat sb1;
    struct stat sb2;
    /*Open Current Directory*/
    if(-1 == stat(".",&sb1)){
        perror("Home stat fail");
        exit(EXIT_FAILURE);
    }
    if(-1 == stat("..",&sb2)){
        perror("Home stat fail");
        exit(EXIT_FAILURE);
    }
    if(sb1.st_dev == sb2.st_dev && sb1.st_ino == sb2.st_ino){
        return 1;
    }
    else{
        return 0;
    }
}

/*Checks if the stats of 2 file objects are equal*/
int statEquals(struct stat sb1, struct stat sb2){
    if(sb1.st_dev == sb2.st_dev && sb1.st_ino == sb2.st_ino){
        return 1;
    }
    else{
        return 0;
    }
}

/*Personal Implementation of strncat() functinoality*/
void limitConcat(char* dest, char* lim, int maxDestSize){
    int i = strlen(dest);
    int limSize = strlen(lim);
    int charsWritten = 0;
    while(i < maxDestSize && charsWritten < limSize){
        dest[i] = lim[charsWritten];
        i++;
        charsWritten++;
    }
    dest[i] = '\0';
}

/*Personal Implementation of strdup functinoality*/
char* mystrdup(char* pt){
    int ptLen = strlen(pt);
    char* dup = (char*)malloc(sizeof(char)*(ptLen+1));
    int i;
    for(i=0; i < ptLen; i++){
        dup[i] = pt[i];
    }
    dup[i] = '\0';
    return dup;
}