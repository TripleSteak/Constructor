CXX=g++
CXXFLAGS=-std=c++14 -MMD -Wall -g
CCFILES=$(wildcard ../src/*/*.cc)
OBJECTS=$(CCFILES:.cc=.o)
TESTFILES=$(wildcard */*.cc)
TESTOBJECTS=$(TESTFILES:.cc=.o)
DEPENDS=${CCFILES:.cc=.d} ${TESTFILES:.cc=.d}
EXEC=./tests.out
${EXEC}:${OBJECTS} ${TESTOBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${TESTOBJECTS} -pthread -lgtest -lgtest_main -o ${EXEC}
-include ${DEPENDS}

PHONY:clean
clean:
	rm ${OBJECTS} ${TESTOBJECTS} ${EXEC} ${DEPENDS}
