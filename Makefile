all: main

main: main.cpp Entity.cpp player.cpp mob.cpp Bullet.cpp client.cpp server.cpp windowrenderer.cpp SDL.cpp position.cpp crosshair.cpp camera.cpp
	g++ -I src/include -o BCTroyale main.cpp Entity.cpp player.cpp mob.cpp Bullet.cpp client.cpp server.cpp windowrenderer.cpp SDL.cpp position.cpp crosshair.cpp camera.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lsfml-network -lsfml-system

clean:
	rm -f BCTroyale
