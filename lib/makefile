CXX			:= g++
CXXFLAGS	:= -Wall -std=c++17 -O2 -fPIC

TARGET		:=  libled.so
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
	install $(TARGET) /usr/lib/
	install $(HEADER) /usr/include/

.PHONY: uninstall
uninstall:
	rm /usr/lib/$(TARGET)
	rm /usr/include/$(HEADER)
