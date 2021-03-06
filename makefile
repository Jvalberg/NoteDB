CC=g++
LD=g++

CFLAGS=-std=c++11
LFLAGS=-Wall -std=c++11  

MODULES=noted notectl helpers
MODULES_DAEMON=noted helpers
MODULES_CTL=notectl helpers

BUILD_DIR=$(addprefix build/,$(MODULES))
SRC_DIR=$(addprefix src/,$(MODULES))
# SRC=$(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
# OBJ=$(patsubst src/%.cpp, build/%.o, $(SRC))

INTERNAL_INCLUDES=$(addprefix -I,$(SRC_DIR))
SHARED_LIBRARIES=-lboost_system -lboost_filesystem

DAEMON_DIRS=$(addprefix src/,$(MODULES_DAEMON))
DAEMON_SRC=$(foreach bdir,$(DAEMON_DIRS),$(wildcard $(bdir)/*.cpp))
DAEMON_OBJS=$(patsubst src/%.cpp, build/%.o, $(DAEMON_SRC))

CTL_DIRS=$(addprefix src/,$(MODULES_CTL))
CTL_SRC=$(foreach sdir,$(CTL_DIRS),$(wildcard $(sdir)/*.cpp))
CTL_OBJ=$(patsubst src/%.cpp, build/%.o,$(CTL_SRC))

vpath %.cpp $(SRC_DIR)

define make-goal
$(1)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INTERNAL_INCLUDES) -c $$< -o $$@
	@echo $(1)
endef

# RESULT=$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))

all: checkdirs daemon ctl install

install: install.sh
	sh install.sh

daemon: build/noted.out

ctl: build/notectl.out

build/notectl.out: $(CTL_OBJ)
	$(LD) $(LFLAGS) $(SHARED_LIBRARIES) $^ -o $@

build/noted.out: $(DAEMON_OBJS)
	$(LD) $(LFLAGS) $(SHARED_LIBRARIES) $^ -o $@

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf build

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal, $(bdir))))
