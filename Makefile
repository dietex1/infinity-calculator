TARGET = infinity_calculator_c++

SRCS := src/main.cpp src/Interface/UserInterface.cpp src/Logic/Calculator.cpp src/Logic/ImportExport.cpp  src/Numbers/Number.cpp src/Numbers/IntegerNumber.cpp src/Numbers/FloatNumber.cpp

BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
OBJS := $(SRCS:%.cpp=$(OBJDIR)/%.o)

DEPDIR = $(BUILDDIR)/dep
DEPFILES := $(SRCS:%.cpp=$(DEPDIR)/%.d)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedantic -Wextra -Wshadow -Wconversion -Wunreachable-code -g -Wno-long-long -O0 -ggdb

LD = g++

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

.PHONY: clean all compile doc

$(TARGET): $(OBJS)
	@echo Linking: $(LD) $@
	@$(LD) $(LDFLAGS) $^ -o $@

all: compile run

compile: $(TARGET)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR) $(DEPDIR)
	@echo Compiling: $(CXX) $@
	@$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	@echo Cleaning...
	@rm -rf $(BUILDDIR) $(TARGET)

$(OBJDIR) $(DEPDIR):
	@echo Creating directories...
	@for i in $(dir $(SRCS)); do \
            mkdir -p $@/$$i; \
        done

doc:
	@echo Generating doc...
	@doxygen Doxyfile > /dev/null

memtest: compile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

run: compile
	./$(TARGET)

$(DEPFILES):

include $(wildcard $(DEPFILES))