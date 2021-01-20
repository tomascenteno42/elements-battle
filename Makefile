########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -g    # -fsanitize=address -Wno-stack-protector -Wall -Wconversion -Wextra  -std=c++14 -pedantic -Wshadow -Werror -O1 -fno-omit-frame-pointer 
LDFLAGS = 

# Makefile settings - Can be customized.
APPNAME = BattleOfTheElements
EXT = .cpp
BASEDIR = 
SRCDIR = src
LIBDIR = lib
OBJDIR = obj

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(BASEDIR)/*$(EXT))
OBJ = $(SRC:$(BASEDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(BASEDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
ifeq ($(OS),Windows_NT)
    $(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) ${SRCDIR}/*/*.cpp ${SRCDIR}/*/*.h ${SRCDIR}/*.cpp ${SRCDIR}/*.h *.dll *.cpp 

else
    $(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) ${SRCDIR}/*/*.cpp ${SRCDIR}/*/*.h ${SRCDIR}/*.cpp ${SRCDIR}/*.h *.cpp -L/usr/include/SFML/ -lsfml-graphics -lsfml-window -lsfml-system 

endif

# Creates the dependecy rules
%.d: $(BASEDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(BASEDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)