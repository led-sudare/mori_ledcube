CXX			:= g++
CXXFLAGS	:= -Wall -std=c++11

TARGET		:= demo
PROJ_ROOT	:= $(realpath .)
INCLUDES	:= 
SRCS		:= main.cpp
LIBS		:= -lled
OBJS		:= $(SRCS:.cpp=.o)

### Rules ######################################################################

.PHONY: all
all: $(TARGET)

.PHONY: make
make: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) *.o

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<
