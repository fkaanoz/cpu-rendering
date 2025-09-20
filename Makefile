build:
	gcc -Wall -std=c99 ./src/*c \
	-I/opt/homebrew/opt/sdl2/include \
	-L/opt/homebrew/opt/sdl2/lib \
	-lSDL2 \
	-o graphy

run:
	./graphy

clean:
	rm graphy
