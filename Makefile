
all: monogreek

monogreek: monogreek.c
	gcc -o monogreek monogreek.c -lutf8proc
