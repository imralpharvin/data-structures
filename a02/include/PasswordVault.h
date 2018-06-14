#ifndef _PASS_VAULT_
#define _PASS_VAULT_

#include <stdio.h>
#include <stdlib.h>

typedef struct user_struct {
     char username[64];
     char password[64];
} User;

void createUser(User newUser);
void signin(User theUser, HTable * passVault);
void loadFile(User theUser, HTable * passVault);
void loadTable(User theUser, HTable * passVault);


User * openUser(char username[], char password[] , HTable * passVault);

HTable *createVault(size_t size, int (*hashFunction)(size_t tableSize, char key[]),void (*destroyData)(void *data),void (*printData)(void *toBePrinted));

#endif
