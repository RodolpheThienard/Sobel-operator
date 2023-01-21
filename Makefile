CC=icx

CFLAGS=-g3

OFLAGS=-march=native -Ofast -funroll-loops -ftree-vectorize -finline-functions -fopenmp -pthread
INTEL_LFLAGS=-qmkl 
UNOPTI_OFLAGS=-march=native -O1

DEFINE= -D$(VERSION)

BUILD=build
BIN=$(BUILD)/bin
SRC=src
INCLUDE=-I include

all:  $(BIN)/sobel $(BIN)/elapsed_time $(BIN)/aligned $(BIN)/malloc

ifeq ($(CC), icx)
$(BIN)/sobel: $(SRC)/sobel.c
	$(CC) -D$(DEFINE) $(CFLAGS) $(INCLUDE) $(INTEL_LFLAGS) $(OFLAGS) $< src/common.c src/kernel.c -o $@ -lm

$(BIN)/elapsed_time: $(SRC)/elapsed_time.c
	$(CC) -D$(DEFINE) $(CFLAGS) $(INCLUDE) $(INTEL_LFLAGS) $(OFLAGS) $< src/common.c src/kernel.c -o $@ -lm

$(BIN)/aligned: $(SRC)/aligned.c
	$(CC) -D$(DEFINE) $(CFLAGS) $(INCLUDE) $(INTEL_LFLAGS) $(OFLAGS) $< src/common.c src/kernel.c -o $@ -lm

$(BIN)/malloc: $(SRC)/malloc.c
	$(CC) -D$(DEFINE) $(CFLAGS) $(INCLUDE) $(INTEL_LFLAGS) $(OFLAGS) $< src/common.c src/kernel.c -o $@ -lm
else
$(BIN)/sobel: $(SRC)/sobel.c
	$(CC) -D$(DEFINE) $(CFLAGS) $(INCLUDE) $(OFLAGS) $< src/common.c src/kernel.c -o $@ -lm
$(BIN)/elapsed_time: $(SRC)/elapsed_time.c
	$(CC) -D$(DEFINE) $(CFLAGS) $(INCLUDE) $(OFLAGS) $< src/common.c src/kernel.c -o $@ -lm
$(BIN)/aligned: $(SRC)/aligned.c
	$(CC) -D$(DEFINE) $(CFLAGS) $(INCLUDE) $(OFLAGS) $< src/common.c src/kernel.c -o $@ -lm
$(BIN)/malloc: $(SRC)/malloc.c
	$(CC) -D$(DEFINE) $(CFLAGS) $(INCLUDE) $(OFLAGS) $< src/common.c src/kernel.c -o $@ -lm
endif

clean:
	$(RM) build/bin/*
