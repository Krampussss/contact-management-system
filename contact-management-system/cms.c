#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct records
{
    char name[50];
    char phone[15];
} list;

FILE *fp;

void addContact();
void viewContacts();
void deleteContact();
void searchContact();
void editContact();

int main()
{
    printf("\n========WELCOME TO CONTACT MANAGEMENT SYSTEM========\n");
    int choice;
    char toContd;
    code:
    do
    {
        printf("\n\nWhat would you like to do?\n\n");
        printf("\n1. Add New Contact\n2. View existing contacts\n3. Delete a contact\n4. Search for a contact\n5. Edit a contact\n6. Exit\n");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addContact();
            break;
        case 2:
            viewContacts();
            break;
        case 3:
            deleteContact();
            break;
        case 4:
            searchContact();    
            break;
        case 5:
            editContact();
            break;
        case 6:
            printf("Thank you for using Contact Management System. Now Exiting the System");
            return 0;
        default:
            printf("Invalid Choice!!");
            break;
        }

        fflush(stdin);
        printf("\nDo you want to continue? (Y/N): ");
        scanf("%c",&toContd);
    } 
    while (toContd == 'y' || toContd == 'Y');
    
    if (toContd == 'n' || toContd == 'N')
    {
        printf("Thank you for using Contact Management System. Now Exiting the System");
        return 0;
    }

    else
    {
        printf("Invalid Choice, Exitting System");
        return 0;
    }

    return 0;
}

void addContact()
{
    fp = fopen("record.txt", "a");

    printf("\n\t\tAdding Contact\n");
    fflush(stdin);
    printf("\nEnter Name\t:");
    fgets(list.name, 50, stdin);

    fflush(stdin);
    printf("Enter Number\t:");
    fgets(list.phone, 15, stdin);

    fwrite(&list, sizeof(list), 1, fp);
    printf("\nContact Successfully Added");

    fclose(fp);
}

void viewContacts()
{
    fp = fopen("record.txt", "r");

    printf("\n\t\tViewing Contacts\n");

    while (fread(&list, sizeof(list), 1, fp) == 1)
    {
        printf("Name: %s", list.name);
        printf("Number: %s", list.phone);
        printf("\n--------------------------\n");
    }

    fclose(fp);
}

void deleteContact()
{
    FILE *temp;
    char toDelete[50];
    int found = 0;

    printf("\n\t\tDeleting Contact\n");
    printf("Enter the Name of the contact you want to delete (Please enter full name) : ");
    fflush(stdin);
    fgets(toDelete, 50, stdin);

    fp = fopen("record.txt", "r");
    temp = fopen("temp.txt", "w");

    while (fread(&list, sizeof(list), 1, fp) == 1)
    {
        if (strcmp(list.name, toDelete) == 0)
        {
            found = 1;
            printf("\nContact found and deleted.\n");
        }
        else
        {
            fwrite(&list, sizeof(list), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("record.txt");
    rename("temp.txt", "record.txt");

    if (found == 0)
    {
        printf("\nContact not found.\n");
    }
}

void searchContact()
{
    char toSearch[50];
    int found = 0;

    printf("\n\t\tSearching for a Contact\n");
    printf("Enter the Name of the contact you want to search (Please enter full name): ");
    fflush(stdin);
    fgets(toSearch, 50, stdin);

    fp = fopen("record.txt", "r");

    while (fread(&list, sizeof(list), 1, fp) == 1)
    {
        if (strcmp(list.name, toSearch) == 0)
        {
            found = 1;
            printf("\nContact found:\n");
            printf("Name: %s", list.name);
            printf("Number: %s", list.phone);
            printf("\n--------------------------\n");
            break;
        }
    }

    fclose(fp);

    if (found == 0)
    {
        printf("\nContact not found.\n");
    }
}

void editContact()
{
    FILE *temp;
    char contactName[50], newContactName[50], newContactNumber[15];
    int found = 0;

    printf("\n\t\tEditing Contact\n");
    printf("Enter the Name of the contact you want to edit (Please enter full name) : ");
    fflush(stdin);
    fgets(contactName, 50, stdin);

    fp = fopen("record.txt", "r");
    temp = fopen("temp.txt", "w");

    while (fread(&list, sizeof(list), 1, fp) == 1)
    {
        if (strcmp(list.name, contactName) == 0)
        {
            found = 1;
            printf("\nContact found. Enter new details: ");
            printf("\nEnter new Name: ");
            fflush(stdin);
            fgets(newContactName, 50, stdin);
            printf("\nEnter new Number: ");
            fflush(stdin);
            fgets(newContactNumber, 15, stdin);

            strcpy(list.name, newContactName);
            strcpy(list.phone, newContactNumber);
        }

        fwrite(&list, sizeof(list), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("record.txt");
    rename("temp.txt", "record.txt");

    if (found == 1)
    {
        printf("\nContact successfully edited.\n");
    }
    else
    {
        printf("\nContact not found.\n");
    }
}


