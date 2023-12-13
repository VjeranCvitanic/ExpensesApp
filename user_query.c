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

void query(node_element_p first, int flag)
{
    node_element_p temp = NULL;
    float result = 0;
    switch(flag)
    {
        case 1:
            temp = most_expensive_buy(first);
            break;
        case 2:
            result = sum_of_all(first);
            printf("Sum is: %f\n", result);
            break;
    }

    if(temp)
        print_element(temp);
}