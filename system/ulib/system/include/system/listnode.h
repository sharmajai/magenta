// Copyright 2016 The Fuchsia Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <system/compiler.h>
#include <stdbool.h>
#include <stddef.h>

__BEGIN_CDECLS;

#define containerof(ptr, type, member) ((type*)((uintptr_t)(ptr)-offsetof(type, member)))

typedef struct list_node list_node_t;

struct list_node {
    list_node_t* prev;
    list_node_t* next;
};

#define LIST_INITIAL_VALUE(list) \
    { &(list), &(list) }
#define LIST_INITIAL_CLEARED_VALUE \
    { NULL, NULL }

static inline void list_initialize(list_node_t* list) {
    list->prev = list->next = list;
}

static inline void list_clear_node(list_node_t* item) {
    item->prev = item->next = 0;
}

static inline bool list_in_list(list_node_t* item) {
    if (item->prev == 0 && item->next == 0)
        return false;
    else
        return true;
}

static inline void list_add_head(list_node_t* list, list_node_t* item) {
    item->next = list->next;
    item->prev = list;
    list->next->prev = item;
    list->next = item;
}

#define list_add_after(entry, new_entry) list_add_head(entry, new_entry)

static inline void list_add_tail(list_node_t* list, list_node_t* item) {
    item->prev = list->prev;
    item->next = list;
    list->prev->next = item;
    list->prev = item;
}

#define list_add_before(entry, new_entry) list_add_tail(entry, new_entry)

static inline void list_delete(list_node_t* item) {
    item->next->prev = item->prev;
    item->prev->next = item->next;
    item->prev = item->next = 0;
}

static inline list_node_t* list_remove_head(list_node_t* list) {
    if (list->next != list) {
        list_node_t* item = list->next;
        list_delete(item);
        return item;
    } else {
        return NULL;
    }
}

#define list_remove_head_type(list, type, element)   \
    ({                                               \
        list_node_t* __nod = list_remove_head(list); \
        type* __t;                                   \
        if (__nod)                                   \
            __t = containerof(__nod, type, element); \
        else                                         \
            __t = (type*)0;                          \
        __t;                                         \
    })

static inline list_node_t* list_remove_tail(list_node_t* list) {
    if (list->prev != list) {
        list_node_t* item = list->prev;
        list_delete(item);
        return item;
    } else {
        return NULL;
    }
}

#define list_remove_tail_type(list, type, element)   \
    ({                                               \
        list_node_t* __nod = list_remove_tail(list); \
        type* __t;                                   \
        if (__nod)                                   \
            __t = containerof(__nod, type, element); \
        else                                         \
            __t = (type*)0;                          \
        __t;                                         \
    })

static inline list_node_t* list_peek_head(list_node_t* list) {
    if (list->next != list) {
        return list->next;
    } else {
        return NULL;
    }
}

#define list_peek_head_type(list, type, element)     \
    ({                                               \
        list_node_t* __nod = list_peek_head(list);   \
        type* __t;                                   \
        if (__nod)                                   \
            __t = containerof(__nod, type, element); \
        else                                         \
            __t = (type*)0;                          \
        __t;                                         \
    })

static inline list_node_t* list_peek_tail(list_node_t* list) {
    if (list->prev != list) {
        return list->prev;
    } else {
        return NULL;
    }
}

#define list_peek_tail_type(list, type, element)     \
    ({                                               \
        list_node_t* __nod = list_peek_tail(list);   \
        type* __t;                                   \
        if (__nod)                                   \
            __t = containerof(__nod, type, element); \
        else                                         \
            __t = (type*)0;                          \
        __t;                                         \
    })

static inline list_node_t* list_prev(list_node_t* list, list_node_t* item) {
    if (item->prev != list)
        return item->prev;
    else
        return NULL;
}

#define list_prev_type(list, item, type, element)    \
    ({                                               \
        list_node_t* __nod = list_prev(list, item);  \
        type* __t;                                   \
        if (__nod)                                   \
            __t = containerof(__nod, type, element); \
        else                                         \
            __t = (type*)0;                          \
        __t;                                         \
    })

static inline list_node_t* list_prev_wrap(list_node_t* list, list_node_t* item) {
    if (item->prev != list)
        return item->prev;
    else if (item->prev->prev != list)
        return item->prev->prev;
    else
        return NULL;
}

#define list_prev_wrap_type(list, item, type, element)   \
    ({                                                   \
        list_node_t* __nod = list_prev_wrap(list, item); \
        type* __t;                                       \
        if (__nod)                                       \
            __t = containerof(__nod, type, element);     \
        else                                             \
            __t = (type*)0;                              \
        __t;                                             \
    })

static inline list_node_t* list_next(list_node_t* list, list_node_t* item) {
    if (item->next != list)
        return item->next;
    else
        return NULL;
}

#define list_next_type(list, item, type, element)    \
    ({                                               \
        list_node_t* __nod = list_next(list, item);  \
        type* __t;                                   \
        if (__nod)                                   \
            __t = containerof(__nod, type, element); \
        else                                         \
            __t = (type*)0;                          \
        __t;                                         \
    })

static inline list_node_t* list_next_wrap(list_node_t* list, list_node_t* item) {
    if (item->next != list)
        return item->next;
    else if (item->next->next != list)
        return item->next->next;
    else
        return NULL;
}

#define list_next_wrap_type(list, item, type, element)   \
    ({                                                   \
        list_node_t* __nod = list_next_wrap(list, item); \
        type* __t;                                       \
        if (__nod)                                       \
            __t = containerof(__nod, type, element);     \
        else                                             \
            __t = (type*)0;                              \
        __t;                                             \
    })

// iterates over the list, node should be list_node_t*
#define list_for_every(list, node) for (node = (list)->next; node != (list); node = node->next)

// iterates over the list in a safe way for deletion of current node
// node and temp_node should be list_node_t*
#define list_for_every_safe(list, node, temp_node)                      \
    for (node = (list)->next, temp_node = (node)->next; node != (list); \
         node = temp_node, temp_node = (node)->next)

// iterates over the list, entry should be the container structure type *
#define list_for_every_entry(list, entry, type, member)                                 \
    for ((entry) = containerof((list)->next, type, member); &(entry)->member != (list); \
         (entry) = containerof((entry)->member.next, type, member))

// iterates over the list in a safe way for deletion of current node
// entry and temp_entry should be the container structure type *
#define list_for_every_entry_safe(list, entry, temp_entry, type, member) \
    for (entry = containerof((list)->next, type, member),                \
        temp_entry = containerof((entry)->member.next, type, member);    \
         &(entry)->member != (list);                                     \
         entry = temp_entry, temp_entry = containerof((temp_entry)->member.next, type, member))

static inline bool list_is_empty(list_node_t* list) {
    return (list->next == list) ? true : false;
}

static inline size_t list_length(list_node_t* list) {
    size_t cnt = 0;
    list_node_t* node = list;
    list_for_every(list, node) {
        cnt++;
    }

    return cnt;
}

__END_CDECLS;
