#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"


static LIST_HEAD(l);


struct person
{
    char *name;
    struct list_head node;
};


static int add_person(const char *person_name)
{
    struct person *new = calloc(1, sizeof(struct person));
    if (new == NULL) {
        return -1;
    }

    new->name = strdup(person_name);

    list_add_tail(&(new->node), &l);

    printf("person_name[%s]:added\n", person_name);

    return 0;
}


static void dump_person_list()
{
    unsigned int i = 0;
    struct person *p = NULL;
    list_for_each_entry(p, &l, node) {
        printf("dump name[%s]:id[%d]\n", p->name, i);
        i++;
    }
}


static void clean_person_list()
{
    struct person *p;
    list_for_each_entry(p, &l, node) {
        free(p->name);
        free(p);
    }
}


static int entry()
{
    add_person("Mike");
    add_person("Georges");
    add_person("Andrew");

    dump_person_list();

    printf("nbr_of_person_in_list[%ld]\n", list_length(&l));

    clean_person_list();

    init_list(&l);

    add_person("Louis");

    dump_person_list();

    printf("nbr_of_person_in_list[%ld]\n", list_length(&l));

    clean_person_list();

    return 0;
}


int main()
{
    entry();
    return 0;
}

