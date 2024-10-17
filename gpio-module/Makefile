CC = gcc
CFLAGS = -Wall -Werror
INC = -I include
all: gpio_app

gpio_app: main.o gpio.o app.o
	$(CC) -o gpio_app main.o gpio.o app.o

main.o: test/main.c include/gpio.h
	$(CC) $(CFLAGS) $(INC) -c test/main.c

gpio.o: src/gpio.c include/gpio.h
	$(CC) $(CFLAGS) $(INC) -c src/gpio.c

app.o: src/app.c include/gpio.h
	$(CC) $(CFLAGS) $(INC) -c src/app.c

clean:
	rm -f *.o gpio_app
