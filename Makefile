all: build

build: poduri lego

poduri: poduri.o
	g++ -o poduri poduri.o

poduri.o: poduri.cpp
	g++ -c poduri.cpp

lego:lego.o
	g++ -o lego lego.o

lego.o:lego.cpp
	g++ -c lego.cpp

run-p1:
	./poduri

run-p3:
	./lego

clean:
	rm -f poduri lego
	rm -f *.o
