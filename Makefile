
# Makefile to build TREK, the packing list expert system

CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-I. -std=gnu++0x #-Wall -Weffc++

FINAL_EXECUTABLE_NAME=trek

SRCS=main.cpp state.cpp frame.cpp working_memory.cpp knowledge_base.cpp application_specific_definitions.cpp 
OBJS=$(subst .cpp,.o,$(SRCS))

all: trek

trek: $(OBJS) patch
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $(FINAL_EXECUTABLE_NAME) $(OBJS) $(LDLIBS) 

clean: dist-clean
	$(RM) $(OBJS)
	$(RM) *.patch

dist-clean:
	$(RM) $(FINAL_EXECUTABLE_NAME)

BACKUP_DIR="$(shell find ~/backup/trek/ -type d | sort | tail -n 1)"
patch:
	echo $(BACKUP_DIR)
	@echo "Files that have been changed since last backup:" > $(FINAL_EXECUTABLE_NAME).patch
	@echo "-----------------------------------------------" >> $(FINAL_EXECUTABLE_NAME).patch
	@-diff -ubB --brief ../$(FINAL_EXECUTABLE_NAME) $(BACKUP_DIR)/ >> $(FINAL_EXECUTABLE_NAME).patch
	@echo "-----------------------------------------------" >> $(FINAL_EXECUTABLE_NAME).patch
	@echo "Diff for the above mentioned files:" > $(FINAL_EXECUTABLE_NAME).patch
	@-diff -rubB ../$(FINAL_EXECUTABLE_NAME) $(BACKUP_DIR)/ >> $(FINAL_EXECUTABLE_NAME).patch
