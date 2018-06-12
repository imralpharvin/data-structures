#include <stdio.h>
#include <stdlib.h>

#include "HashTableAPI.h"

typedef struct user_struct {
     char username[64];
     char password[64];
} User;

User * createUser(char username[], char password[]);
