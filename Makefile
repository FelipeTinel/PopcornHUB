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
       src/services/statistics.cpp \
       src/services/statistics_service.cpp \
       src/core/user.cpp \
       src/core/content.cpp \
       src/core/comment.cpp \
       src/core/genre.cpp \
       src/core/question.cpp \
       src/core/watched_entry.cpp \
       src/containers/binary_tree.cpp

TARGET_DIR = build
TARGET = $(TARGET_DIR)/ecv_terminal

ifeq ($(OS),Windows_NT)
    RM_CMD = if exist $(TARGET_DIR) rmdir /s /q $(TARGET_DIR)
else
    RM_CMD = rm -rf $(TARGET_DIR)
endif

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

run: all
	./$(TARGET)

clean:
	$(RM_CMD)