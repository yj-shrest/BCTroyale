# This a C++ project built using SDL2 and SFML libraries

## On windows
To build, run the runcode.bat script on command prompt
After that main.exe will run the game

## On Linux
The following script will build you the game as many distributions come with SDL out of the box
g++ -o main main.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

### if you don't have SDL you can install the package using the command

- On Fedora/RHEL-based systems: `sudo dnf install SDL2 SDL2-devel SDL2_ttf-devel SDL2_mixer-devel`
- On Ubuntu/Debian-based systems: `sudo apt-get install libsdl2-dev  libsdl2-ttf-dev`

### then, you can run the game by the command
`./main` or `./main.exe` (windows)
## Or 
simply opening the executble main
