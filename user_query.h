#ifndef USER_QUERY
#define USER_QUERY

#include "functions.h"

node_element_p most_expensive_buy(node_element_p first);

float sum_of_all(node_element_p first);

void buys_in_time_interval(node_element_p first, date_element_p start, date_element_p end);

void query(node_element_p first, int flag);

#endif