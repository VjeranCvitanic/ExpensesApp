#include "functions.h"
#include "trace.h"

const int months[][2] = 
{
    {1, 31},
    {2, 28},
    {3, 31},
    {4, 30},
    {5, 31},
    {6, 30},
    {7, 31},
    {8, 31},
    {9, 30},
    {10, 31},
    {11, 30},
    {12, 31},
};

const int leap_months[][2] = 
{
    {1, 31},
    {2, 29},
    {3, 31},
    {4, 30},
    {5, 31},
    {6, 30},
    {7, 31},
    {8, 31},
    {9, 30},
    {10, 31},
    {11, 30},
    {12, 31},
};

node_element_p create_new_element(char* name, float price, char* location, char* desc, date_element_p date)
{
    node_element_p q = (node_element_p)malloc(sizeof(node_element));
    if(!q)
    {
        trace_memory_error("Can't allocate memory for new node_element_p");
        return NULL;
    }

    strncpy(q->name_of_expense, name, MAX_NAME_LENGTH);
    strncpy(q->location, location, MAX_LOCATION_LENGTH);
    strncpy(q->description, desc, MAX_DESCRIPTION_LENGTH);
    q->price = price;

    q->date_of_expense = copy_date(date);
    q->next = NULL;

    return q;
}

date_element_p create_new_date(int day, int month, int year)
{
    date_element_p q = (date_element_p)malloc(sizeof(date_element));
    if(!q)
    {
        trace_memory_error("Can't allocate memory for new date_element_p");
        return NULL;
    }

    if(!is_date_valid(day, month, year))
    {
        trace("Date invalid!");
        return NULL;
    }

    q->day = day;
    q->month = month;
    q->year = year;

    return q;
}

date_element_p copy_date(date_element_p src_date)
{
    date_element_p q = (date_element_p)malloc(sizeof(date_element));
    if(!q)
    {
        trace_memory_error("Can't allocate memory for new date_element_p");
        return NULL;
    }

    q->day = src_date->day;
    q->month = src_date->month;
    q->year = src_date->year;

    return q;
}

int insert_after(node_element_p prev, node_element_p q)
{
    if(!prev || !q)
    {
        trace("Function argument is NULL");
        return EXIT_FAILURE;
    }

    q->next = prev->next;
    prev->next = q;

    return EXIT_SUCCESS;
}

int insert_by_date(node_element_p first, node_element_p q)
{
    node_element_p temp = first;

    if(!temp)
    {
        trace("Error while inserting element in node list, list is empty!");
        return EXIT_FAILURE;
    }

    for(; temp->next != NULL; temp = temp->next)
    {
        if(datecmp(temp->next->date_of_expense, q->date_of_expense) > 0)
        {
            insert_after(temp, q);
            return EXIT_SUCCESS;
        }
    }

    insert_after(temp, q);
    return EXIT_SUCCESS;
}

int datecmp(date_element_p a, date_element_p b)
{
    if(a->year == b->year)
    {
        if(a->month == b->month)
        {
            if(a->day == b->day)
            {
                return 0;
            }

            return a->day - b->day;
        }

        return a->month - b->month;
    }

    return a->year - b->year;
}

bool is_date_valid(int day, int month, int year)
{
    if(year < 2000)
    {
        trace_num("Invalid year entered: %d", year);
        return false;
    }

    if(1 <= month <= 12)
    {
        if(day <= 0)
        {
            trace_num("Invalid day entered: %d", day);
        }
        else if(is_leap_year(year))
        {
            if(day <= leap_months[month - 1][1])
                return true;
            trace_num("Invalid day entered: %d", day);
            return false;
        }

        else
        {
            if(day <= months[month - 1][1])
                return true;
            trace_num("Invalid day entered: %d", day);
            return false;
        }
    }

    else
    {
        trace_num("Invalid month entered: %d", month);
        return false;
    }

    return false;
}

bool is_leap_year(int year)
{
    if(year % 4 == 0)
        return true;
    return false;
}

void print_element(node_element_p q)
{
    printf("%s, %f, %s, ", q->name_of_expense, q->price, q->location);
    printf("<%s>, ", q->description);
    print_date(q->date_of_expense);
}

void print_date(date_element_p q)
{
    printf("%d.%d.%d.", q->day, q->month, q->year);
}

void print_list(node_element_p first)
{
    node_element_p temp = NULL;
    if(!first)
    {
        trace("List is empty");
        return;
    }

    temp = first->next;
    for(; temp; temp = temp->next)
    {
        new_line();
        print_element(temp);
        new_line();
    }
}

node_element_p input_new_node_element()
{
    char buy_name[MAX_NAME_LENGTH] = {0};
    char location[MAX_LOCATION_LENGTH] = {0};
    char buy_description[MAX_DESCRIPTION_LENGTH] = {0};
    float price = 0;
    int year = 0, month = 0, day = 0;
    date_element_p date = NULL;
    node_element_p q = NULL;

    getchar();
    printf("ENTER:\nbuy_name: ");
    scanf("%[^\n]s", buy_name);
    getchar();
    printf("\nprice: ");
    scanf("%f", &price);
    getchar();
    printf("\nbuy_location: ");
    scanf("%[^\n]s", location);
    getchar();
    printf("\nbuy_description: ");
    scanf("%[^\n]s", buy_description);
    getchar();
    printf("\ndate: ");
    printf("day: ");
    scanf("%d", &day);
    printf("month: ");
    scanf("%d", &month);
    printf("year: ");
    scanf("%d", &year);

    date = create_new_date(day, month, year);
    q = create_new_element(buy_name, price, location, buy_description, date);

    return q;
}

int enter_new_node_element(node_element_p first)
{
    node_element_p q = input_new_node_element();
    if(!q)
    {
        trace("Wrong buy info input, please try again.");
        return EXIT_FAILURE;
    }

    trace("Successfull input of new element!");

    insert_by_date(first, q);

    return EXIT_SUCCESS;
}

void print_main_menu()
{
    printf("Select action:");
    new_line();
    printf("1 -> print the list");
    new_line();
    printf("2 -> enter new buy");
    new_line();
    printf("3 -> delete a buy");
    new_line();
    printf("4 -> save the list to file");
    new_line();
    printf("5 -> read the list from file");
    new_line();
    printf("6 -> delete the list");
    new_line();
    printf("7 -> most expensive buy");
    new_line();
    printf("8 -> sum of all buys");
    new_line();
    printf("9 -> buys in selected time period");
    new_line();
    printf("10 -> exit");
    new_line();
}

void print_goodbye_msg()
{
    new_line();
    printf("Goodbye!");
    new_line();
    new_line();
}

int save_to_file(node_element_p first)
{
    FILE* fp = fopen(FILENAME, "w");
	if (!fp)
    {   
        trace("Couldn't open file!");
		return EXIT_FAILURE;
    }

	node_element_p temp = first->next;

	while (temp)
	{
		fprintf(fp, "%s   %.2f   %s   %s   %d:%d:%d", temp->name_of_expense, temp->price, temp->location,
        temp->description, temp->date_of_expense->day, temp->date_of_expense->month,
        temp->date_of_expense->year);
		temp = temp->next;
		if (temp)
			fprintf(fp, "\n");
	}

	fclose(fp);

    trace("Successfully saved data to file!");

	return EXIT_SUCCESS;
}

int read_from_file(node_element_p first)
{
    FILE* fp = NULL;
    char buffer[200] = {0};
	char buy_name[MAX_NAME_LENGTH] = { 0 };
	char location[MAX_LOCATION_LENGTH] = { 0 };
    char description[MAX_DESCRIPTION_LENGTH] = { 0 };
	float price = 0;
    int day = 0, month = 0, year = 0;
    date_element_p date_q = NULL;
	node_element_p q = NULL;

    delete_all(first);
    
    fp = fopen(FILENAME, "r");

	if (!fp)
    {
        trace("Couldn't open file!");
		return EXIT_FAILURE;
    }

	while (!feof(fp))
	{
        fgets(buffer, MAX_LINE, fp);

        if(strlen(buffer) == 0)
        {
            trace("Empty file!");
            return EXIT_SUCCESS;
        }
		
		sscanf(buffer, "%s   %f   %s   %s   %d:%d:%d\n", buy_name, &price, location, description, &day, &month, &year);

        printf("%s %.2f %s %s %d:%d:%d", buy_name, price, location, description, day, month, year);

        date_q = create_new_date(day, month, year);
		q = create_new_element(buy_name, price, location, description, date_q);

		insert_by_date(first, q);
	}

    trace("Successfully read data from file!");

	fclose(fp);

	return EXIT_SUCCESS;
}

int delete_next_element(node_element_p prev)
{
    node_element_p temp = prev->next->next;
    delete_date(prev->next);
    free(prev->next);
    prev->next = temp;
    return EXIT_SUCCESS;
}

int delete_all(node_element_p first)
{
    if(!first)
        return EXIT_SUCCESS;
    while(first->next)
    {
        delete_next_element(first);
    }

    trace("Deleted whole list!");

    return EXIT_SUCCESS;
}

int delete_date(node_element_p q)
{
    free(q->date_of_expense);
    return EXIT_SUCCESS;
}


