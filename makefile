CEXE=gcc -std=c11 # Variable para crear el ejecutable del codigo que ya esta en formato .o
CO=gcc -std=c11 -Wall -Werror -c # Variable para compilar archivos .c a archivos .o (object o codigo maquina)

# symbolo # para comentarios en sintaxis makefile

# Crea todos los archivos del proyecto
all: sistema publicador suscriptor 
	@printf "\nTodos los archivos ejecutables han sido creados con exito.\n"

clear: rm_publicador \
	rm_suscriptor \
	rm_sistema
	@printf "\nArchivos eliminados\n"

# Comandos individuales
publicador: publisher.o
	@$(CEXE) -o $@ $^
	-@rm $^
	@printf "\nEl archivo \"publicador\" ha sido creado\n"

suscriptor: suscriber.o
	@$(CEXE) -o $@ $^
	-@rm $^
	@printf "\nEl archivo \"suscriptor\" ha sido creado\n"

sistema: system.o SusSistema.o stack.o
	@$(CEXE) -o $@ $^
	-@rm $^
	@printf "\nEl archivo \"sistema\" ha sido creado\n"


# Dependencias

publisher.o: src/publisher/publisher.c
	@$(CO) $^
	
suscriber.o: src/suscriber/suscriber.c
	@$(CO) $^

system.o: src/system/system.c
	@$(CO) $^

SusSistema.o: src/system/SusSistema/SusSistema.c
	@$(CO) $^

stack.o: src/system/stack/stack.c
	@$(CO) $^

# Eliminacion de archivos individuales y sus dependencias
rm_publicador:
	-@rm publicador
	@printf "\nEl archivo \"publicador\" y sus dependencias se han eliminado.\n"
	
rm_suscriptor:
	-@rm suscriptor
	@printf "\nEl archivo \"suscriptor\" y sus dependencias se han eliminado.\n"

rm_sistema:
	-@rm sistema 
	@printf "\nEl archivo \"sistema\" y sus dependencias se han eliminado.\n"
	