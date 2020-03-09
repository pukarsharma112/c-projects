7#include <stdio.h>
#include <conio.h>
#include <string.h>

#define FILE_PATH "__data__/contacts.bin"
#define TEMP_FILE "__data__/temp.bin"

// structure for contact data
struct contact
{
    char name[50];
    long long unsigned int phone;
    char email [50];
    char address[100];
} c;

// file pointers
FILE *fptr; // for contact file
FILE *tempfile; // for temporary file

// global variables
char opt;

// definitions for the functions used in my program
char option_menu();
void read_details(char);
void add_contact();
void search_contact();
void list_contacts();
void edit_contact();
void delete_contact();

// print the option menu to the screen
char option_menu()
{
    printf("|====================================|\n");
    printf("|     Contact Management System      |\n");
    printf("|====================================|\n");
    printf("| a. Add Contact                     |\n");
    printf("| b. Show Contacts                   |\n");
    printf("| c. Search Contact                  |\n");
    printf("| d. Delete Contact                  |\n");
    printf("| e. Edit Contact                    |\n");
    printf("| x. Exit                            |\n");
    printf("|====================================|\n");
    printf("|>> ");
    return tolower(_getch());
}

void read_details(char mode)
{
    struct contact temp;
read_name:
    fflush(stdin);
    printf("> Enter the name:\t\t");
    gets(c.name);

    // check if name field is empty or not
    if((strcmp(c.name, "") == 0) || (strcmp(c.name, " ") == 0))
        goto read_name;

    // check if the name exists in contact
    if(mode == 'c')
    {
        fptr = fopen(FILE_PATH, "rb");

        while(fread(&temp, sizeof(temp), 1, fptr))
        {
            if(stricmp(c.name, temp.name) == 0)
            {
                printf("  This name already exists in the contact list.\n");
                goto read_name;
            }
        }

        fclose(fptr);
    }


    fflush(stdin);
    printf("> Enter phone number:\t\t");
    scanf("%llu", &c.phone);

    fflush(stdin);
    printf("> Enter the email address:\t");
    scanf("%s", c.email);

    fflush(stdin);
    printf("> Address (Optional) :\t\t");
    gets(c.address);
}

// function to add new contact
void add_contact()
{
add_contact:
    system("cls");
    printf("Enter the details of your contact...\n\n");

    read_details('c'); // read user's detail in create mode

    // save to file
    fptr = fopen(FILE_PATH, "ab"); // reopen the file in append mode
    fwrite(&c, sizeof(c), 1, fptr);
    fclose(fptr);

    system("cls");

    if(fwrite == NULL)
        printf("An error occured while saving your contact.");
    else
        printf("Your new contact was saved successfully!");
    printf("\nPress any key to continue...");
    _getch();
    system("cls");
    printf("Do you want to add another contact [Y/n]:\t");
    opt = _getch();
    if(opt == 'N' || opt == 'n')
        system("cls");
    else
        goto add_contact;
}

// function to list all saved contacts
void list_contacts()
{
    int id = 1;
    char ans;
    system("cls");

    fptr = fopen(FILE_PATH, "rb");

    printf("Listing all of your contacts...\n");

    while(fread(&c,sizeof(c),1,fptr))
    {
        printf("\n#%d\n", id);
        printf("Name:\t\t%s\n", c.name);
        printf("Phone number:\t%llu\n", c.phone);
        printf("Email address:\t%s\n", c.email);
        printf("Address:\t%s\n", c.address);
        id++;
    }
    fclose(fptr);

    if(id == 1)
    {
        system("cls");
        printf("No contacts to list...\n");
        printf("Would you like to add new contact [y/N]:\t");
        ans = _getch();
        if(ans == 'y' || ans == 'Y')
            add_contact();
    }

    printf("\n\nPress any key to go back to main menu...");
    _getch();
    system("cls");
}

// function to search the contact with provided name
void search_contact()
{
    char name[20];
    int result;

search_contact:
    result = 0;
    system("cls");
    fptr = fopen(FILE_PATH, "rb");

read_name:
    fflush(stdin);
    printf("Enter the name of the contact to search for :\t");
    gets(name);

    if( (strcmp(name, "") == 0) || ( strcmp(name, " ") == 0) )
        goto read_name;

    while( fread(&c, sizeof(c), 1, fptr) )
    {
        if(stricmp(c.name, name) == 0)
        {
            printf("\nName:\t\t%s\n", c.name);
            printf("Phone number:\t%llu\n", c.phone);
            printf("Email address:\t%s\n", c.email);
            printf("Address:\t%s\n", c.address);
            result = 1;
        }
    }

    if(result == 0)
    {
        printf("No result found for your search query...\n");

    }

    printf("\nWould you like to search again [Y/n]:\t");
    opt = _getch();

    if(opt == 'n' || opt == 'N');
    else   goto search_contact;
    // close the file
    fclose(fptr);
    system("cls");
}

// function to delete the contact
void delete_contact()
{
    int found;
    char name[50];

delete_contact:
    found = 0;

    fptr = fopen(FILE_PATH, "rb");
    tempfile = fopen(TEMP_FILE, "ab");

    system("cls");

    fflush(stdin);
    printf("Please enter the name of the contact to delete:\t\t");
    gets(name);

    system("cls");

    while( fread(&c, sizeof(c), 1, fptr) )
    {
        if(found == 0 && stricmp(name, c.name) == 0)
        {
            printf("*********** Contact to delete: ***********\n");
            printf("Name:\t\t%s\n", c.name);
            printf("Phone number:\t%llu\n", c.phone);
            printf("Email address:\t%s\n", c.email);
            printf("Address:\t%s\n", c.address);
            printf("****************************************\n\n");
            printf("Press any key to proceed...\n");
            _getch();
            found = 1;
        }

        if(stricmp(name, c.name) != 0)
            fwrite(&c, sizeof(c), 1, tempfile);
    }

    fclose(fptr);
    fclose(tempfile);
    remove(FILE_PATH);
    rename(TEMP_FILE, FILE_PATH);

    if(found == 1)
        printf("The contact was deleted successfully.\n");
    else
        printf("No contact found with provided name...\n");

    printf("Do you want to delete another contact [Y/n]:\t");
    opt = _getch();

    if(opt == 'Y' || opt == 'y')
        goto delete_contact;

    system("cls");
}

// function to add contact
void edit_contact()
{
    int found;
    struct contact temp;

edit_contact:
    found = 0;
    fptr = fopen(FILE_PATH, "rb");
    tempfile = fopen(TEMP_FILE, "ab");

    system("cls");
    fflush(stdin);
    printf("> Enter the name of the contact to edit:\t");
    gets(temp.name);

    while( fread(&c, sizeof(c), 1, fptr) )
    {
        if(stricmp(c.name, temp.name) == 0)
            found = 1;
        if(stricmp(c.name, temp.name) != 0)
            fwrite(&c, sizeof(c), 1, tempfile);
    }

    if(found == 1)
    {
        printf("> Contact [%s] selected to update...\n", temp.name);
        read_details('u'); // read user's detail in update mode
        printf("\nUpdating the contact...\n");
        fwrite(&c, sizeof(c), 1, tempfile);
        printf("> The contact was updated successfully.\n");
    }

    else
    {
        printf("> No contact with provided name was found...\n\n");
    }

    fclose(fptr);
    fclose(tempfile);
    remove(FILE_PATH);
    rename(TEMP_FILE, FILE_PATH);

    printf("> Enter any key to go to main menu.");
    _getch();
    system("cls");

}

// main function
void main()
{
    int running = 1;
    system("cls");

    // continue the program till running != 0
    while(running)
    {
        switch(option_menu())
        {
        case 'a':
            add_contact();
            break;

        case 'b':
            list_contacts();
            break;

        case 'c':
            search_contact();
            break;

        case 'd':
            delete_contact();
            break;
        case 'e':
            edit_contact();
            break;
        case 'x':
        case 27:
            // exit the program
            running = 0;
            break;

        default:
            /* print the error message to console and reprint menu if
               the invalid option is selected */
            system("cls");
            printf(" Please select a valid option.\n");
            break;
        }
    }
}
