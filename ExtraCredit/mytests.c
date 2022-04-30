#include <stdio.h>
#include <string.h>
#include "ProcEntry.h"

int testECSingleSpace(void) {
   char testName[] = "Extra Credit Single Space Test";
   ProcEntry * testEntry = CreateProcEntryFromFile("test_data_ec/stat.single_space");
   if (testEntry == NULL) {
      fprintf(stderr,"%s failed\n", testName);
      return 1;
   }
   fprintf(stderr, "%s: started\n", testName);
   fprintf(stdout,"\t- Generated Output: ");
   PrintProcEntry(testEntry);
   fprintf(stdout,"\t-  Expected Output:    1080     892     S     0     0       3 (hello world)             test_data_ec/stat.single_space\n");
   DestroyProcEntry(testEntry);
   fprintf(stdout, "%s: passed\n", testName);
   return 0;
}

int testECTwoSpaces(void) {
   char testName[] = "Extra Credit Two Spaces Test";
   ProcEntry * testEntry = CreateProcEntryFromFile("test_data_ec/stat.two_spaces");
   if (testEntry == NULL) {
      fprintf(stderr,"%s failed\n", testName);
      return 1;
   }
   fprintf(stderr, "%s: started\n", testName);
   fprintf(stdout,"\t- Generated Output: ");
   PrintProcEntry(testEntry);
   fprintf(stdout,"\t-  Expected Output:    1080     892     S     0     0       3 (hello beautiful world)   test_data_ec/stat.two_spaces\n");
   DestroyProcEntry(testEntry);
   fprintf(stdout, "%s: passed\n", testName);
   return 0;
}

int testECManySpaces(void) {
   char testName[] = "Extra Credit Many Spaces Test";
   ProcEntry * testEntry = CreateProcEntryFromFile("test_data_ec/stat.many_spaces");
   if (testEntry == NULL) {
      fprintf(stderr,"%s failed\n", testName);
      return 1;
   }
   fprintf(stderr, "%s: started\n", testName);
   fprintf(stdout,"\t- Generated Output: ");
   PrintProcEntry(testEntry);
   fprintf(stdout,"\t-  Expected Output:    1080     892     S     0     0       3 (h e l l o w o r l d)     test_data_ec/stat.many_spaces\n");
   DestroyProcEntry(testEntry);
   fprintf(stdout, "%s: passed\n", testName);
   return 0;
}

int testECSingleOpeningParan(void) {
   char testName[] = "Extra Credit Single Opening Paran Test";
   ProcEntry * testEntry = CreateProcEntryFromFile("test_data_ec/stat.single_opening_paran");
   if (testEntry == NULL) {
      fprintf(stderr,"%s failed\n", testName);
      return 1;
   }
   fprintf(stderr, "%s: started\n", testName);
   fprintf(stdout,"\t- Generated Output: ");
   PrintProcEntry(testEntry);
   fprintf(stdout,"\t-  Expected Output:    1080     892     S     0     0       3 (hello(world)             test_data_ec/stat.single_opening_paran\n");
   DestroyProcEntry(testEntry);
   fprintf(stdout, "%s: passed\n", testName);
   return 0;
}

int testECSingleClosingParan(void) {
   char testName[] = "Extra Credit Single Closing Paran Test";
   ProcEntry * testEntry = CreateProcEntryFromFile("test_data_ec/stat.single_closing_paran");
   if (testEntry == NULL) {
      fprintf(stderr,"%s failed\n", testName);
      return 1;
   }
   fprintf(stderr, "%s: started\n", testName);
   fprintf(stdout,"\t- Generated Output: ");
   PrintProcEntry(testEntry);
   fprintf(stdout,"\t-  Expected Output:    1080     892     S     0     0       3 (hello)world)             test_data_ec/stat.single_closing_paran\n");
   DestroyProcEntry(testEntry);
   fprintf(stdout, "%s: passed\n", testName);
   return 0;
}

int testECNestedParans(void) {
   char testName[] = "Extra Credit Nested Parans Test";
   ProcEntry * testEntry = CreateProcEntryFromFile("test_data_ec/stat.nested_parans");
   if (testEntry == NULL) {
      fprintf(stderr,"%s failed\n", testName);
      return 1;
   }
   fprintf(stderr, "%s: started\n", testName);
   fprintf(stdout,"\t- Generated Output: ");
   PrintProcEntry(testEntry);
   fprintf(stdout,"\t-  Expected Output:    1080     892     S     0     0       3 ((hello world))           test_data_ec/stat.nested_parans\n");
   DestroyProcEntry(testEntry);
   fprintf(stdout, "%s: passed\n", testName);
   return 0;
}

int testECSurroundedWords(void) {
   char testName[] = "Extra Credit Surrounded Words Test";
   ProcEntry * testEntry = CreateProcEntryFromFile("test_data_ec/stat.surrounded_words");
   if (testEntry == NULL) {
      fprintf(stderr,"%s failed\n", testName);
      return 1;
   }
   fprintf(stderr, "%s: started\n", testName);
   fprintf(stdout,"\t- Generated Output: ");
   PrintProcEntry(testEntry);
   fprintf(stdout,"\t-  Expected Output:    1080     892     S     0     0       3 ((hello) (world))         test_data_ec/stat.surrounded_words\n");
   DestroyProcEntry(testEntry);
   fprintf(stdout, "%s: passed\n", testName);
   return 0;
}

int main(void) {

   int status = 0;
   status += testECSingleSpace();
   status += testECTwoSpaces();
   status += testECManySpaces();
   status += testECSingleOpeningParan();
   status += testECSingleClosingParan();
   status += testECNestedParans();
   status += testECSurroundedWords();

   return status;
}
