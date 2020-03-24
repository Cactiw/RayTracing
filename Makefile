CC = g++

all:
	g++ main.cpp vector.cpp objects/Object.h objects/Object.cpp objects/Sphere.h objects/Sphere.cpp classes/Ray.cpp classes/Color.h classes/Color.cpp classes/Ray.h -std=c++17 -Wall -o run -g

clean:
	rm classes/*.gch -f
	rm objects/*.gch -f
	rm *.gch -f
	rm run -f
