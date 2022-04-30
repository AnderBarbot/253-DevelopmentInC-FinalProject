/* 
 * Author: Ander Barbot
 * Date: Fri Apr 29 14:58:22 MDT 2022
 * Description: custom version of the ps command
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h> 
#include "ProcEntry.h"

#define READ_BUFFER_SIZE 1024
#define MAX_FILEPATH_SIZE 4096

#define UNUSED(x) (void)x

/*
 * @params direct** entryA, dirent** entryB
 *  returns 0
 */
int noSort(const struct dirent ** entryA, const struct dirent ** entryB) {
    UNUSED(entryA);
    UNUSED(entryB);
    return 0;
}

/*
 * @params void* a, void* b
 *  returns int
 */
static int pidSort(const void *a, const void *b)
{
     ProcEntry* i = *(ProcEntry **)a;
     ProcEntry* j = *(ProcEntry **)b;
     int val = i->process_id - j->process_id;
     return val;
}


/* 
 *  @params void* a, void* b
 *  returns int
 */
static int commSort(const void* a, const void* b)
{
     ProcEntry* i = *(ProcEntry **)a;
     ProcEntry* j = *(ProcEntry **)b;
     int val = strcmp(i->comm, j->comm);    //I believe I need to create my own strcmp, though the one i tried produced MANY errors
     return val;
}

/*
 * @params of direct* curr
 * returns, 1 as default, or zero if the file is not a digit or not a directory
 */
static int defaultF (const struct dirent* curr) {
    if(curr->d_type != 4 || !isdigit(curr->d_name[0])) {
        return 0;
    }
    return 1;
}

/*
 * prints a usage menu for the syntax of myps
 */
void printUse(void) {
    fprintf(stderr, "Usage: ./myps [-d <path>] [-p] [-c] [-z] [-h]\n");
    fprintf(stderr, "\t-d <path> Directory containing proc entries (default: /proc)\n");
    fprintf(stderr, "\t-p\t  Display proc entries sorted by pid (default)\n");
    fprintf(stderr, "\t-c\t  Display proc entries sorted by command lexicographically\n");
    fprintf(stderr, "\t-z\t  Display ONLY proc entries in the zombie state\n");
    fprintf(stderr, "\t-h\t  Display this use message\n");
}

int main (int argc, char * argv[]) {
    int n;
    int opt;
    bool onlyZombie = false;

    /* filterF pointer declaration*/
    int (*filterF)(const struct dirent *);
    filterF = defaultF;
    /* sortF pointer declaration*/
    int (*sortF)(const struct dirent **, const struct dirent **);
    sortF = noSort;
    int (*qSortF)(const void *, const void *);
    qSortF = pidSort;

    /* dirPath declaration */
    char dirPath[MAX_FILEPATH_SIZE];
    strcpy(dirPath, "/proc");

    /* use getopt() to process command line arguments */
    while( (opt = getopt(argc, argv, "d:pczh")) != -1) {
        switch(opt) {
            case 'd':
                strncpy(dirPath, optarg, MAX_FILEPATH_SIZE);
                break;
            case 'p':
                qSortF = pidSort;
                break;
            case 'c':
                qSortF = commSort;
                break;
            case 'z':
                onlyZombie = true;
                break;
            case 'h':
                printUse();
                exit(0);
                break;
            default:
                fprintf(stderr, "Invalid option specified\n");
                fprintf(stderr, "Usage: %s [-d <path>] [-p] [-c] [-z] [-h]\n", argv[0]);
                break;
        }
    }
     /* Scan dir at dirPath */
    struct dirent **eps;
    errno = 0;
    n = scandir (dirPath, &eps, filterF, sortF);
    ProcEntry ** myprocs = (ProcEntry **) (malloc(sizeof(ProcEntry *) * n));

    /* validate directory  */
    if (n < 0) {
        perror("scandir: ");
        exit(1);
    }

    /* Header */
    fprintf(stdout,"%7s %7s %5s %5s %5s %7s %-25s %-20s\n","PID","PPID","STATE","UTIME","STIME","THREADS","CMD","STAT_FILE");

    int count;
    for (count = 0; count < n; ++count) {
        char myPath[MAX_FILEPATH_SIZE];
        strcpy(myPath, dirPath);
        strcat(myPath, "/");
        strcat(myPath, eps[count]->d_name);
        strcat(myPath, "/stat");
        myprocs[count] = CreateProcEntryFromFile(myPath);
    }
    /* Sort Array */
    qsort(myprocs, n, sizeof(ProcEntry*), qSortF);

    for (count = 0; count < n; ++count) {
        // filter by onlyZombie
        if((onlyZombie && myprocs[count]->state == 'Z') || (!onlyZombie)) {
            PrintProcEntry(myprocs[count]);
        }
    }

    /* cleanup memory */
    for(int i = 0; i < n; i++) {
        free(eps[i]);
        DestroyProcEntry(myprocs[i]);
    }

    free (eps);
    free(myprocs);
}