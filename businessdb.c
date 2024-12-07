#include "businessdb_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(void) {
    
    // make the database
    database *db = make_database(1000);

    // load in the pre-existing database from file
    load_db(db);
    
 // *** operatable program loop *** //
    while (1) {
        // variables for user interaction
        char input[20];        
        char email[100];
        char name[100];
        int shoe_size = 0;
        char food[100];

        // get user input
        printf("command: ");
        scanf(" %[^\n]", input);
        
        // add
        if (strcmp(input, "add") == 0) {
            printf("email: ");
            scanf(" %[^\n]", email);
            char *e = strtok(email, "\t");

            // if email already in database
            if (lookup_entry(db, email)) {
                delete_entry(db, email);
            }
            
            printf("name: ");
            scanf(" %[^\n]", name);
            char *n = strtok(name, "\t");
            
            // get shoe size, making sure it's an int
            float ss;
            printf("shoe size: ");
            scanf("%f", &ss);
            shoe_size = (int) ss;

            printf("favorite food: ");
            scanf(" %[^\n]", food);
            char *f = strtok(food, "\t");
 
            // create new entry using inputted data
            add_entry(db, e, n, shoe_size, f);
        }
        // lookup
        else if (strcmp(input, "lookup") == 0) {
            printf("email: ");
            scanf(" %[^\n]", email);
            person *p = lookup_entry(db, email);
            if (p) {
                printf("\nemail: %s\n", p->email);
                printf("name: %s\n", p->name);
                printf("shoe size: %d\n", p->shoe_size);
                printf("favorite food: %s\n", p->food);
            }
            else {
                printf("Customer not found. \n");
            }
        }
        // list
        else if (strcmp(input, "list") == 0) {
            list_entries(db);
        } 
        // delete
        else if (strcmp(input, "delete") == 0) {
            printf("email: ");
            scanf(" %[^\n]", email);
            delete_entry(db, email);
        }
        // save
        else if (strcmp(input, "save") == 0) {
            save(db);
        }
        // quit
        else if (strcmp(input, "quit") == 0) {
            quit(db);
            break;
        }
    } 
    
    return 0;
}
