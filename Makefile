BINDIR      = bin

10Dof-D_Demo:main.o Waveshare_10Dof-D.o
	gcc -Wall -o 10Dof-D main.o Waveshare_10Dof-D.o -lwiringPi -lm -std=gnu99
main.o: main.c Waveshare_10Dof-D.h
	gcc -Wall -c main.c -lwiringPi -lm -std=gnu99
Waveshare_10Dof-D.o: Waveshare_10Dof-D.c Waveshare_10Dof-D.h
	gcc -Wall -c Waveshare_10Dof-D.c -lwiringPi -lm -std=gnu99	
install:
	install -D -m 755 10Dof-D $(DESTDIR)/$(BINDIR)/10Dof-D
	install -D -m 644 10dof.service $(DESTDIR)/etc/systemd/system/10dof.service
clean:
	rm main.o Waveshare_10Dof-D.o 10Dof-D_Demo
