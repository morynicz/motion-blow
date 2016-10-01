CFLAGS = -std=gnu99

mot: main.c
	gcc main.c ${CFLAGS} -lwiringPi -o mot 
