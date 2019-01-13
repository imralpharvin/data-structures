/**
 * @file PasswordVault.h
 * @author Ralph Arvin De Castro
 * @date June 2018
 * @brief File containing the function definitions needed for password struct
 */

#ifndef _PASS_VAULT_
#define _PASS_VAULT_

#include <stdio.h>
#include <stdlib.h>
#include "HashTableAPI.h"

/**
 *User. It contains elements which is the username or password.
 **/
typedef struct user_struct
{
  char username[100];
  char password[100];
} User;

/**Function to create user by creating a bin file as the password vault
*@return user struct
*@param passVault hashtable that includes the usernames and password
**/
User createUser(HTable * passVault);

/**Function to sign in the user by loading the contents of the file
*@param theUser the user with username and password
*@param passVault hashtable that acts as the password vault
**/
void signin(User theUser, HTable * passVault);

/**Function to add password to hashtable
*@param theUser pointer to user struct with username and password
*@param passVault hashtable that acts as the password vault
**/
void addPassword(User * theUser, HTable * passVault);

/**Function to change a password of a system in the hashtable
*@param theUser pointer to user struct with username and password
*@param passVault hashtable that acts as the password vault
**/
void changePassword(User * theUser, HTable * passVault);

/**Function to return a password by username
*@return pointer to password string
*@param theUser pointer to user struct with username and password
*@param passVault hashtable that acts as the password vault
**/
char * getPassword(User * theUser, HTable * passVault );

/**Function to remove a system in hashtable
*@param theUser pointer to user struct with username and password
*@param passVault hashtable that acts as the password vault
**/
void removePassword(User * theUser, HTable * passVault );

/**Function to load file to hash table
*@param theUser the user with username and password
*@param passVault hashtable that acts as the password vault
**/
void loadFile(User theUser, HTable * passVault);

/**Function to load hashtable to the binary file or password vault
*@param theUser the user with username and password
*@param passVault hashtable that acts as the password vault
**/
void loadTable(User theUser, HTable * passVault);

/**Function to print the contents of vault
*@param theUser the user with username and password
*@param passVault hashtable that acts as the password vault
**/
void printVault(User theUser, HTable * passVault);

/**Function to point the hash table to the appropriate functions. Allocates memory to the struct and table based on the size given.
*@return pointer to the hash table
*@param size size of the hash table
*@param hashFunction function pointer to a function to hash the data
*@param destroyData function pointer to a function to delete a single piece of data from the hash table
*@param printNode function pointer to a function that prints out a data element of the table
**/
HTable *createVault(size_t size, int (*hashFunction)(size_t tableSize, char key[]),void (*destroyData)(void *data),void (*printData)(void *toBePrinted));

/**Function to create a path name for creating a file
*@return character string that contains the pathway
*@param theUser the user with username and password
**/
char * createPathname (User theUser);

/**Function to create an index for hashtable
*@return integer that includes the index
*@param tableSize size of hashtable
*@param key character string for password
**/
int hashFunction(size_t tableSize, char key[]);

/**Function to print passwords
*@param toBePrinted the data to be printed
**/
void printPassword(void *toBePrinted);

/**Function to destroy password
*@param toBeDeleted the data to be destroyed
**/
void deletePassword(void *toBeDeleted);

/**Function to check if system exist on hashtable
*@return integer that includes the index
*@param tableSize size of hashtable
*@param key character string for password
**/
int checkSystem(User * theUser, HTable * passVault );
#endif
