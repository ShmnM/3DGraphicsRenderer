program.exe: main.o SDL_Point3D.o Camera.o
	g++ -Isrc/include -Lsrc/lib main.o SDL_Point3D.o Camera.o -lmingw32 -lSDL3 -o program.exe

main.o: main.cpp
	g++ -c -Isrc/include main.cpp -o main.o

SDL_Point3D.o: SDL_Point3D.cpp src/include/SDL_Point3D.h
	g++ -c -Isrc/include SDL_Point3D.cpp -o SDL_Point3D.o

Camera.o: Camera.cpp src/include/Camera.h
	g++ -c -Isrc/include Camera.cpp -o Camera.o

clean:
	del *.o program.exe 

run:
	program.exe
