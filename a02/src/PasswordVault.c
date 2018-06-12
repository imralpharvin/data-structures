#include <stdio.h>
#include "HashTableAPI.h"
#include "PasswordVault.h"

User * createUser(char username[], char password[])
{
  User * newUser = malloc(sizeof(User));

  newUser->username = username;
  newUser->password = password;

  return newUser;
}
