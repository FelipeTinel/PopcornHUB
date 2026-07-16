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
       src/services/genre_manager.cpp \
       src/core/user.cpp \
       src/core/content.cpp \
       src/core/comment.cpp \
       src/core/genre.cpp \
       src/core/question.cpp \
       src/containers/binary_tree.cpp

TARGET = build/ecv_terminal

ifeq ($(OS),Windows_NT)
    MKDIR = if not exist build mkdir build
    RUN_TARGET = ecv_terminal.exe
else
    MKDIR = mkdir -p build
    RUN_TARGET = ./ecv_terminal
endif

all: $(TARGET)

$(TARGET): $(SRCS)
	@$(MKDIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: all
	cd build && $(RUN_TARGET)

clean:
	rm -f $(TARGET)