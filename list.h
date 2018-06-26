#ifndef __LIST_H__
#define __LIST_H__


#include <stdlib.h>


struct list {
    struct list *next, *prev;
};


#define LIST_HEAD_INIT(name) { &(name), &(name) }

/**
 * INIT_LIST - Define and initilize a head of list
 *
 * @name:       name of the declared structure
 */
#define INIT_LIST(name) \
    struct list name = LIST_HEAD_INIT(name)


/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 */
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))


/**
 * for_each - iterate over a list
 * @pos:        the struct list ptr to use as a loop counter.
 * @head:       the head for your list.
 */
#define for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)


/**
 * for_each_entry - iterate over a list of given type
 * @pos:        the type * to use as a loop counter.
 * @head:       the head for your list.
 * @member:     the name of the list_struct within the struct.
 */
#define for_each_entry(pos, head, member) \
    for (pos = container_of((head)->next, typeof(*pos), member); \
            &pos->member != (head); \
            pos = container_of(pos->member.next, typeof(*pos), member))


/* ONLY FOR INTERNAL USE
 *
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_insert(struct list *entry, struct list *prev, struct list *next)
{
    prev->next = entry;
    next->prev = entry;
    entry->next = next;
    entry->prev = prev;
}


static inline void init_list(struct list *head)
{
    head->prev = head;
    head->next = head;
}


static inline void list_add_head(struct list *head, struct list *entry)
{
    __list_insert(entry, head, head->next);
}


static inline void list_add_tail(struct list *head, struct list *entry)
{
    __list_insert(entry, head->prev, head);
}


static inline void list_delete(struct list *entry)
{
    if (entry->next && entry->prev) {
        entry->next->prev = entry->prev;
        entry->prev->next = entry->next;
    }
    entry->next = NULL;
    entry->prev = NULL;
}


static inline size_t list_length(struct list *head)
{
    size_t len = 0;
    struct list *nodep = NULL;

    for_each(nodep, head)
        len++;

    return len;
}


#endif /* __LIST_H__ */

