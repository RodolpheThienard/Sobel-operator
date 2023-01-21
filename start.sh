#!/bin/sh

# # ICX
# make CC=icx -B 
# ./build/bin/sobel_opt in/input.raw out/output.raw

# # GCC
# make CC=gcc -B 
# ./build/bin/sobel_opt in/input.raw out/output.raw

# # CLANG
# make CC=clang -B 
# ./build/bin/sobel_opt in/input.raw out/output.raw


# ICX
# make CC=icx -B 
# ./build/bin/sobel in/input.raw out/output.raw >> data/compilateur.dat

# # GCC
# make CC=gcc -B 
# ./build/bin/sobel in/input.raw out/output.raw >> data/compilateur.dat

# # CLANG
# make CC=clang -B 
# ./build/bin/sobel in/input.raw out/output.raw >> data/compilateur.dat


# ICX compiler performance capturing for each implementation
# make -B 

# All DEFINED version 
versions=(BASELINE SQRT PIXEL PIXELSQRT SOBEL7 SOBEL3)

# All used compiler
compilers=(icx gcc clang)

# ALl measured flags
#flags=("-O1", "-O2", "-O3", "-OFast")

for compiler in ${compilers[@]}
do
  for version in ${versions[@]}
  do 
    # echo "$compiler and $version"
    make -B CC=$compiler DEFINE=$version
    ./build/bin/sobel in/input.raw out/output.raw $version >> data/$compiler.dat
    ./build/bin/elapsed_time in/input.raw out/output.raw $version >> data/elapsed_$compiler.dat
    ./build/bin/aligned in/input.raw out/output.raw $version >> data/aligned_$compiler.dat
    ./build/bin/malloc in/input.raw out/output.raw $version >> data/malloc_$compiler.dat
    
  done
done

