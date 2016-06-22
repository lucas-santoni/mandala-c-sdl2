MAKEFLAGS += --silent
MAKEFLAGS += --ignore-errors

all:
	@echo "Let's make this !"
	gcc -o mandala mandala.c -lSDL2 -lm
	@echo "If no errors appeared, just ./mandala ! Enjoy mandala ! ;-)"

clean:
	rm -f mandala

help:
	@echo "Juste use make (without any argument) to compile."
	@echo "Use make clean in order to delete mandala."
	@echo "If you have errors during compilation, you can contact me for help."
	@echo "Windows users, you can use MinGW with this project."