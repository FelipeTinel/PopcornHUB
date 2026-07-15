#include <cstring>

#include "ui/screens.hpp"
#include "ui/window.hpp"
#include "core/comment.hpp"
#include "../../thirdparty/imgui/imgui.h"
#include "../../thirdparty/imgui/backends/imgui_impl_glfw.h"
#include "../../thirdparty/imgui/backends/imgui_impl_opengl3.h"

Window::Window(AuthService & auth, InteractionService & interaction, AdminService & content_admin,
               DoublyLinkedList<Content> & contents, DoublyLinkedList<Comment> & comments,
               int width, int height, const char * title)
    : windowId(nullptr), width(width), height(height), title(title),
      actual_screen(Screen::PROFILE_CHOOSE),
      auth_service(auth), interaction_service(interaction), content_admin_service(content_admin),
      contents(contents), comments(comments),
      selected_content(nullptr), login_error(false)

{
    buffer_nome[0] = '\0';
    buffer_senha[0] = '\0';
    buffer_titulo_admin[0] = '\0';
    buffer_comentario[0] = '\0';
    buffer_avaliacao = 5.0f;

    buffer_type_admin = 0;
    buffer_genre_admin = 0;
    buffer_year_admin = 2024;
    buffer_views_admin = 0;
    buffer_rating_admin = 0.0f;

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

        bool logged_in = auth_service.login_user(buffer_nome, buffer_senha);

        if (!logged_in) {
            bool created = auth_service.register_user(buffer_nome, buffer_senha);
            if (created) logged_in = auth_service.login_user(buffer_nome, buffer_senha);
        }

        if (logged_in) {
            login_error = false;
            actual_screen = Screen::QUESTIONARY;
        } else {
            login_error = true;
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Voltar")) {
        login_error = false;
        actual_screen = Screen::PROFILE_CHOOSE;
    }

    if (login_error) {
        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "Senha incorreta para esse usuario.");
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

const char * Window::genre_to_string(Genre g) {
    switch (g) {
        case Genre::ACTION:           return "Acao";
        case Genre::COMEDY:           return "Comedia";
        case Genre::ROMANCE:          return "Romance";
        case Genre::HORROR:           return "Terror";
        case Genre::SUSPENSE:         return "Suspense";
        case Genre::DRAMA:            return "Drama";
        case Genre::SCIENCE_FICTION:  return "Ficcao Cientifica";
    }
    return "Desconhecido";
}

const char * Window::type_to_string(Type t) {
    switch (t) {
        case Type::MOVIE:       return "Filme";
        case Type::SERIES:      return "Serie";
        case Type::DOCUMENTARY: return "Documentario";
        case Type::ANIME:       return "Anime";
        case Type::CARTOON:     return "Desenho";
    }
    return "Desconhecido";
}

void Window::render_content_detail() {

    ImGui::Begin("PopcornHUB - Detalhes");

    if (selected_content == nullptr) {
        ImGui::Text("Nenhum conteudo selecionado.");
        if (ImGui::Button("Voltar para Home")) {
            actual_screen = Screen::USER_DASHBOARD;
        }
        ImGui::End();
        return;
    }

    ImGui::Text("Assistindo: %s", selected_content->get_title().c_str());
    ImGui::Text("Genero: %s", genre_to_string(selected_content->get_genre()));
    ImGui::SameLine();
    ImGui::Text("| Tipo: %s", type_to_string(selected_content->get_type()));
    ImGui::Text("Ano: %d", selected_content->get_year());
    ImGui::Text("Views: %ld", selected_content->get_views());
    ImGui::Text("Avaliacao media: %.1f (%d avaliacoes)",
                selected_content->get_rating(), selected_content->get_rating_count());

    ImGui::Separator();
    ImGui::Button("PLAY", ImVec2(-1, 200));

    ImGui::Separator();

    bool already_rated = auth_service.is_logged_in() &&
        interaction_service.has_rated(auth_service.get_current_user()->get_id(), selected_content->get_id());

    if (already_rated) {
        ImGui::Text("Voce ja avaliou este conteudo.");
    } else {
        ImGui::Text("Deixe sua avaliacao:");
        ImGui::SliderFloat("##nota", &buffer_avaliacao, 0.0f, 5.0f, "%.1f");
        ImGui::SameLine();
        if (ImGui::Button("Avaliar")) {
            interaction_service.rate_content(*selected_content, buffer_avaliacao);
        }
    }

    ImGui::Separator();
    ImGui::Text("Comentarios:");

    if (ImGui::BeginChild("##comentarios", ImVec2(-1, 120), true)) {

        Node<Comment> * node = comments.get_head();

        while (node != nullptr) {
            if (node->info.get_content_id() == selected_content->get_id()) {

                User * author = auth_service.find_by_id(node->info.get_user_id());
                std::string author_name = (author != nullptr) ? author->get_name() : "Usuario desconhecido";

                ImGui::TextWrapped("%s: %s", author_name.c_str(), node->info.get_comment().c_str());
            }
            node = node->next;
        }

        ImGui::EndChild();
    }

    ImGui::InputText("##novo_comentario", buffer_comentario, sizeof(buffer_comentario));
    ImGui::SameLine();
    if (ImGui::Button("Comentar")) {
        if (buffer_comentario[0] != '\0') {
            interaction_service.add_comment_to_content(*selected_content, buffer_comentario);
            buffer_comentario[0] = '\0';
        }
    }

    ImGui::Separator();
    if (ImGui::Button("Voltar para Home")) {
        actual_screen = Screen::USER_DASHBOARD;
    }

    ImGui::End();
}

    void Window::render_admin_dashboard() {

        ImGui::Begin("Painel Administrativo");
        ImGui::Text("Gerenciar Conteudos:");

        if (ImGui::Button("Adicionar Novo Conteudo")) {
            selected_content = nullptr;
            buffer_titulo_admin[0] = '\0';
            buffer_type_admin = 0;
            buffer_genre_admin = 0;
            buffer_year_admin = 2024;
            buffer_views_admin = 0;
            buffer_rating_admin = 0.0f;
            actual_screen = Screen::ADMIN_FORMULARY;
        }

        ImGui::Separator();

        Node<Content> * node = contents.get_head();
        while (node != nullptr) {

            Content * current = &node->info;
            node = node->next; // avanca antes, pois "Excluir" pode invalidar o node atual

            ImGui::Text("%s", current->get_title().c_str());
            ImGui::SameLine();

            std::string edit_label = "Editar##" + std::to_string(current->get_id());
            if (ImGui::Button(edit_label.c_str())) {
                selected_content = current;
                std::strncpy(buffer_titulo_admin, current->get_title().c_str(), sizeof(buffer_titulo_admin) - 1);
                buffer_titulo_admin[sizeof(buffer_titulo_admin) - 1] = '\0';
                buffer_type_admin = static_cast<int>(current->get_type());
                buffer_genre_admin = static_cast<int>(current->get_genre());
                buffer_year_admin = current->get_year();
                buffer_views_admin = static_cast<int>(current->get_views());
                buffer_rating_admin = current->get_rating();
                actual_screen = Screen::ADMIN_FORMULARY;
            }

            ImGui::SameLine();

            std::string delete_label = "Excluir##" + std::to_string(current->get_id());
            if (ImGui::Button(delete_label.c_str())) {
                if (selected_content == current) selected_content = nullptr;
                content_admin_service.remove_content(current->get_id());
            }
        }

        if (ImGui::Button("Sair do Painel")) {
            actual_screen = Screen::PROFILE_CHOOSE;
        }

        ImGui::End();
}

void Window::render_admin_formulary() {

    static const char * type_options[] = { "Filme", "Serie", "Documentario", "Anime", "Desenho" };
    static const char * genre_options[] = { "Acao", "Comedia", "Romance", "Terror", "Suspense", "Drama", "Ficcao Cientifica" };

    ImGui::Begin("Admin - Formulario");
    ImGui::Text(selected_content == nullptr ? "Cadastrar Novo Item" : "Editar Item");

    ImGui::InputText("Nome", buffer_titulo_admin, sizeof(buffer_titulo_admin));
    ImGui::Combo("Tipo", &buffer_type_admin, type_options, IM_ARRAYSIZE(type_options));
    ImGui::Combo("Genero", &buffer_genre_admin, genre_options, IM_ARRAYSIZE(genre_options));
    ImGui::InputInt("Ano", &buffer_year_admin);
    ImGui::InputInt("Views", &buffer_views_admin);
    ImGui::SliderFloat("Avaliacao inicial", &buffer_rating_admin, 0.0f, 5.0f, "%.1f");

    if (buffer_year_admin < 0) buffer_year_admin = 0;
    if (buffer_views_admin < 0) buffer_views_admin = 0;

    if (ImGui::Button("Salvar")) {

        if (buffer_titulo_admin[0] != '\0') {

            Type type = static_cast<Type>(buffer_type_admin);
            Genre genre = static_cast<Genre>(buffer_genre_admin);

                if (selected_content == nullptr) {
                    content_admin_service.add_content(buffer_titulo_admin, type, genre,
                        buffer_year_admin, buffer_views_admin, buffer_rating_admin);
                } else {
                    content_admin_service.edit_content(selected_content->get_id(), buffer_titulo_admin, type, genre,
                        buffer_year_admin, buffer_views_admin, buffer_rating_admin);
                }

                selected_content = nullptr;
                actual_screen = Screen::ADMIN_DASHBOARD;
            }
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