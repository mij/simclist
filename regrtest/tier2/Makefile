CFLAGS= -std=c99 -Wall -g -I../../

all: tier2_tests

tier2_tests: tier2_tests.c \
						 tier2_testa.c \
						 tier2_testb.c \
						 tier2_testc.c \
						 tier2_testd.c \
						 ../lib/random.o \
						 ../lib/helpers.o \
						 ../../simclist.o

clean:
	find . -name tier2_tests -delete
