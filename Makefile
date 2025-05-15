all:
	g++ -lSDL2 main.cpp engine.cpp vec3.cpp -o game -g

clean:
	rm game
