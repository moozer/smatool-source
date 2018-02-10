smatool: smatool.o
	gcc smatool.o -L/usr/lib -lbluetooth -lm -o smatool 
smatool.o: smatool.c
	gcc -c smatool.c 
