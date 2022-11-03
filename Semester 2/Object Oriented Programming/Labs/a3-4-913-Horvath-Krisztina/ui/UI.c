#include "UI.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

UI* create_ui(Service* s)
{
    UI* ui = malloc(sizeof(UI));
    if(ui == NULL)
        return NULL;
    ui->serv = s;

    return ui;
}

void destroy_ui(UI* ui)
{
    if(ui == NULL)
        return;

    /// destroy the Service
    destroy_service(ui->serv);
    /// free the UI memory
    free(ui);
}

void print_menu()
{
    printf("\n\nMenu:\n"
           "\t1 - add a country\n"
           "\t2 - delete a country\n"
           "\t3 - update a country(no migration)\n"
           "\t4 - update a country(with migration)\n"
           "\t5 - display all countries containing a given string\n"
           "\t6 - display all countries on a given continent(ascending by population)\n"
           "\t7 - undo\n"
           "\t8 - redo\n"
           "\t9 - lab3 activity\n"
           "\t0 - exit\n"
           "\n Bonus 1:\n"
           "\t10 - filtering by number of letters in the name(user gives number of letters)\n"
           "\t11 - display all countries on a given continent(descending by population)\n\n");
}


/**
	Verifies if the given command is valid (is either 1, 2, 3or 0)
	Input: command - integer
	Output: 1 - if the command is valid
	0 - otherwise
*/
int validCommand(int command)
{
    if (command >= 0 && command <= 11)
        return 1;
    return 0;
}

/**
	Reads an integer number from the keyboard. Asks for number while read errors encountered.
	Input: the message to be displayed when asking the user for input.
	Returns the number.
*/
int read_integer_number(const char* message)
{
    char s[16] = { 0 };
    int res = 0;
    int flag = 0;
    int r = 0;

    while (flag == 0)
    {
        printf("%s", message);
        int scanf_result = scanf("%15s", s);

        r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
        flag = (r == 1);
        if (flag == 0)
            printf("Error reading number!\n");
    }
    return res;
}


double read_double_number(const char* message)
{
    char s[16] = { 0 };
    double res = 0;
    int flag = 0;
    int r = 0;

    while (flag == 0)
    {
        printf("%s", message);
        int scanf_result = scanf("%15s", s);

        r = sscanf(s, "%lf", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
        flag = (r == 1);
        if (flag == 0)
            printf("Error reading number!\n");
    }
    return res;
}

void list_all_countries(UI* ui)
{
    if(ui == NULL)
        return;

    printf("\n");

    CountryRepo* repo= get_repo(ui->serv);
    int n = get_repo_length(repo);

    for(int i = 0; i < n; i++)
    {
        Country* c = get_country_on_pos(repo, i);
        char nice_print[100];
        to_string(c, nice_print);
        printf("%s", nice_print);
    }
}

void list_dynamic_array(UI* ui, DynamicArray* v)
{
    if(ui == NULL)
        return;

    printf("\n");

    int n = get_length(v);

    for(int i = 0; i < n; i++)
    {
        Country* c = get(v, i);
        char nice_print[100];
        to_string(c, nice_print);
        printf("%s", nice_print);
    }
}

/**
	Reads a string with spaces from the standard input.
	Input:	message - string, message to be shown to the user.
			maxStrSize - the maximum size for the string to be read
	Output: the string that was read.
*/
void readStringWithSpaces(const char* message, int maxStrSize, char str[])
{
    printf("%s", message);
    fgets(str, maxStrSize, stdin);
    // the newline is also read so we must eliminate it from the string
    size_t size = strlen(str) - 1;
    if (str[size] == '\n')
        str[size] = '\0';
}

int add_country_ui(UI* ui)
{
    char name[50], continent[50];
    double population;
    fgetc(stdin); /// read the newline, to prevent it from going further to fgets
    readStringWithSpaces("Please input the name: ", 50, name);
    readStringWithSpaces("Please input the continent: ", 50, continent);
    population = read_double_number("Please input the population number in millions: ");

    return add_country_srv(ui->serv, name, continent, population);
}

int delete_country_ui(UI* ui)
{
    char name[50];
    fgetc(stdin);
    readStringWithSpaces("Please introduce the name of the country that you would like to delete: ", 50, name);

    return delete_country_srv(ui->serv, name);
}

int update_no_migration_ui(UI* ui)
{
    char name[50];

    fgetc(stdin); /// read the newline, to prevent it from going further to fgets
    readStringWithSpaces("Please introduce the name of the country that you would like to update: ", 50, name);

    double population;
    population = read_double_number("Please input the population number in millions: ");

    return update_no_migration_srv(ui->serv, name, population);
}

int update_with_migration_ui(UI* ui)
{
    char country1[50], country2[50];

    double population;

    fgetc(stdin); /// read the newline, to prevent it from going further to fgets
    readStringWithSpaces("Please introduce the name of the country from where the migration is made: ", 50, country1);
    readStringWithSpaces("\nPlease introduce the name of the country to where the migration is made: ", 50, country2);
    population = read_double_number("\nPlease input the population migrating: ");

    return update_with_migration_srv(ui->serv, country1, country2, population);
}

void display_countries_containing_given_string_ui(UI* ui)     /// todo make it think in the serv
{
    char string[50];
    fgetc(stdin);
    readStringWithSpaces("Please introduce the substring that you would like to look for(null for empty string): ", 50, string);

    if( strcmp(string, "null") == 0)
        list_all_countries(ui);
    else
    {
        DynamicArray* v = display_countries_containing_given_string_srv(ui->serv, string);
        list_dynamic_array(ui, v);
    }
}

void display_countries_ascending_order(UI* ui)
{
    DynamicArray* v = malloc(sizeof(DynamicArray));
    v = lab3_activity(ui->serv);
    list_dynamic_array(ui, v);
}

void display_countries_on_given_continent_ascending(UI* ui)
{
    char continent[50];
    double population;
    fgetc(stdin); /// read the newline, to prevent it from going further to fgets
    readStringWithSpaces("Please input the continent(null for empty string): ", 50, continent);
    population = read_double_number("Please input the population number in millions: ");

    DynamicArray* v;/// = malloc(sizeof(DynamicArray));
    if (strcmp(continent, "null") == 0) {
        v = display_countries_by_population_srv(ui->serv, population);
    }
    else
        v = display_countries_on_given_continent_srv(ui->serv, continent, population);
    sort_ascending_by_population(v);
    list_dynamic_array(ui, v);
}

void display_countries_on_given_continent_descending(UI* ui)
{
    char continent[50];
    double population;
    fgetc(stdin); /// read the newline, to prevent it from going further to fgets
    readStringWithSpaces("Please input the continent(null for empty string): ", 50, continent);
    population = read_double_number("Please input the population number in millions: ");

    DynamicArray* v = malloc(sizeof(DynamicArray));
    if (strcmp(continent, "null") == 0) {
        v = display_countries_by_population_srv(ui->serv, population);
    }
    else
        v = display_countries_on_given_continent_srv(ui->serv, continent, population);
    sort_descending_by_population(v);
    list_dynamic_array(ui, v);
}

/// todo for bonus 1
void display_by_number_of_letters_in_name(UI *ui)
{
    int number = read_integer_number("Please introduce an integer number: ");
    if(number != 0)
    {
        DynamicArray* v =display_by_nr_letters(ui->serv, number);
        printf("The countries that have %d number of letters are: ", number);
        list_dynamic_array(ui, v);
    }
    else
        printf("There can be no countries with 0 letters in their name!");

}

int undo_ui(UI* ui)
{
    return undo(ui->serv);
}

int redo_ui(UI* ui)
{
    return redo(ui->serv);
}

void start_ui(UI* ui)
{
    while(1)
    {
        print_menu();
        int command = read_integer_number("Command: ");
        while(validCommand(command) == 0)
        {
            printf("Please input a valid command!\n");
            command = read_integer_number("Input command: ");
        }
        if(command == 0)
            break;
        switch(command)
        {
            case 1:  /// add
            {
                int res = add_country_ui(ui);
                if (res == 0)
                    printf("\n\t\tCountry successfully added.\n");
                else
                    printf("\n\t\tError! Country could not be added, as there is another country with the same name!\n");
                break;

            }
            case 2:  /// delete
            {
                int res = delete_country_ui(ui);
                if (res == 1)
                    printf("\n\t\tCountry deleted successfully!\n");
                else
                    printf("\n\t\tError! Country could not be deleted, as no country with that name exists!\n");
                break;
            }
            case 3:  /// update no migration
            {
                int res = update_no_migration_ui(ui);
                if (res == 1)
                    printf("\n\t\tCountry updated successfully!\n");
                else
                    printf("\n\t\tError! Country could not be updated, as no country with that name exists!\n");
                break;
            }
            case 4:  /// update with migration
            {
                int res = update_with_migration_ui(ui);
                if (res == 1)
                    printf("\n\t\tCountry updated successfully!(with migration)\n");
                else
                    printf("\n\t\tError! Country could not be updated, as no country with that name exists!(with migration)\n");
                break;
            }
            case 5:  /// display all countries containing a given string
            {
                /// todo leaks when searching for something different than null
                display_countries_containing_given_string_ui(ui);
                break;
            }
            case 6:
            {
                display_countries_on_given_continent_ascending(ui);
                break;
            }
            case 7:   /// undo
            {
                /// todo undo not working after there was an error, doesn't undo the previous operations
                /// todo not working correctly when the previous operations aren't correct from the first try
                int res = undo_ui(ui);

                if(res == 0)
                    printf("Undo successful!");
                else if(res == -1)
                    printf("There was an error!");
                else
                    printf("There were no operations made that can de undone!");
                break;
            }
            case 8:   /// redo
            {
                int res = redo_ui(ui);

                if(res == 0)
                    printf("Redo successful!");
                else if(res == -1)
                    printf("There was an error!");
                else
                    printf("There were no operations made that can de redone!");
                break;
            }
            case 9:  /// lab activity for w3, display elems sorted by name, not to sort the repo
            {
                display_countries_ascending_order(ui);
                break;
            }
            case 10:  /// bonus 1 a
            {
                display_by_number_of_letters_in_name(ui);
                break;
            }
            case 11:  /// bonus 2 a
            {
                display_countries_on_given_continent_descending(ui);
                break;
            }
        }
    }
}



