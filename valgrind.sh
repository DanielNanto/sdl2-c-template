cmake -B./build -H./ && 
make -C ./build &&
valgrind ./build/sdl-template > log.txt 2>&1