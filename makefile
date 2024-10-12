EXECUTE=gcc -std=c11 -o main # Variable para ejecutar el codigo que ya esta en formato .o
CO=gcc -std=c11 -Wall -Werror -c # Variable para compilar archivos .c a archivos .o (object o codigo maquina)

# comentario

# Ejecuta el archivo
all: main.o
	@$(EXECUTE) *.o
	@echo "\nEjecutando el archivo \"main\"\n"
	@./main 

clear:
	@echo "\nArchivos eliminados\n"
	@rm *.o
	@rm main

#dependencias
main.o: main.c
	@$(CO) main.c