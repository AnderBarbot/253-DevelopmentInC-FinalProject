/* 
 * File: mytests.c
 * Author: Ander Barbot 
 * Date: Fri Apr 29 14:43:10 MDT 2022
 * Description: Unit tests for ProcEntry functions
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include "ProcEntry.h"

#define UNUSED(x) (void)(x)
#define DISP_MSG(MSG)                                \
   if (write(STDOUT_FILENO, MSG, strlen(MSG)) == -1) \
      perror("write");

/* error Handler */
static void handler(int sig, siginfo_t *si, void *unused){
   UNUSED(sig);
   UNUSED(unused);
   if (si->si_signo == SIGSEGV){
      DISP_MSG("failed (segfault)\n")
      exit(1);
   }
}

/* UNIT TESTS */
int testCreateDestroy(void){
   char testName[] = "Create/Destroy Test";
   ProcEntry *testProc = CreateProcEntry();
   if (testProc == NULL){
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }
   DestroyProcEntry(testProc);
   fprintf(stderr, "%s passed\n", testName);
   return 0;
}

int testCreateFromFileDestroy(void){
   char testName[] = "CreateFromFile/Destroy Test";
   ProcEntry *testProc = CreateProcEntryFromFile("/proc/1/stat");
   if (testProc == NULL){
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }
   DestroyProcEntry(testProc);
   fprintf(stderr, "%s passed\n", testName);
   return 0;
}

int testCreateFromFilePrintDestroy(void){
   char testName[] = "CreateFromFile/Print/Destroy Test";
   ProcEntry *testProc = CreateProcEntryFromFile("/proc/1/stat");

   PrintProcEntry(testProc);

   if (testProc == NULL){
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }
   DestroyProcEntry(testProc);
   fprintf(stderr, "%s passed\n", testName);
   return 0;
}

int testCreateFromNULLFile(void){
   char testName[] = "CreateFromFile NULL Test";
   ProcEntry *testProc = CreateProcEntryFromFile(NULL);
   if (testProc == NULL){
      fprintf(stderr, "%s passed\n", testName);
      return 0;
   }
   DestroyProcEntry(testProc);
   fprintf(stderr, "%s failed\n", testName);
   return 1;
}

int testCreateFromNonExistentFile(void){
   char testName[] = "CreateFromFile DoesNotExist Test";
   ProcEntry *testProc = CreateProcEntryFromFile("nonExistent");
   if (testProc == NULL)
   {
      fprintf(stderr, "%s passed\n", testName);
      return 0;
   }
   DestroyProcEntry(testProc);
   fprintf(stderr, "%s failed\n", testName);
   return 1;
}

int testCreateFromInvalidFormatFile(void){
   char testName[] = "CreateFromFile InvalidFormat Test";
   ProcEntry *testProc = CreateProcEntryFromFile("InvalidFormat");
   if (testProc == NULL){
      fprintf(stderr, "%s passed\n", testName);
      return 0;
   }
   DestroyProcEntry(testProc);
   fprintf(stderr, "%s failed\n", testName);
   return 1;
}

int main(void){
   testCreateDestroy();

   testCreateFromFileDestroy();

   testCreateFromFilePrintDestroy();

   testCreateFromNULLFile();

   testCreateFromNonExistentFile();

   testCreateFromInvalidFormatFile();

   return 0;
}
