CXX=g++
CXXFLAGS=-std=c++14 -MMD -Wall -g
CCFILES=$(wildcard *.cc) $(wildcard */*.cc)
OBJECTS=$(CCFILES:.cc=.o)
DEPENDS=${CCFILES:.cc=.d}
EXEC=../ctor
${EXEC}:${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}

PHONY:clean
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
