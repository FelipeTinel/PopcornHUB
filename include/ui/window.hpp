#pragma once

#include <GLFW/glfw3.h>

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

        // referencias para os services (a UI passa a enxergar o "backend")
        AuthService & auth_service;
        InteractionService & interaction_service;
        DoublyLinkedList<Content> & contents;

        Content * selected_content;

        // buffers de input, agora membros da classe em vez de "static" no .cpp
        char buffer_nome[128];
        char buffer_senha[128];
        char buffer_titulo_admin[128];

        bool initGLFW();
        bool initImGui();
        void cleanup();

        // uma funcao por tela, no lugar dos "case" do switch gigante
        void render_profile_choose();
        void render_register();
        void render_questionary();
        void render_user_dashboard();
        void render_content_detail();
        void render_admin_dashboard();
        void render_admin_formulary();

    public:

        Window(AuthService & auth, InteractionService & interaction, DoublyLinkedList<Content> & contents,
               int width = 1280, int height = 720, const char * title = "PopcornHUB");

        ~Window();

        void run();
};