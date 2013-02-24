CFLAGS= -pthread -std=c99 -Wall -g -I../../

all: tier3_tests

tier3_tests: tier3_tests.c \
						 tier3_testa.c \
						 tier3_testb.c \
						 ../lib/random.o \
						 ../lib/helpers.o \
						 ../../simclist.o

clean:
	find . -name tier3_tests -delete
