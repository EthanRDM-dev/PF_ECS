CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-sign-compare
LDFLAGS = -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
INCFLAGS = -Iinclude -IECS/include -IEngine/include -IComponents/include -ISystems/include -IPhysics2/include
#DEFFLAGS = -DECS_DEBUG_ #à ajouter après les CXXFLAGS

all: clean bin/BasicECS launch

launch:
	bin/BasicECS.exe

bin/BasicECS: obj/main.o obj/Engine.o obj/AssetsLoader.o obj/Manager.o obj/icon.res
	g++ $(CXXFLAGS) -o bin/BasicECS obj/main.o obj/Engine.o obj/AssetsLoader.o obj/Manager.o obj/icon.res $(INCFLAGS) $(LDFLAGS) 

obj/main.o: main.cpp 
	g++ $(CXXFLAGS) -o obj/main.o -c main.cpp $(INCFLAGS) $(LDFLAGS)

obj/Engine.o: Engine/src/Engine.cpp
	g++ $(CXXFLAGS) -o obj/Engine.o -c Engine/src/Engine.cpp $(INCFLAGS) $(LDFLAGS)

obj/AssetsLoader.o: Engine/src/AssetsLoader.cpp
	g++ $(CXXFLAGS) -o obj/AssetsLoader.o -c Engine/src/AssetsLoader.cpp $(INCFLAGS) $(LDFLAGS)

obj/Manager.o: ECS/src/Manager.cpp
	g++ $(CXXFLAGS) -o obj/Manager.o -c ECS/src/Manager.cpp $(INCFLAGS) $(LDFLAGS)

obj/icon.res:
	windres res/icon.rc -O coff -o obj/icon.res

clean:
	del obj\*.o bin\*.exe

########################################################################
####################### Makefile Template ##############################
########################################################################

# ODIR := obj
# OBJ = $(wildcard $(ODIR)/*.o)

# Compiler settings - Can be customized.
# CC = g++
# CXXFLAGS = -std=c++17 -Wall -Wextra
# LDFLAGS = -Llib -lmingw32 -lSDL2main -lSDL2
# INCLUDES = -Iinclude

# Makefile settings - Can be customized.
# APPNAME = ProjetL3
# EXT = .cpp
# SRCDIR = ./
# OBJDIR = obj

############## Do not change anything from here downwards! #############
# SRC = $(wildcard $(SRCDIR)/*$(EXT))
# OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
# DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
# RM = rm
# DELOBJ = $(OBJ)
# Windows OS variables & settings
# DEL = del
# EXE = .exe
# WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

# all: $(APPNAME)

# Builds the app
# $(APPNAME): $(OBJ)
# 	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
# %.d: $(SRCDIR)/%$(EXT)
# 	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
# -include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
# $(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
# 	$(CC) $(CXXFLAGS) -o $@ -c $<

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
# .PHONY: cleanw
# cleanw:
# 	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
# .PHONY: cleandepw
# cleandepw:
# 	$(DEL) $(DEP)