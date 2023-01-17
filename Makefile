CC=gcc

CFLAGS=-g3

OFLAGS=-march=native -mavx512f -Ofast -funroll-loops -ftree-vectorize -finline-functions -qmkl -fopenmp
UNOPTI_OFLAGS=-O1

BUILD=build
BIN=$(BUILD)/bin
SRC=src
INCLUDE=-I include

all: $(BIN)/sobel_opt

$(BIN)/sobel_opt: $(SRC)/sobel_opt.c
	$(CC) -DBASELINE=1 $(CFLAGS) $(INCLUDE) $(OFLAGS) $< src/common.c -o $@ -lm
	
$(BIN)/sobel: $(SRC)/sobel.c
	$(CC) -DBASELINE=1 $(CFLAGS) $(INCLUDE) $(UNOPTI_OFLAGS) $< common.c -o $@ -lm

clean:
	rm -Rf *~ sobel
