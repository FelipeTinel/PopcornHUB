#include <cstring>

#include "ui/screens.hpp"
#include "ui/window.hpp"
#include "../../thirdparty/imgui/imgui.h"
#include "../../thirdparty/imgui/backends/imgui_impl_glfw.h"
#include "../../thirdparty/imgui/backends/imgui_impl_opengl3.h"

Window::Window(AuthService & auth, InteractionService & interaction, DoublyLinkedList<Content> & contents,
               int width, int height, const char * title)
    : windowId(nullptr), width(width), height(height), title(title),
      actual_screen(Screen::PROFILE_CHOOSE),
      auth_service(auth), interaction_service(interaction), contents(contents),
      selected_content(nullptr)
{
    buffer_nome[0] = '\0';
    buffer_senha[0] = '\0';
    buffer_titulo_admin[0] = '\0';

    initGLFW();
    initImGui();
}

Window::~Window() {
    cleanup();
}

bool Window::initGLFW() {

    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowId = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (windowId == nullptr) return false;

    glfwMakeContextCurrent(windowId);
    glfwSwapInterval(1);

    return true;
}

bool Window::initImGui() {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(windowId, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    return true;
}

void Window::cleanup() {

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (windowId != nullptr) glfwDestroyWindow(windowId);
    glfwTerminate();
}

void Window::render_profile_choose() {

    ImGui::Begin("PopcornHUB - Selecao de Perfil");
    ImGui::Text("Bem-vindo ao PopcornHUB");

    if (ImGui::Button("Admin", ImVec2(120, 40))) {
        actual_screen = Screen::ADMIN_DASHBOARD;
    }
    ImGui::SameLine();
    if (ImGui::Button("Usuario", ImVec2(120, 40))) {
        actual_screen = Screen::REGISTER;
    }

    ImGui::End();
}

void Window::render_register() {

    ImGui::Begin("PopcornHUB - Cadastro / Login");
    ImGui::Text("Digite um nome:");
    ImGui::InputText("##nome", buffer_nome, sizeof(buffer_nome));

    ImGui::Text("Uma senha:");
    ImGui::InputText("##senha", buffer_senha, sizeof(buffer_senha), ImGuiInputTextFlags_Password);

    if (ImGui::Button("Avancar", ImVec2(100, 30))) {

        if (!auth_service.login_user(buffer_nome, buffer_senha)) {
            auth_service.register_user(buffer_nome, buffer_senha);
            auth_service.login_user(buffer_nome, buffer_senha);
        }

        actual_screen = Screen::QUESTIONARY;
    }
    ImGui::SameLine();
    if (ImGui::Button("Voltar")) {
        actual_screen = Screen::PROFILE_CHOOSE;
    }

    ImGui::End();
}

void Window::render_questionary() {

    ImGui::Begin("PopcornHUB - Questionario");
    ImGui::Text("Ola %s, vamos personalizar seu catalogo!", buffer_nome);
    ImGui::Text("[Aqui vai a pergunta da arvore do seu amigo]");

    if (ImGui::Button("Sim", ImVec2(80, 35))) {
        actual_screen = Screen::USER_DASHBOARD;
    }
    ImGui::SameLine();
    if (ImGui::Button("Nao", ImVec2(80, 35))) {
        actual_screen = Screen::USER_DASHBOARD;
    }

    ImGui::End();
}

void Window::render_user_dashboard() {

    ImGui::Begin("PopcornHUB - Home");
    ImGui::Text("Recomendados para voce:");

    if (ImGui::BeginListBox("##rec", ImVec2(-1, 120))) {

        Node<Content> * node = contents.get_head();

        while (node != nullptr) {

            if (ImGui::Selectable(node->info.get_title().c_str())) {
                selected_content = &node->info;
                interaction_service.watch_content(node->info);
                actual_screen = Screen::CONTENT_DETAIL;
            }

            node = node->next;
        }

        ImGui::EndListBox();
    }

    if (ImGui::Button("Logout")) {
        auth_service.logout();
        actual_screen = Screen::PROFILE_CHOOSE;
    }

    ImGui::End();
}

void Window::render_content_detail() {

    ImGui::Begin("PopcornHUB - Detalhes");

    if (selected_content != nullptr) {
        ImGui::Text("Assistindo: %s", selected_content->get_title().c_str());
    }

    ImGui::Button("PLAY", ImVec2(-1, 200));

    if (ImGui::Button("Voltar para Home")) {
        actual_screen = Screen::USER_DASHBOARD;
    }

    ImGui::End();
}

void Window::render_admin_dashboard() {

    ImGui::Begin("Painel Administrativo");
    ImGui::Text("Gerenciar Conteudos:");

    if (ImGui::Button("Adicionar Novo Conteudo")) {
        buffer_titulo_admin[0] = '\0';
        actual_screen = Screen::ADMIN_FORMULARY;
    }

    ImGui::Separator();

    Node<Content> * node = contents.get_head();
    while (node != nullptr) {

        ImGui::Text("%s", node->info.get_title().c_str());
        ImGui::SameLine();

        std::string btn_label = "Editar##" + std::to_string(node->info.get_id());
        if (ImGui::Button(btn_label.c_str())) {
            selected_content = &node->info;
            std::strncpy(buffer_titulo_admin, node->info.get_title().c_str(), sizeof(buffer_titulo_admin));
            actual_screen = Screen::ADMIN_FORMULARY;
        }

        node = node->next;
    }

    if (ImGui::Button("Sair do Painel")) {
        actual_screen = Screen::PROFILE_CHOOSE;
    }

    ImGui::End();
}

void Window::render_admin_formulary() {

    ImGui::Begin("Admin - Formulario");
    ImGui::Text("Cadastrar/Editar Item");

    ImGui::InputText("Nome", buffer_titulo_admin, sizeof(buffer_titulo_admin));

    if (ImGui::Button("Salvar")) {

        if (selected_content != nullptr) {
            selected_content->set_title(buffer_titulo_admin);
            selected_content = nullptr;
        }

        actual_screen = Screen::ADMIN_DASHBOARD;
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancelar")) {
        selected_content = nullptr;
        actual_screen = Screen::ADMIN_DASHBOARD;
    }

    ImGui::End();
}

void Window::run() {

    while (!glfwWindowShouldClose(windowId)) {

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        switch (actual_screen) {

            case Screen::PROFILE_CHOOSE:  render_profile_choose();  break;
            case Screen::REGISTER:        render_register();        break;
            case Screen::QUESTIONARY:     render_questionary();     break;
            case Screen::USER_DASHBOARD:  render_user_dashboard();  break;
            case Screen::CONTENT_DETAIL:  render_content_detail();  break;
            case Screen::ADMIN_DASHBOARD: render_admin_dashboard(); break;
            case Screen::ADMIN_FORMULARY: render_admin_formulary(); break;
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(windowId, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(windowId);
    }
}