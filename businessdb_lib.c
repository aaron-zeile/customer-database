#include "businessdb_lib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_db(database *db) {
    // add existing customers in .tsv to database
    FILE *file;
    char line[1000];
    char *e;
    char *n;
    int ss = 0;
    char *f;

    file = fopen("customer_data.tsv", "r");
    if (file == NULL) {
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {            
        char *token = strtok(line, "\t\n");
        for (int i = 0; i < 4; i++) {
            if (i == 0) {
                e = token;
            }
            else if (i == 1) {
                n = token;
            }
            else if (i == 2) {
                ss = atoi(token);
            }
            else if (i == 3) {
                f = token;
            }
            token = strtok(NULL, "\t\n");
        }
        add_entry(db, e, n, ss, f);
    }

    fclose(file);
}

unsigned long db_hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while (*str != '\0') {
        c = *str;
        hash = ((hash << 5) + hash) + (unsigned char)c;
        str++;
    }
  return hash;
}

database *make_database(size_t num_buckets) {
    database *out = calloc(1, sizeof(database));
    out->buckets = calloc(num_buckets, sizeof(database *));
    out->num_buckets = num_buckets;
    return out;
}

// add person info
person *add_info(person *p, char *email, char *name, int shoe_size, char *food) {
    person *new_front = calloc(1, sizeof(person));
    if (!new_front) {
        return NULL;
    }

    new_front->email = strdup(email);
    new_front->name = strdup(name);
    new_front->shoe_size = shoe_size;
    new_front->food = strdup(food);
    new_front->next = p;

    return new_front;
}

// add person to hash table
void add_entry(database *db, char *email, char *name, int shoe_size, char *food) {    
    unsigned long hashval = db_hash(email);
    size_t bucket = hashval % db->num_buckets;

    db->buckets[bucket] = add_info(db->buckets[bucket], email, name, shoe_size, food);
}

// lookup email in person's info
person *lookup_info(person *p, char *email) {
    // if no person(s)
    if (!p) {
        return NULL;
    }
    // if matching email is found
    if (strcmp(email, p->email) == 0) {
        return p;
    }
    // if no match is found, move to next person
    else {
        return lookup_info(p->next, email);
    }

}

// lookup bucket for person
person *lookup_entry(database *db, char *email) {
    unsigned long hashval = db_hash(email);
    size_t bucket = hashval % db->num_buckets;
    
    return lookup_info(db->buckets[bucket], email);
}

// delete specific entry
void delete_entry(database *db, char *email) {
    // save target
    person *target = lookup_entry(db, email);

    // if target doesn't exist
    if (!target) {
        printf("User not found.\n");
    }   

    // iterate through buckets in database
    for (size_t i = 0; i < db->num_buckets; i++) {
        // keep track of current and previous people in ll
        person *current = db->buckets[i];
        person *prev = NULL;

        // while we are in the linked list
        while (current != NULL) {
            // if target is found
            if (current == target) {
                // and if the target is the head
                if (prev == NULL) {
                    db->buckets[i] = current->next; // move the head over one node
                }
                // if target is not the head
                else {
                    prev->next = current->next; // skip over target
                }
                // free all data associated with target and return
                free(current->email);
                free(current->name);
                //free(current->shoe_size);
                free(current->food);
                free(current);
                return;
            }
        // while target is yet to be found,
        // update pointers
        prev = current;
        current = current->next;
        }                

    }
    // if we get to this point, display message
    printf("User not found.\n");
}

void list_entries(database *db) {
    // go to each bucket
    for (size_t i = 0; i < db->num_buckets; i++) {
        // display each person in current bucket
        person *current = db->buckets[i];
        while (current != NULL) {
            printf("\nemail: %s\n", current->email);
            printf("name: %s\n", current->name);
            printf("shoe size: %d\n", current->shoe_size);
            printf("favorite food: %s\n\n", current->food);
            current = current->next;
        }
    }    
}

void save(database *db) {
   FILE *file;
   file = fopen("customer_data.tsv", "w");
   if (file == NULL) {
      printf("Error opening file\n");
      return;
   }  

   for (size_t i = 0; i < db->num_buckets; i++) {
       // go through each person
       person *current = db->buckets[i];
       while (current != NULL) {
           fprintf(file, "%s\t%s\t%d\t%s\n", 
                   current->email, 
                   current->name, 
                   current->shoe_size, 
                   current->food);
           current = current->next;
       }
   }    
  fclose(file); 
}

void quit(database *db) {
    for (size_t i = 0; i < db->num_buckets; i++) {
        // go through each person
        person *current = db->buckets[i];
        while (current != NULL) {
            person *next = current->next;
            free(current->email);
            free(current->name);
            //free(current->shoe_size);
            free(current->food);
            free(current);
            current = next;   
        } 
    }   
    free(db->buckets); 
    free(db); 
}
