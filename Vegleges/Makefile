#
# Makefile a CPPswap eloallitasahoz
#

PROG = vonat_elarusito
SRCS = main.cpp kocsi.cpp vonat.cpp mystring.cpp datum.cpp memtrace.cpp jegy.cpp mav.cpp menu.cpp teszteles.cpp intercity.cpp helykozi.cpp
HDRS = kocsi.h vonat.h mystring.h gtest_lite.h myvector.hpp datum.h memtrace.h jegy.h mav.h menu.h teszteles.h intercity.h helykozi.h
OBJS = $(SRCS:.cpp=.o)

CXXFLAGS = -g -Wall -Werror -DMEMTRACE -pedantic

$(PROG): $(OBJS) 
	$(CXX) -o $(PROG) $(OBJS)

.PHONY:

clean:
	rm -f $(OBJS) 
$(OUT)

# Egyszerusites: Minden .o fugg minden header-tol, es meg a Makefile-tol is 
$(OBJS): $(HDRS) Makefile