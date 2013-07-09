CXX=g++-4.8 --std=c++11
CXXFLAGS=-O2 -Wall -Wextra -Winline -Wshadow -pedantic

TLIB_INC_DIR    = -I../include

INC_DIRS = $(TLIB_INC_DIR)
LIBS     = -lboost_unit_test_framework

MAIN_TEST         = main.cpp
ITERATORS_TESTS   = $(wildcard iterator/*.cpp)
TYPE_TRAITS_TESTS = $(wildcard type_traits/*.cpp)
MPL_TESTS         = $(wildcard mpl/*.cpp) \
                    $(wildcard mpl/arithmetic/*.cpp)
FUNCTIONAL_TESTS  = $(wildcard functional/*.cpp)

SRCS     = $(MAIN_TEST) \
           $(ITERATORS_TESTS) \
           $(TYPE_TRAITS_TESTS) \
           $(MPL_TESTS) \
           $(FUNCTIONAL_TESTS)
OBJS     = $(SRCS:.cpp=.o)
MAIN     = test_all

.PHONY: all
all: compile run

.PHONY: run
run: $(MAIN)
	./$(MAIN) --show_progress=true

.PHONY: compile
compile: $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(INC_DIRS) $(LIBS)

%.o: %.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INC_DIRS)

.PHONY: clean
clean:
	rm -f $(MAIN) $(OBJS)
