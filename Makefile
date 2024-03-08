all:
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp Player.cpp Level.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf