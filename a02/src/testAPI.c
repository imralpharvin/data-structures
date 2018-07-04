#include <stdio.h>
#include <string.h>
#include "HashTableAPI.h"
#include "PasswordVault.h"

int main ()
{
	char key[100] = "facebook";
	char password[100] = "pass";
	char key2[100] = "instagram";
	char password2[100] = "pass2";

  printf("*** Test #1: createTable ***\n");
  printf("Expected:\nThe table is empty\n");
	printf("HTable is NOT null\n\n");
	HTable * newHTable = createTable(109, hashFunction, deletePassword, printPassword);
	printf("Received:\n");
	printTable(newHTable);
	printf("%s\n", newHTable ? "HTable is NOT null" : "HTable is NULL");
	printf("%s", newHTable ? "   ***PASS***   \n\n" : "   ***FAILED***   \n\n");

	printf("*** Test #2: createNode ***\n");
  printf("Expected:\n");
	printf("Node is NOT null\n\n");
  Node *newNode = createNode(key, password);
	printf("Received:\n");
	printf("%s\n", newNode ? "Node is NOT null" : "Node is NULL");
	printf("%s", newNode ? "   ***PASS***   \n\n" : "   ***FAILED***   \n\n");

  printf("*** Test #3: insertData ***\n");
	printf("Expected:\nHash :6 | Key :facebook | Data : pass\nHash :98 | Key :instagram | Data : pass2\n");
  insertData(newHTable, key, password);
	insertData(newHTable, key2, password2);
	printf("Received:\n");
	printTable(newHTable);
  printf("   ***PASS***   \n\n");

	printf("*** Test #4: removeData ***\n");
	printf("Expected:\nHash :6 | Key :facebook | Data : pass\n");
	removeData(newHTable, key2);
	printf("Received:\n");
	printTable(newHTable);

	printf("\n*** Test #5: lookupData ***\n");
	printf("Expected: pass\n");
	Node * temp = lookupData(newHTable, key);
	printf("Received: ");
	newHTable->printData(temp);
	printf("   ***PASS***   \n\n");

	printf("\n*** Test #6: changeData ***\n");
	printf("Expected:\nHash :6 | Key :facebook | Data : changed\n");
	char change[100] = "changed";
	changeData(newHTable, key, change);
	printf("Received:\n");
	printTable(newHTable);
	printf("   ***PASS***   \n\n");

	printf("\n*** Test #7: checkKey ***\n");
	printf("Expected:\n0\n");
	char check[100] = "check";
	printf("Received:\n");
	printf("%d\n", checkKey(newHTable, check));
	printf("Expected:\n1\n");
	printf("Received:\n");
	printf("%d\n", checkKey(newHTable, key));
	printf("   ***PASS***   \n\n");

	printf("*** Test #8: destroyTable ***\n");
	printf("Expected:\nTable is NULL\n");
	destroyTable(newHTable);
	newHTable = NULL;
	printf("Received:\n");
	printf("%s\n", newHTable != NULL ? "Table is NOT null" : "Table is NULL");
	printf("%s", newHTable != NULL ? "   ***FAILED***   \n\n" : "   ***PASS***   \n\n");

  return 0;
}
