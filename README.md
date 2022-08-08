| Version | License | Website | LicenseContact | 
| - | - | - | - |
| 1.6.3 | [BSD revised](http://www.opensource.org/licenses/bsd-license.php) | http://mij.oltrelinux.com/devel/simclist/ | mij@sshguard.net |

# Overview of SimCList

`SimCList` is a high quality C library (and C++ embeddable) for handling lists. It exploits several advanced techniques for improving performance, including freelists, sentinels, automatic sort algorithm selection, sort randomization, mid pointer, and optional multithreading. The API is simple but powerful, makes elegant and consistent use of information hiding, abstracts the actual data type to store, and is fairly complete. The library itself makes a good compromise between performance in terms of time and space, and is well documented.

SimCList is used projects ranging from [Intrusion Detection](https://sshguard.net), to [device drivers](https://opensource.apple.com/source/SmartcardCCID/) and [simulation](https://www.nrel.gov/wind/nwtc/openfast.html).

## Features

- iteration
- sorting
- custom types as items
- self-allocation
- dump / restore

# Usage examples

## Basic use

```C
#include <stdio.h>

#include <simclist.h>   /* use the SimCList library */

int main() {
    list_t mylist;      /* declare a list */
    int userval;

    printf("Insert your number: ");
    scanf("%d", & userval);

    list_append(& mylist, & userval);       /* add an element to the list */

    printf("The list now holds %u elements.\n", \
            list_size(& mylist));           /* get the size of the list */

    printf("Your number was: %d\n", \
            * (int*)list_get_at(& mylist, 0));  /* extract the first element of the list */

    list_destroy(&mylist);
    
    return 0;
}
```

## Self-allocation and iteration

```C
#include <stdio.h>

#include <simclist.h>

int main() {
    int val;
    list_t l;

    list_init(&l);

    /* request to store copies, and provide the metric function */
    list_attributes_copy(&l, list_meter_int32_t, 1);

    printf("Give numbers. Terminate with one negative.\n");
    scanf("%d", &val);
    while (val > 0) {
        list_append(&l, &val);
        scanf("%d", &val);
    } 

    /* setting the comparator, so the list can sort, find the min, max etc */
    list_attributes_comparator(&l, list_comparator_int32_t);
    list_sort(&l, -1);      /* sorting the list in descending (-1) order */
    
    /* printing out the result */
    printf("Sorted values:\n");
    
    list_iterator_start(&l);        /* starting an iteration "session" */
    while (list_iterator_hasnext(&l)) { /* tell whether more values available */
        printf("%d\n", *(int *)list_iterator_next(&l));     /* get the next value */
    }
    list_iterator_stop(&l);         /* starting the iteration "session" */
    
    list_destroy(&l);

    return 0;
}
```

## Custom list items

```C
#include <stdio.h>

#include <simclist.h>

typedef struct {
	int x, y;
} point2D;

typedef struct {
	point2D a, b, c, d;
} rectangle;	/* custom data type to store in list */

/* this function returns the size of elements */
size_t mymeter(const void *el) {
	/* every element has the constant size of a rectangle structure */
	return sizeof(rectangle);
}

/*
 * compare rectangles by area
 * 
 * this function compares two elements:
 * <0: a greater than b
 * 0: a equivalent to b
 * >0: b greater than a
 */
int mycomparator(const void *a, const void *b) {
	/* compare areas */
	const rectangle *A = (rectangle *) a;
	const rectangle *B = (rectangle *) b;
	unsigned int    areaA, areaB;
	areaA = ((A->c.y - A->b.y) * (A->b.x - A->a.x));
	areaB = ((B->c.y - B->b.y) * (B->b.x - B->a.x));
	return (areaA < areaB) - (areaA > areaB);
}

int main() {
	rectangle rect;
	list_t l;

	list_init(&l);

	/* setting the custom spanning function */
	list_attributes_copy(&l, mymeter, 1);

	/* acquire rectangles and insert in list ... */

	/* setting the custom area comparator */
	list_attributes_comparator(&l, mycomparator);
	list_sort(&l, -1);	/* sorting by area (descending) */

	/* [display list ...] */

    list_destroy(&l);

	return 0;
}
```

# License

SimCList is BSD-licensed. See [BSD 2-Clause License](http://www.opensource.org/licenses/bsd-license.php).

# Installation

You have various options:

- Copy files `simclist.c` and `simclist.h` into your application.
- Install SimCList as a shared library.

Your Operating System's package manager may provide a SimCList package.

## Compiling SimCList

here's how you install SimCList manually:

```bash
cd simclist/
cmake .         # creates the Makefile for your platform
make            # compiles SimClist into a dynamic library for your platform
```

# API Documentation

## Online

See [SimCList API refere](http://mij.oltrelinux.com/devel/simclist/apidoc/d3/d68/simclist_8h.html).

## Locally

Build a local copy of SimCList's documentation with [doxygen](https://www.doxygen.nl):

```bash
cd simclist/
doxygen         # creates files in doc/html/
```
