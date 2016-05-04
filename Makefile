CC = g++
PROG ?= tester
OBJS = PiecewiseCurveBuilder.o Tester.o
INCLUDE_DIRS = -I/usr/local/include/
LIBRARY_DIRS = -L/usr/local/lib/
LDFLAGS =  -lQuantLib -larmadillo
CXXFLAGS = -g -pedantic -std=c++11 -DDEBUG # -O2

all: $(PROG)

.cpp.o:
	$(CC) $(CXXFLAGS) -Wall $(INCLUDE_DIRS) -pedantic -ggdb -c -o $@ $<

$(PROG): $(OBJS)
	$(CC) $(CXXFLAGS) -Wall $(INCLUDE_DIRS) $(LIBRARY_DIRS) -pedantic -ggdb -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f *.o $(PROG)
