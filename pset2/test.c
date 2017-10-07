#include <stdio.h>
#include <cs50.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>
#define _XOPEN_SOURCE

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./test password");
        return 1;
    }
    string password = argv[1];
    printf("Password: %s\n", password);
    char *hashedPassword = crypt(password, "50");
    printf("Hash: %s\n", hashedPassword);
}