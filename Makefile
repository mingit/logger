DIR_INC = ./include
DIR_TST = ./tests
DIR_OBJ = ./obj
DIR_BIN = ./bin
DIR_DAT = ./data

CXX			=	g++
CFLAGS		=	-std=c++11 -g -Wall -I${DIR_INC} 
LDFLAGS		=	-lpthread  


all: clean ${DIR_BIN}/general ${DIR_BIN}/customoutput-multithread ${DIR_BIN}/customtype ${DIR_BIN}/customoutput ${DIR_BIN}/multithread
.PHONY:all


${DIR_BIN}/general: ${DIR_OBJ}/general.o 
	$(CXX) $< ${LDFLAGS} -o $@ 

${DIR_BIN}/customoutput-multithread: ${DIR_OBJ}/customoutput-multithread.o 
	$(CXX) $< ${LDFLAGS} -o $@ 

${DIR_BIN}/customtype: ${DIR_OBJ}/customtype.o
	$(CXX) $< ${LDFLAGS} -o $@ 

${DIR_BIN}/customoutput: ${DIR_OBJ}/customoutput.o
	$(CXX) $< ${LDFLAGS} -o $@ 

${DIR_BIN}/multithread: ${DIR_OBJ}/multithread.o 
	$(CXX) $< ${LDFLAGS} -o $@ 



${DIR_OBJ}/%.o:${DIR_TST}/%.cpp
	$(CXX) $(CFLAGS) -c  $< -o $@

.PHONY:clean
clean:
	-rm -fr ${DIR_OBJ}/*.o
	-rm -fr ${DIR_BIN}/*
	-rm -fr ${DIR_DAT}/*.dat
