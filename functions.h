#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 20
#define MAX_DESCRIPTION_LENGTH 50
#define MAX_LOCATION_LENGTH 15
#define MAX_LINE (MAX_DESCRIPTION_LENGTH + MAX_NAME_LENGTH + MAX_LOCATION_LENGTH + 40)

#define FILENAME "./expenses.txt"

extern const int months[][2];
extern const int leap_months[][2];

struct date_element_;
typedef struct date_element_* date_element_p;
typedef struct date_element_
{
    int day;
    int month;
    int year;
}date_element;

struct node_element_;
typedef struct node_element_* node_element_p;
typedef struct node_element_
{
    char name_of_expense[MAX_NAME_LENGTH];
    float price;
    char location[MAX_LOCATION_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    date_element_p date_of_expense;
    node_element_p next;
}node_element;

node_element_p create_new_element(char* name, float price, char* location, char* description, date_element_p date);

date_element_p create_new_date(int day, int month, int year);

date_element_p copy_date(date_element_p src_date);

int insert_after(node_element_p prev, node_element_p q);

int insert_by_date(node_element_p first, node_element_p q);

int datecmp(date_element_p a, date_element_p b);

bool is_date_valid(int day, int month, int year);

void print_element(node_element_p q);

void print_date(date_element_p q);

bool is_leap_year(int year);

void print_list(node_element_p first);

node_element_p input_new_node_element();

int enter_new_node_element(node_element_p first);

void print_main_menu();

void print_goodbye_msg();

int save_to_file(node_element_p first);

int read_from_file(node_element_p first);

int delete_next_element(node_element_p prev);

int delete_all(node_element_p first);

int delete_date(node_element_p q);
#endif

