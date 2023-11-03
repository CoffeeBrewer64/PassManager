#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_PASSWORD_LENGTH 50
#define MAX_KEYWORD_LENGTH 5
#define FILENAME "PASS.txt"

// Structure to store user information
struct User
{
    char username[50];
    char password[MAX_PASSWORD_LENGTH];
    char keyword[MAX_KEYWORD_LENGTH];
};

// Array to store user information
struct User users[MAX_USERS];
int userCount = 0;

// Function to add a new user
void addUser()
{
    if (userCount < MAX_USERS)
    {
        printf("Enter username: ");
        scanf("%s", users[userCount].username);
        printf("Enter password: ");
        scanf("%s", users[userCount].password);
        printf("Enter a 5-letter keyword: ");
        scanf("%s", users[userCount].keyword);
        userCount++;

        // Save user data to the file
        saveUserData();
        printf("User added successfully.\n");
    }
    else
    {
        printf("User storage is full.\n");
    }
}

// Function to retrieve a user's password
void retrievePassword()
{
    char username[50];
    printf("Enter username: ");
    scanf("%s", username);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(username, users[i].username) == 0)
        {
            char enteredKeyword[MAX_KEYWORD_LENGTH];
            printf("Enter the 5-letter keyword: ");
            scanf("%s", enteredKeyword);

            if (strcmp(enteredKeyword, users[i].keyword) == 0)
            {
                printf("Password for %s: %s\n", username, users[i].password);
            }
            else
            {
                printf("Keyword does not match.\n");
            }
            return;
        }
    }

    printf("User not found.\n");
}

// Function to delete a user's password
void deleteUser()
{
    char username[50];
    printf("Enter username to delete: ");
    scanf("%s", username);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(username, users[i].username) == 0)
        {
            // Remove the user by shifting remaining users
            for (int j = i; j < userCount - 1; j++)
            {
                strcpy(users[j].username, users[j + 1].username);
                strcpy(users[j].password, users[j + 1].password);
                strcpy(users[j].keyword, users[j + 1].keyword);
            }

            userCount--;

            // Save user data to the file after deleting
            saveUserData();
            printf("User deleted successfully.\n");
            return;
        }
    }

    printf("User not found.\n");
}

// Function to delete the password file
void deletePasswordFile()
{
    char enteredKeyword[MAX_KEYWORD_LENGTH];
    printf("Enter the 5-letter keyword to delete the password file: ");
    scanf("%s", enteredKeyword);

    // Verify the keyword before deleting the file
    if (userCount > 0 && strcmp(enteredKeyword, users[0].keyword) == 0)
    {
        if (remove(FILENAME) == 0)
        {
            printf("Password file deleted successfully.\n");
            userCount = 0; // Reset user count
        }
        else
        {
            printf("Unable to delete the password file.\n");
        }
    }
    else
    {
        printf("Keyword does not match or there are no users.\n");
    }
}

// Function to save user data to a file
void saveUserData()
{
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL)
    {
        printf("Error opening the file for writing.\n");
        exit(1);
    }

    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "%s %s %s\n", users[i].username, users[i].password, users[i].keyword);
    }

    fclose(file);
}

// Function to load user data from a file
void loadUserData()
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        return; // File doesn't exist yet.
    }

    while (fscanf(file, "%s %s %s", users[userCount].username, users[userCount].password, users[userCount].keyword) == 3)
    {
        userCount++;
    }

    fclose(file);
}

int main()
{
    // Load user data from the file at the start
    loadUserData();

    int choice;

    while (1)
    {
        printf("\n1. Add a new user\n2. Retrieve password\n3. Delete user\n4. Delete password file\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addUser();
            break;
        case 2:
            retrievePassword();
            break;
        case 3:
            deleteUser();
            break;
        case 4:
            deletePasswordFile();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
