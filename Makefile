CXX = clang++
CXX_FLAGS =  -arch arm64 -std=c++11
BIN_FOLDER = bin
EXE = $(BIN_FOLDER)/app
SRC_FOLDER = src
TEST_FOLDER = $(SRC_FOLDER)/tests
IMGUI_DIR = external/imgui
SOURCES = $(SRC_FOLDER)/main.cpp

#APP SOURES
SOURCES += $(SRC_FOLDER)/index_buffer.cpp $(SRC_FOLDER)/renderer.cpp $(SRC_FOLDER)/shader.cpp $(SRC_FOLDER)/stb_image.cpp $(SRC_FOLDER)/texture.cpp $(SRC_FOLDER)/vertex_array.cpp $(SRC_FOLDER)/vertex_buffer.cpp

#TEST SOURCES
SOURCES += $(TEST_FOLDER)/test_clear_color.cpp $(TEST_FOLDER)/test.cpp

#IMGUI SOURES
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_widgets.cpp $(IMGUI_DIR)/imgui_tables.cpp

# DEPENDENCIES
LIBS = -L/opt/homebrew/lib -framework OpenGL -lGLEW -lglfw

# INCLUDES
INCLUDES = -I include -I external/include -I $(IMGUI_DIR) -I $(SRC_FOLDER)/tests

debug:
	$(CXX) $(SOURCES) -g $(CXX_FLAGS)  $(LIBS) $(INCLUDES) -o $(EXE)

build:
	$(CXX) $(SOURCES) -O3 $(CXX_FLAGS)  $(LIBS) $(INCLUDES) -o $(EXE)

clean:
	rm $(EXE)
