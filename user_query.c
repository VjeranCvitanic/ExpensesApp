#include "user_query.h"

node_element_p most_expensive_buy(node_element_p first)
{
    float max = -1;
    node_element_p max_element = NULL;
    node_element_p temp = first;
    if(!temp)
        return NULL;

    temp = temp->next;

    while(temp)
    {
        if(temp->price > max)
        {
            max_element = temp;
            max = max_element->price;
        }

        temp = temp->next;
    }

    return max_element;
}

float sum_of_all(node_element_p first)
{
    float sum = 0;
    node_element_p temp = first;

    if(!temp)
        return 0;
    
    temp = temp->next;

    while(temp)
    {
        sum += temp->price;
        temp = temp->next;
    }

    return sum;
}

void buys_in_time_interval(node_element_p first, date_element_p start, date_element_p end)
{
    node_element_p temp = first->next;
    float sum = 0;

    while(temp)
    {
        if(datecmp(temp->date_of_expense, start) >= 0 && datecmp(temp->date_of_expense, end) <= 0)
        {
            print_element(temp);
            printf("\n");
            sum += temp->price;
        }
        temp = temp->next;
    }

    printf("\n\nSum of spendings between %d:%d:%d - %d:%d:%d is %f\n\n", start->day, start->month, start->year, end->day, end->month, end->year, sum);
}

void query(node_element_p first, int flag)
{
    node_element_p temp = NULL;
    date_element_p start = NULL;
    date_element_p end = NULL;
    float result = 0;
    int day = 0, month = 0, year = 0;

    switch(flag)
    {
        case 1:
            temp = most_expensive_buy(first);
            if(temp)
                print_element(temp);
            break;
        case 2:
            result = sum_of_all(first);
            printf("Sum is: %f\n", result);
            break;
        case 3:
            printf("Enter start date:\n");
            printf("day: ");
            scanf("%d", &day);
            printf("month: ");
            scanf("%d", &month);
            printf("year: ");
            scanf("%d", &year);

            start = create_new_date(day, month, year);

            printf("Enter end date:\n");
            printf("day: ");
            scanf("%d", &day);
            printf("month: ");
            scanf("%d", &month);
            printf("year: ");
            scanf("%d", &year);

            end = create_new_date(day, month, year);

            if(start && end)
                buys_in_time_interval(first, start, end);
            else
                printf("Wrong date input");
            break;
        default:
            break;
    }
}