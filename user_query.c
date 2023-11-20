#include "user_query.h"

node_element_p most_expensive_buy(node_element_p first)
{
    float max = -1;
    node_element_p max_element = NULL;
    node_element_p temp = first;
    if(!temp)
        return NULL;

    while(temp->next)
    {
        if(temp->next->price > max)
        {
            max_element = temp->next;
            max = max_element->price;
        }

        temp = temp->next;
    }

    return max_element;
}

void query(node_element_p first)
{
    node_element_p temp = most_expensive_buy(first);

    if(temp)
        print_element(temp);
}