#include "hw9_io.h"


void main_menu(sequence* mySequence){                                       /* Main menu for the system */
    short selection;
    node* next;

    printf("Current Sequence:");
    next = mySequence->first;
    while (next != NULL) {
        printf("%d", next->dataCustomer->label);
        if(next->next != NULL)
            printf("-");
        next = (node *)next->next;
    }

    printf("\n1-Add Customer");
    printf("\n2-Process Customer\n");
    scanf("%hd",&selection);

    if(selection == 1)
        add_customer_menu(mySequence);
    else if(selection == 2)
        process_customer_menu(mySequence);
    else{
        printf("Wrong selection\n");                                                                       /* if selection is wrong */
        main_menu(mySequence);
    }

}

void process_customer_menu(sequence* mySequence){                                       /* processing customer menu */
    if(mySequence->size < 1)
        printf("There is not any customer in bank system sequence.\n");

    else {
        customer *proceed = processCustomer(mySequence);
        printf("Proceed customer is %s \n",proceed->name);
    }
    main_menu(mySequence);
}


void add_customer_menu(sequence* mySequence){                                       /* add customer menu takes information and saves */
    customer *newCustomer = malloc(sizeof(customer) );
    printf("Please enter the name of the customer : ");
    scanf("%s",newCustomer->name);

    printf("Please enter the age of the customer : ");
    scanf("%d",&newCustomer->age);

    printf("Please enter the label of the customer : ");
    scanf("%hd",&newCustomer->label);

    if(newCustomer->label >=0 && newCustomer->label <=4)
        addCustomer(mySequence, newCustomer);

    else
        printf("The label must be between 0-4. ");
    main_menu(mySequence);
}