all: compile-run

compile-run: main.c func/func.c
	gcc main.c func/func.c -o assembler
	./assembler teste.asm -o saida.bin


clean:
	rm -f run *.o
