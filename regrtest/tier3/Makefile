CFLAGS= -pthread -std=c99 -Wall -g -I../../

all: tier3_tests tier3_testc

tier3_tests: tier3_tests.c \
						 tier3_testa.c \
						 tier3_testb.c \
						 ../lib/random.o \
						 ../lib/helpers.o \
						 ../../simclist.o

tier3_testc: tier3_testc.c \
						 ../../simclist.o

clean:
	rm -f tier3_tests tier3_testc
