## Makefile ##
## Source : http://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/

CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := bin/runner

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS -fasynchronous-unwind-tables -fexceptions
CFLAGS += -fstack-protector-strong -grecord-gcc-switches -O2 -pipe -Wall -Werror=format-security
CFLAGS += -Werror=implicit-function-declaration -Wl,-z,defs -Wl,-z,now -Wl,-z,relro
CFLAGS += -fwrapv -fno-strict-aliasing -flto -mstackrealign # Additional
#CFLAGS += -fpie i-Wl,-pie # for executables, full ASLR 
#CFLAGS += -fpic -shared # for shared libraries
#CFLAGS += -fplugin=annobin # for hardening quality control
#CFLAGS += -fstack-clash-protection -mcet -fcf-protection # unknown

LIB := -pthread -L lib #-lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)
  
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<
  
clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
  
# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester
  
# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
