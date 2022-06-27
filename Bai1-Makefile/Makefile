.PHONY: rule1 rule2 rule3 all clean

var = "var"
var3 ?= "var3"
include vietdz.mk

var1 = $(var)
var2 := $(var)
var3 ?= $(var)

rule4: huyNgu.c huyNgu.h
	@echo $@
	@echo $<
	@echo $^


rule3:
	@echo "$(var1)"
	@echo "$(var2)"
	@echo "$(var3)"

var := "changed"

rule1:
	echo "Hello im rule1"

rule2:
	@echo "Hello im rule1"

all: 
	gcc -o main main.c ./inc/hello.c -I.

clean:
	rm -rf main
