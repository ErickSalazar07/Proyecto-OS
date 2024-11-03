CEXE=gcc -std=c11 -o # Variable para crear el ejecutable del codigo que ya esta en formato .o
CO=gcc -std=c11 -Wall -Werror -c # Variable para compilar archivos .c a archivos .o (object o codigo maquina)

# comentario

# Ejecuta el archivo
all: publisher suscriber system 
	@echo "\nTodos los archivos ejecutables han sido creados con exito.\n"

clear:
	@rm *.o
	@rm publisher
	@rm system
	@rm suscriber
	@echo "\nArchivos eliminados\n"

# Comandos individuales
publisher: publisher.o
	@$(CEXE) publisher publisher.o
	@echo "\nEl archivo \"publisher\" ha sido creado\n"


suscriber: suscriber.o
	@$(CEXE) suscriber suscriber.o
	@echo "\nEl archivo \"suscriber\" ha sido creado\n"

system: system.o
	@$(CEXE) system system.o
	@echo "\nEl archivo \"system\" ha sido creado\n"


#dependencias
main.o: main.c
	@$(CO) main.c
	
publisher.o: src/publisher/publisher.c
	@$(CO) src/publisher/publisher.c
	
suscriber.o: src/suscriber/suscriber.c
	@$(CO) src/suscriber/suscriber.c

system.o: src/system/system.c
	@$(CO) src/system/system.c