.PHONY: clean

all: micro32 

micro32: micro32.c
	gcc -o micro32 micro32.c

clean:
	rm micro32 
