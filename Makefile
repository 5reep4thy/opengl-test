default:
	clang++ src/*.cpp -g -lglfw -std=c++11 -arch arm64 -I include -I external/include -L/opt/homebrew/lib/ -framework OpenGL -lGLEW -o bin/main
clean:
	rm bin/main
