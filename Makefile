CXX=clang++
CXX_FLAGS=-std=c++11 -stdlib=libc++ -g -O0 -Wall -Wextra 

.PHONY: all test clean

seam_carver : driver.o seam_carver.o image_ppm.o
	${CXX} ${CXX_FLAGS} -lc++abi driver.o seam_carver.o image_ppm.o -o seam_carver

driver.o : src/driver.cpp image_ppm.o seam_carver.o
	${CXX} ${CXX_FLAGS} -c src/driver.cpp

seam_carver.o : image_ppm.o includes/seam_carver.hpp src/seam_carver.cpp
	${CXX} ${CXX_FLAGS} -c src/seam_carver.cpp

image_ppm.o : includes/pixel.hpp includes/image_ppm.hpp src/image_ppm.cpp
	${CXX} ${CXX_FLAGS} -c src/image_ppm.cpp

test : image_ppm.o seam_carver.o test.o
	${CXX} ${CXX_FLAGS} -lc++abi test.o image_ppm.o seam_carver.o -o test

test.o : tests/catch.hpp includes/image_ppm.hpp includes/seam_carver.hpp tests/tests.cc
	${CXX} ${CXX_FLAGS} -c tests/tests.cc

clean :
	rm *.o