smatool: smatool.o config.o
	gcc smatool.o config.o -L/usr/lib -lbluetooth -lm -o smatool 
smatool.o: smatool.c
	gcc -c smatool.c -I.
config.o: config.c
	gcc -c config.c -I.