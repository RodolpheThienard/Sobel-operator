CC=icx

CFLAGS=-g3

OFLAGS=-march=native -mavx512f -Ofast -funroll-loops -ftree-vectorize -finline-functions -fopenmp
INTEL_LFLAGS=-qmkl 
UNOPTI_OFLAGS=-march=native -O1

DEFINE= -D$(VERSION)

BUILD=build
BIN=$(BUILD)/bin
SRC=src
INCLUDE=-I include

all:  $(BIN)/sobel 

ifeq ($(CC), icc)
$(BIN)/sobel: $(SRC)/sobel.c
	$(CC) $(DEFINE) $(CFLAGS) $(INCLUDE) $(INTEL_LFLAGS) $(UNOPTI_OFLAGS) $< src/common.c src/kernel.c -o $@ -lm
else
$(BIN)/sobel: $(SRC)/sobel.c
	$(CC) -D$(DEFINE) $(CFLAGS) $(INCLUDE) $(OFLAGS) $< src/common.c src/kernel.c -o $@ -lm
endif

clean:
	rm -Rf *~ sobel
