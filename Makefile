all:
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp Level.cpp Player.cpp Dot.cpp Coin.cpp HUD_Text.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf