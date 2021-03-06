/*
CPE 357 Lab05
Author: Dylan Baxter (dybaxter)
File: mypwd.c
Description: This file contains main functionality for a program that will
print the curren working directory of the the user up to 2048 characters.
and print "path too long" otherwise
*/
#include<unistd.h>
#include<limits.h>
#include"dir.h"

int main(int argc, char* argv[]){
    /*Initialze Variables*/
    char* path = (char*)malloc(sizeof(char)*PATH_MAX);
    path[0] = '\0';
    /*Dirlist of 1 char dirs has max of PATH_MAX/2 */
    char* dirList[PATH_MAX/2];
    int i;
    /*Initialze dirlist*/
    for(i = 0; i< (PATH_MAX/2); i++){
        dirList[i] = NULL;
    }
    int dirCount = 0;
    struct stat sb;
    struct stat sb_old;
    DIR* currentDir;
    struct dirent* e;


    /*While parent of current dir is not itself*/
    while(!(isBaseDir())){
        /*Stat Current Directory*/
        if(-1 == stat(".",&sb_old)){
            perror("Home stat fail");
            exit(EXIT_FAILURE);
        }

        /*Go up a directory*/
        if(-1==chdir("..")){
            perror("Change Dir");
            exit(EXIT_FAILURE);
        }

        /*Open parent dir for reading*/
        if(NULL==(currentDir = opendir("."))){
            perror("Open dir");
            exit(EXIT_FAILURE);
        }
        if(NULL==(e = readdir(currentDir))){
            perror("read dir");
            exit(EXIT_FAILURE);
        }

        /*While there are files in parent dir*/
        while((e = readdir(currentDir))){
            /*Look for a file with the same device
            and inode as previous*/
            if(-1 == stat(e->d_name,&sb)){
                perror("Home stat fail");
                exit(EXIT_FAILURE);
            }
            if(statEquals(sb, sb_old)){
                /*Store name of file in path string*/
                if(dirCount > PATH_MAX/2){
                    printf("Filepath too long\n");
                    exit(EXIT_FAILURE);
                }
                dirList[dirCount] = mystrdup(e->d_name);
                dirCount++;
                break;
            }
        }



        /*Close Current Dir*/
        if(-1==closedir(currentDir)){
            perror("Close dir");
            exit(EXIT_FAILURE);
        }
    }
    /*Initialize path Process*/
    int pathLength = 0;
    char delim[2];
    delim[0] = '/';
    delim[1] = '\0';
    limitConcat(path, delim, PATH_MAX);
    pathLength++;
    /*Construct Path*/
    for(i=dirCount-1; i >= 0;i--){
        /*For each directory in reverse order*/
        if(dirList[i] != NULL){
            /*Increase pathlength*/
            pathLength = pathLength+strlen(dirList[i]);
            /*Check to make sure path does not exceed limit*/
            if(pathLength < PATH_MAX-1){
                /*Add dir name and foreward slash*/
                limitConcat(path, delim, PATH_MAX);
                pathLength++;
                limitConcat(path, dirList[i], PATH_MAX);
            }
            else{
                printf("Filepath too long!\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    /*Null terminate*/
    path[pathLength+1] = '\0';

    /*Return to original dir and print path*/
    chdir(path);
    printf("%s\n",path);

    /*Free Memory*/
    free(path);
    for(i = 0; i< (PATH_MAX/2); i++){
        if(dirList[i] != NULL){
                free(dirList[i]);
        }
    }
    return 0;
}