#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"


static LIST_HEAD(person_head);


struct person
{
    char *name;
    struct list_head node;
};


static int add_person(const char *person_name)
{
    struct person *new = calloc(1, sizeof(struct person));
    if (new == NULL)
        return -1;

    new->name = strdup(person_name);
    list_add_tail(&(new->node), &person_head);
    printf("person_name[%s]:added\n", person_name);

    return 0;
}


static void dump_person_list()
{
    unsigned int i = 0;
    struct person *p = NULL;
    list_for_each_entry(p, &person_head, node) {
        printf("dump name[%s]:id[%d]\n", p->name, i);
        i++;
    }
}


static void clean_person_list()
{
    struct person *p, *save;
    list_for_each_entry_safe(p, save, &person_head, node) {
        list_del(&(p->node));
        free(p->name);
        free(p);
    }
}


int main()
{
    add_person("Mike");
    add_person("Georges");
    add_person("Andrew");

    dump_person_list();

    printf("nbr_of_person_in_list[%ld]\n", list_length(&person_head));

    clean_person_list();
    printf("person_list cleaned\n");

    add_person("Louis");

    dump_person_list();

    printf("nbr_of_person_in_list[%ld]\n", list_length(&person_head));

    clean_person_list();

    return 0;
}

