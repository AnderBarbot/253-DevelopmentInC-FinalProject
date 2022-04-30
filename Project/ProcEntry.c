/* 
 * Author: Ander Barbot
 * Date: Fri Apr 29 14:28:50 MDT 2022
 * Description: struct and functions for ProcEntry
 */

#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include "ProcEntry.h"

#define MAX_PATH_SIZE 62

ProcEntry * CreateProcEntry(void) {
    /* Memory allocation and validation */
    ProcEntry * entry = (ProcEntry *) malloc(sizeof(ProcEntry));
    if (entry == NULL) {
        return NULL;
    }
    entry->process_id = 0;
    entry->parent_process_id = 0;
    entry->comm = (char *) malloc(MAX_PATH_SIZE);
    entry->state = '\0';  
    entry->utime = 0;
    entry->stime = 0;
    entry->number_of_threads = 0;
    entry->path = (char *) malloc(MAX_PATH_SIZE);

    return entry;
}

ProcEntry * CreateProcEntryFromFile(const char statFile[]) {

    if(statFile == NULL) {
        return NULL;
    }

    /* file opening and validation */
    FILE* file = fopen(statFile, "r");
    if(file == NULL) {
        fprintf(stderr, "CreateProcEntryFromFile: No such file or directory\n");
        return NULL;
    }

    /*Memory allocation and validation*/
    ProcEntry * entry = (ProcEntry *) malloc(sizeof(ProcEntry));
    if (entry == NULL) {
        return NULL;
    }

    entry->comm = (char *) malloc(MAX_PATH_SIZE);
    entry->path = (char *) malloc(MAX_PATH_SIZE);

    fscanf(file, "%d ", &entry->process_id);
    fscanf(file, "%s ", entry->comm);
    fscanf(file, "%c ", &entry->state);
    fscanf(file, "%d", &entry->parent_process_id);

    /* until utime, read words*/
    int num = 0;
    char s;
    while(num < 10 && (s=fgetc(file))!=EOF) {
        if(s == ' ') {
            num++;
        }
    }    

    fscanf(file, "%lu ", &entry->utime);
    fscanf(file, "%lu", &entry->stime);

    /* until utime, read words */
    num = 0;
    while(num < 5 && (s=fgetc(file))!=EOF) {
        if(s == ' ') {
            num++;
        }
    }    

    fscanf(file, "%ld", &entry->number_of_threads);

    strcpy(entry->path, statFile);

    fclose(file);

    return entry;
}

void DestroyProcEntry(ProcEntry * entry) {
    /* param validation */
    if (entry == NULL) {
        return;
    }
    free(entry->comm);
    free(entry->path);

    free(entry);
}

void PrintProcEntry(ProcEntry *entry)
{
    unsigned long int utime = entry->utime / sysconf(_SC_CLK_TCK);
    unsigned long int stime = entry->stime / sysconf(_SC_CLK_TCK);
    fprintf(stdout, "%7d %7d %5c %5lu %5lu %7ld %-25s %-20s\n",
        entry->process_id,
        entry->parent_process_id,
        entry->state,
        utime,
        stime,
        entry->number_of_threads,
        entry->comm,
        entry->path);
}
