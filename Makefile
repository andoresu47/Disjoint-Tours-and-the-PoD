############################################
# Code adapted from: github.com/clementvidon/Makefile_tutor

NAME        := main
TESTNAME	:= testmain

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRC_DIR   source directory
# OBJ_DIR   object directory
# SRCS      source files
# OBJS      object files
#
# CXX       compiler
# CXXFLAGS  compiler flags
# CPPFLAGS  preprocessor flags

SRC_DIR     := src
MAIN		:= \
	app/main.cpp
TESTMAIN	:= \
	test/testmain.cpp
SRCS        := \
    cycles/hamiltonian_cycles.cpp	\
	paths/hamiltonian_paths.cpp		

SRCS        := $(SRCS:%=$(SRC_DIR)/%)                                                                                   
OBJS        := $(SRCS:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)
OBJMAIN		:= $(MAIN:%.cpp=%.o)
OBJTEST		:= $(TESTMAIN:%.cpp=%.o)
CXX         := g++ 
CXXFLAGS 	:= -g -O3 -Wpedantic -Wall -Wextra -Wmisleading-indentation -Wunused -Wuninitialized -Wshadow -std=c++17
CPPFLAGS    := -I headers

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKEFLAGS make flags

RM          := rm -f
MAKEFLAGS   += --no-print-directory

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   linking .o -> binary
# %.o       compilation .cpp -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME) $(TESTNAME)

$(NAME): $(OBJS) $(OBJMAIN)
	$(CXX) $(OBJS) $(OBJMAIN) -o $(NAME)
	$(info CREATED $(NAME))

$(TESTNAME): $(OBJS) $(OBJTEST)
	$(CXX) $(OBJS) $(OBJTEST) -o $(TESTNAME)
	$(info CREATED $(TESTNAME))

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

$(OBJMAIN): $(MAIN)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $(OBJMAIN) $(MAIN)
	$(info CREATED $(OBJMAIN))

$(OBJTEST): $(TESTMAIN)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $(OBJTEST) $(TESTMAIN)
	$(info CREATED $(OBJTEST))

clean:
	$(RM) $(OBJS) $(OBJMAIN) $(OBJTEST)

fclean: clean
	$(RM) $(NAME) $(TESTNAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT:

############################################
