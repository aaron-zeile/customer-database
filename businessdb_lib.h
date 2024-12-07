#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// hash generator
unsigned long db_hash(char *str);

// linked list for each person
typedef struct person {
  char *email;
  char *name;
  int shoe_size;
  char *food;
  struct person *next;
} person;

// database buckets
typedef struct database {
  size_t num_buckets;
  person **buckets;
} database;

void load_db(database *db);

database *make_database(size_t num_buckets);

person *add_info(person *p, char *email, char *name, int shoe_size, char *food);

void add_entry(database *db, char *email, char *name, int shoe_size, char *food);

person *lookup_info(person *p, char *email);

person *lookup_entry(database *db, char *email);

void delete_entry(database *db, char *email);

void list_entries(database *db);

void save(database *db);

void quit(database *db);
