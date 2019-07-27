#
# Makefile for word frequency count examples
#
PROGS = basic_mmap pmemkv freq freq_mt freq_pmem freq_pmem_print freq_pmem_cpp
CFLAGS = -g -Wall -Werror -std=gnu99
CXXFLAGS = -g -Wall -Werror -std=gnu++11

all: $(PROGS)

freq_mt: LIBS = -pthread
freq_pmem freq_pmem_print freq_pmem_cpp: LIBS = -lpmem -lpmemobj -pthread

basic_mmap: basic_mmap.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

pmemkv: pmemkv.cpp
	$(CXX) -o pmemkv pmemkv.cpp -lpmemkv

freq: freq.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

freq_mt: freq_mt.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

freq_pmem: freq_pmem.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

freq_pmem_print: freq_pmem_print.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

freq_pmem_cpp: freq_pmem_cpp.o
	$(CXX) -o $@ $(CFLAGS) $^ $(LIBS)

clean:
	$(RM) *.o a.out core

clobber: clean
	$(RM) $(PROGS)

.PHONY: all clean clobber
