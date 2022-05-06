IDIR     := ./include
CXX      := g++
CXXFLAGS := -g -std=c++2a -Wall -Werror -pedantic-errors -fmessage-length=0 -I $(IDIR)

SDIR := ./src
ODIR := $(SDIR)/obj
LDIR := ./lib
LIBS := -lcurl

DEPS := $(shell find $(IDIR) -name '*.hpp')

_OBJ := $(shell find $(SDIR) -name '*.cpp') 
OBJ  := $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

all: $(OBJ)
	$(CXX) -o peekify $^ $(CXXFLAGS) $(LIBS)

install:
	apt-get install libcurl4-openssl-dev

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~