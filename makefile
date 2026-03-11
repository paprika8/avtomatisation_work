SRC  := $(shell find . -name '*.cpp') $(shell find . -name '*.c')
HDR := $(shell find . -name '*.h')
SRC_NAME := $(subst ./,/,$(SRC))
OBJS  := $(addprefix obj, $(SRC_NAME:.cpp=.o)) 

DEPS := $(addprefix obj, $(SRC_NAME:.cpp=.d)) 
INCLUDE := -I./include
LIB :=  -L./lib -lfreeglut -lopengl32 -lgdi32 -lwinmm
FLAGS := -g -fpermissive -Wextra -MMD -MP -w -DUNICODE -std=c++20 -DFREEGLUT_STATIC #-static-libgcc -static-libstdc++
ARGS := $(FLAGS)
TARGET := automat
.PHONY: all clear clear_all

all: build/$(TARGET).exe

rebuild: clear all

build/$(TARGET).exe:  $(OBJS)
	@mkdir -p build
	g++ $(ARGS) $(OBJS) $(LIB) -o build/$(TARGET).exe 

obj/%.co: %.c
	@mkdir -p $(dir $@)
	gcc $(ARGS) $(INCLUDE) -c $< -o $@

obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	g++ $(ARGS) $(INCLUDE) -c $< -o $@

-include $(DEPS)

clear: 
	rm -f $(OBJS)
	rm -f $(DEPS)

clear_all: clear
	rm -f build/$(TARGET).exe