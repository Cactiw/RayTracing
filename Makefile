CC = g++

all:
	g++ main.cpp vector.cpp objects/Object.h objects/Object.cpp objects/Sphere.h objects/Sphere.cpp classes/Ray.cpp classes/Ray.h -std=c++17 -O2 -Wall -o run

clean:
	rm classes/*.gch -f
	rm objects/*.gch -f
	rm *.gch -f
	rm run -f
