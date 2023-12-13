#include "user_query.h"
#include "trace.h"

int do_action(int input, node_element_p first, int* info);

int main(int argc, char** argv)
{
    node_element head = {"", 0.0, "", "", NULL, NULL};
    node_element_p first = &head;
    char input_string[5];
    int input = 0;
    int info = 0; // 0 -> OK, -1 -> quit

    print_line();
    printf("Welcome!");
    print_line();

    while(1)
    {
        print_main_menu();
        scanf("%5s", input_string);
        input = atoi(input_string);

        do_action(input, first, &info);

        if(info == -1)
        {
            print_goodbye_msg();
            return EXIT_SUCCESS;
        }
    }

    return EXIT_SUCCESS;
}

int do_action(int input, node_element_p first, int* info)
{
    switch(input)
    {
        case 1:
            print_list(first);
            break;
        case 2:
            enter_new_node_element(first);
            break;
        case 3:
            break;
        case 4:
        //user confirm
            save_to_file(first);
            break;
        case 5:
        //user confirm
            read_from_file(first);
            break;
        case 6:
        //user confirm
            delete_all(first);
            break;
        case 7:
            query(first, 1);
            break;
        case 8:
            query(first, 2);
            break;
        case 9:
        //user confirm
            *info = -1;
            break;
        default:
            trace("Invalid input, try again");
            new_line();
            break;

    }

    return EXIT_SUCCESS;
}