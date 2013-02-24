.PHONY: all clean lib tier1 tier2 tier3

all: lib tier1 tier2 tier3

lib:
	${MAKE} -C lib

tier1:
	${MAKE} -C tier1

tier2:
	${MAKE} -C tier2

tier3:
	${MAKE} -C tier3

clean:
	${MAKE} -C lib clean
	${MAKE} -C tier1 clean
	${MAKE} -C tier2 clean
	${MAKE} -C tier3 clean
