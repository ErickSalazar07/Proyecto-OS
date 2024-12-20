CEXE=gcc -std=c11 -o # Variable para crear el ejecutable del codigo que ya esta en formato .o
CO=gcc -std=c11 -Wall -Werror -c # Variable para compilar archivos .c a archivos .o (object o codigo maquina)

# symbolo # para comentarios en sintaxis makefile

# Crea todos los archivos del proyecto
all: publisher suscriber system 
	@printf "\nTodos los archivos ejecutables han sido creados con exito.\n"

clear:
	@rm publisher
	@rm system
	@rm suscriber
	@printf "\nArchivos eliminados\n"

# Comandos individuales
publisher: publisher.o
	@$(CEXE) publisher publisher.o
	@rm publisher.o
	@printf "\nEl archivo \"publisher\" ha sido creado\n"


suscriber: suscriber.o
	@$(CEXE) suscriber suscriber.o
	@rm suscriber.o
	@printf "\nEl archivo \"suscriber\" ha sido creado\n"

system: system.o SusSistema.o stack.o
	@$(CEXE) system system.o SusSistema.o stack.o
	@rm system.o SusSistema.o stack.o
	@printf "\nEl archivo \"system\" ha sido creado\n"


# Dependencias
main.o: main.c
	@$(CO) main.c
	
publisher.o: src/publisher/publisher.c
	@$(CO) src/publisher/publisher.c
	
suscriber.o: src/suscriber/suscriber.c
	@$(CO) src/suscriber/suscriber.c

system.o: src/system/system.c
	@$(CO) src/system/system.c

SusSistema.o: src/system/SusSistema/SusSistema.c
	@$(CO) src/system/SusSistema/SusSistema.c

stack.o: src/system/stack/stack.c
	@$(CO) src/system/stack/stack.c

# Eliminacion de archivos individuales y sus dependencias
rm_publisher:
	@rm publisher 
	@printf "\nEl archivo \"publisher\" y sus dependencias se han eliminado\n"
	
rm_suscriber:
	@rm suscriber 
	@printf "\nEl archivo \"suscriber\" y sus dependencias se han eliminado\n"

rm_system:
	@rm system 
	@printf "\nEl archivo \"system\" y sus dependencias se han eliminado\n"
	