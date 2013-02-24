CFLAGS= -std=c99 -Wall -g -I../../

all: tier1_tests

tier1_tests: tier1_tests.c \
						 tier1_testa.c \
						 tier1_testb.c \
						 tier1_testc.c \
						 ../lib/random.o \
						 ../lib/helpers.o \
						 ../../simclist.o

clean:
	find . -name tier1_tests -delete
