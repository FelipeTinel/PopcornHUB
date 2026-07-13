#pragma once

#include <GLFW/glfw3.h>

#include "core/comment.hpp"
#include "ui/screens.hpp"
#include "services/auth_service.hpp"
#include "services/interaction_service.hpp"
#include "containers/doubly_linked_list.hpp"
#include "core/content.hpp"

class Window {

    private:

        GLFWwindow * windowId;

        int width;
        int height;
        const char * title;

        Screen actual_screen;

        AuthService & auth_service;
        InteractionService & interaction_service;
        DoublyLinkedList<Content> & contents;
        DoublyLinkedList<Comment> & comments; 

        Content * selected_content;

        char buffer_comentario[256];            
        float buffer_avaliacao;   
        char buffer_nome[128];
        char buffer_senha[128];
        char buffer_titulo_admin[128];

        const char * genre_to_string(Genre g);
        const char * type_to_string(Type t);

        bool initGLFW();
        bool initImGui();
        void cleanup();

        void render_profile_choose();
        void render_register();
        void render_questionary();
        void render_user_dashboard();
        void render_content_detail();
        void render_admin_dashboard();
        void render_admin_formulary();

    public:

        Window(AuthService & auth, InteractionService & interaction, DoublyLinkedList<Content> & contents,
            DoublyLinkedList<Comment> & comments, int width = 1280, int height = 720, const char * title = "PopcornHUB");

        ~Window();

        void run();
};