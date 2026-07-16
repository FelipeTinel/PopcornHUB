# Compila e executa apenas a versao de TERMINAL do projeto (sem ImGui/GLFW/OpenGL).
# Uso:
#   make          -> compila
#   make run      -> compila e executa
#   make clean    -> remove o executavel

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

SRCS = src/main_console.cpp \
       src/ui/console.cpp \
       src/services/auth_service.cpp \
       src/services/interaction_service.cpp \
       src/services/admin_service.cpp \
       src/services/user_manager.cpp \
       src/services/comment_manager.cpp \
       src/services/content_manager.cpp \
       src/core/user.cpp \
       src/core/content.cpp \
       src/core/comment.cpp

TARGET = build/ecv_terminal

all: $(TARGET)

$(TARGET): $(SRCS)
	mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: all
	cd build && ./ecv_terminal

clean:
	rm -f $(TARGET)
