#include <stdio.h>
#include <stdlib.h>

#include "../../simclist.h"
#include "tier3_testc.h"


struct my_type {
    uint32_t a;
    uint32_t b;
};

static size_t _my_size(const void *el) {
  return sizeof(struct my_type);
}

void save_and_restore_list() {
    list_t list;
    list_init(&list);
    list_attributes_copy(&list, _my_size, 1);

    // add some data
    for (int32_t i=0; i<1000; i++) {
    	struct my_type t;
    	t.a=i;
    	t.b=i;
        list_append(&list, &t);
    }

    int err = list_dump_file(&list, "dumpedlist", NULL);
    list_destroy(&list);
    if (err) {
        printf("failed to dump the list\n");
        return;
    }

    list_t restored_list;
    list_init(&restored_list);
    list_attributes_copy(&restored_list, _my_size, 1);
    err = list_restore_file(&restored_list, "dumpedlist", NULL);
    if (err) {
        printf("failed to restore the list\n");    
        return;
    }
    struct my_type* t = (struct my_type*)list_get_at(&restored_list, 0);
    printf("get i from restore list %u\n", t->a);
    list_destroy(&restored_list);
}

int testc_check() {
    save_and_restore_list();
    save_and_restore_list();
    return 0;
}
