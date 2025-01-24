CPPFLAGS = -std=c++20 -pedantic -Wall -Wextra -Wformat-security -Wduplicated-cond -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wvla -g3 -O2

all: par.e

parlib-debug.o: parlib.cpp parlib.h communication.h config.h
	g++ $(CPPFLAGS) -D__NOPASSWORD -D__DEBUG_COMMUNICATION parlib.cpp -c -o parlib-debug.o

parlib-nodebug.o: parlib.cpp parlib.h communication.h config.h
	g++ $(CPPFLAGS) -D__NOPASSWORD parlib.cpp -c -o parlib-nodebug.o

par.e: par.cpp parlib-debug.o parlib-nodebug.o
	if [ "$(DEBUG)" = "1" ]; then\
	    g++ $(CPPFLAGS) parlib-debug.o par.cpp -o par.e;\
	else\
	    g++ $(CPPFLAGS) parlib-nodebug.o par.cpp -o par.e;\
    fi

clean:
	rm -f *.e *.o
