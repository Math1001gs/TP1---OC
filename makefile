all: compile-run

compile-run: main.c func/func.c
	gcc main.c func/func.c -o assembler
	./assembler teste.asm


clean:
	del /Q run.exe *.o 2>nul