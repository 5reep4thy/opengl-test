default:
	clang++ src/*.cpp external/imgui/backends/imgui_impl_glfw.cpp external/imgui/backends/imgui_impl_opengl3.cpp external/imgui/*.cpp -g -lglfw -std=c++11 -arch arm64 -I external/imgui  -I include -I external/include -L/opt/homebrew/lib/ -framework OpenGL -lGLEW -o bin/main
clean:
	rm bin/main
