This a C++ project ...(will add later)

On windows, to build, run the runcode.bat script on command prompt
After that main.exe will run the game

On Linux, the following script will build you the game as many distributions come with SDL out of the box
g++ -o main main.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

if you don't have SDL you can install the package using the command

On Fedora/RHEL-based systems: sudo dnf install SDL2 SDL2-devel SDL2_ttf-devel
On Ubuntu/Debian-based systems: sudo apt-get install libsdl2-dev  libsdl2-ttf-dev

then, you can run the game by the command
./main
or simply opening the executble main