CXX			:= g++
CXXFLAGS	:= -Wall -std=c++17 -O2 -fPIC

TARGET		:=  lib3dled.so
HEADER		:= led.h
PROJ_ROOT	:= $(realpath .)
SRCS		:= $(wildcard *.cpp)
OBJS		:= $(SRCS:.cpp=.o)
LIBS		:= 

### Rules ######################################################################

.PHONY: all
all: $(TARGET)

.PHONY: make
make: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -shared -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) *.o

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

.PHONY: install
install:
	install $(TARGET) /usr/local/lib
	install $(HEADER) /usr/local/include

.PHONY: uninstall
uninstall:
	rm /usr/local/lib/$(TARGET)
	rm /usr/local/include/$(HEADER)
