all:
	g++ -lSDL2 main.cpp engine.cpp -o game

clean:
	rm game
