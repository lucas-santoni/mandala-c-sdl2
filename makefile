all:
	@echo "Please, tell me for which platform you want to compile ! :-)"
	@echo "  * GNU/Linux : make mandala.out"
	@echo "  * Windows : make mandala.exe (requires MinGW32)"

mandala.out:
	gcc mandala.c -lSDL2 -lm -o mandala.out

mandala.exe:
	gcc mandala.c -lmingw32 -lSDL2Main -lSDL2 -lm -o mandala.exe
