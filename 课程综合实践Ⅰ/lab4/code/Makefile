CC=gcc
CFLAGS=-mcmodel=medium
# compiler may crash when static array too large,
# add `-mcmodel=medium` in this case.

all:
        $(CC) -fopenmp -O3 -march=core-avx2 -o gemm  hw_baseline.cpp $(CFLAGS)

.PHONY: run
run: all
        ./gemm

.PHONY: clean
clean:
        rm -rf *.o gemm