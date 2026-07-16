#include <cstdlib>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "ui/console.hpp"
#include "containers/node.hpp"

namespace {


    const DoublyLinkedList<std::string> * g_subgenre_priority = nullptr;

    int subgenre_rank(const std::string & subgenre) {

        const int NOT_FOUND = 1000000;

        if (g_subgenre_priority == nullptr || subgenre.empty()) return NOT_FOUND;

        Node<std::string> * node = g_subgenre_priority->get_head();
        int index = 0;
        while (node != nullptr) {
            if (node->info == subgenre) return index;
            node = node->next;
            index++;
        }

        return NOT_FOUND;
    }

    bool content_subgenre_then_rating_desc(const Content & a, const Content & b) {

        int rank_a = subgenre_rank(a.get_subgenre());
        int rank_b = subgenre_rank(b.get_subgenre());

        if (rank_a != rank_b) return rank_a < rank_b;

        return content_rating_desc(a, b);
    }

}

Console::Console(AuthService & auth, InteractionService & interaction, AdminService & content_admin,
                  DoublyLinkedList<Content> & contents, DoublyLinkedList<Comment> & comments,
                  DoublyLinkedList<Genre> & genres)
    : actual_screen(ConsoleScreen::PROFILE_CHOOSE),
      auth_service(auth), interaction_service(interaction), content_admin_service(content_admin),
      contents(contents), comments(comments), genres(genres),
      selected_content(nullptr),
      current_tree_node(nullptr),
      chosen_genre(static_cast<Genre::Value>(0)),
      user_page(0), admin_page(0)
{
    genre_tree.build_tree(genres);
}

const char * Console::genre_to_string(Genre::Value g) {
    switch (g) {
        case Genre::ACTION:           return "Acao";
        case Genre::COMEDY:           return "Comedia";
        case Genre::ROMANCE:          return "Romance";
        case Genre::HORROR:           return "Terror";
        case Genre::SUSPENSE:         return "Suspense";
        case Genre::DRAMA:            return "Drama";
        case Genre::SCIENCE_FICTION:  return "Ficcao Cientifica";
        case Genre::SLICE_OF_LIFE:    return "Slice of Life";
    }
    return "Desconhecido";
}

const char * Console::type_to_string(Type t) {
    switch (t) {
        case Type::MOVIE:       return "Filme";
        case Type::SERIES:      return "Serie";
        case Type::DOCUMENTARY: return "Documentario";
        case Type::ANIME:       return "Anime";
        case Type::CARTOON:     return "Desenho";
    }
    return "Desconhecido";
}

const char * Console::rating_color(float rating) {
    if (rating >= 4.0f) return Ansi::GREEN.c_str();
    if (rating >= 2.5f) return Ansi::YELLOW.c_str();
    return Ansi::RED.c_str();
}

int Console::read_int(const std::string & prompt) {

    int value;

    while (true) {

        if (!prompt.empty()) std::cout << Ansi::YELLOW << prompt << Ansi::RESET;

        std::cin >> value;

        if (std::cin.eof()) {
            std::cout << "\n";
            Ansi::print_info("Entrada finalizada.");
            std::exit(0);
        }

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Ansi::print_error("Entrada invalida, digite um numero inteiro.");
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

float Console::read_float(const std::string & prompt) {

    float value;

    while (true) {

        if (!prompt.empty()) std::cout << Ansi::YELLOW << prompt << Ansi::RESET;

        std::cin >> value;

        if (std::cin.eof()) {
            std::cout << "\n";
            Ansi::print_info("Entrada finalizada.");
            std::exit(0);
        }

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Ansi::print_error("Entrada invalida, digite um numero.");
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

std::string Console::read_line(const std::string & prompt) {

    std::string value;

    if (!prompt.empty()) std::cout << Ansi::YELLOW << prompt << Ansi::RESET;

    std::getline(std::cin, value);

    if (std::cin.eof() && value.empty()) {
        std::cout << "\n";
        Ansi::print_info("Entrada finalizada.");
        std::exit(0);
    }

    return value;
}

// Conta quantos conteudos existem percorrendo a lista encadeada do inicio ao fim.
int Console::count_contents() const {

    int total = 0;
    Node<Content> * node = contents.get_head();

    while (node != nullptr) {
        total++;
        node = node->next;
    }

    return total;
}

// Anda pela lista encadeada ate o primeiro item da pagina pedida.
Node<Content> * Console::get_page_start(int page) const {

    Node<Content> * node = contents.get_head();
    int to_skip = page * PAGE_SIZE;

    for (int i = 0; i < to_skip && node != nullptr; i++) {
        node = node->next;
    }

    return node;
}

// Imprime uma linha formatada com as informacoes de um conteudo.
void Console::print_content_line(const Content & content) {

    std::cout << "  " << Ansi::CYAN << "[" << content.get_id() << "]" << Ansi::RESET
               << " " << Ansi::BOLD << content.get_title() << Ansi::RESET
               << Ansi::DIM << " - " << type_to_string(content.get_type())
               << " | " << genre_to_string(content.get_genre());
    if (!content.get_subgenre().empty()) std::cout << " (" << content.get_subgenre() << ")";
    std::cout << " | " << content.get_year() << Ansi::RESET
               << " | nota " << rating_color(content.get_rating()) << content.get_rating() << Ansi::RESET
               << Ansi::DIM << " (" << content.get_rating_count() << " avaliacoes)"
               << " | " << content.get_views() << " views" << Ansi::RESET << "\n";
}

void Console::render_profile_choose() {

    Ansi::clear_screen();
    Ansi::print_title("PopcornHUB (Terminal)");

    Ansi::print_menu_option("1", "Entrar como Admin");
    Ansi::print_menu_option("2", "Entrar como Usuario");
    Ansi::print_menu_option("0", "Sair");

    int option = read_int("\nEscolha uma opcao: ");

    switch (option) {
        case 1: actual_screen = ConsoleScreen::ADMIN_DASHBOARD; break;
        case 2: actual_screen = ConsoleScreen::LOGIN; break;
        case 0: actual_screen = ConsoleScreen::EXIT; break;
        default: Ansi::print_error("Opcao invalida."); break;
    }
}

void Console::render_login() {

    Ansi::clear_screen();
    Ansi::print_title("Cadastro / Login");

    std::string username = read_line("Nome de usuario: ");
    std::string password = read_line("Senha: ");

    bool logged_in = auth_service.login_user(username, password);

    if (!logged_in) {
        bool created = auth_service.register_user(username, password);
        if (created) logged_in = auth_service.login_user(username, password);
    }

    if (logged_in) {
        Ansi::print_success("\nLogin realizado com sucesso!");
        actual_screen = ConsoleScreen::QUESTIONARY;
    } else {
        Ansi::print_error("\nSenha incorreta para esse usuario.");
        actual_screen = ConsoleScreen::PROFILE_CHOOSE;
    }
}

void Console::render_questionary() {

    if (genre_tree.get_root() == nullptr) {
        // nao ha generos cadastrados, pula direto pro catalogo
        actual_screen = ConsoleScreen::USER_DASHBOARD;
        return;
    }

    if (current_tree_node == nullptr) current_tree_node = genre_tree.get_root();

    if (current_tree_node->question == nullptr) {
        // chegamos numa folha: monta as recomendacoes e segue
        build_recommendations();
        current_tree_node = nullptr;
        actual_screen = ConsoleScreen::RECOMMENDATIONS;
        return;
    }

    Ansi::clear_screen();
    Ansi::print_title("Questionario de Recomendacao");
    std::cout << current_tree_node->question->get_question() << "\n";

    Ansi::print_menu_option("1", "Sim");
    Ansi::print_menu_option("2", "Nao");

    int option = read_int("\nEscolha: ");

    if (option == 1) {
        if (current_tree_node->question->is_genre()) {
            chosen_genre = current_tree_node->question->get_genre().get_value();
        }
        current_tree_node = genre_tree.navigate_yes(current_tree_node);
    } else if (option == 2) {
        current_tree_node = genre_tree.navigate_no(current_tree_node);
    } else {
        Ansi::print_error("Opcao invalida.");
    }
}

void Console::build_recommendations() {

    recommended = DoublyLinkedList<Content>(); // limpa recomendacoes anteriores

    g_subgenre_priority = (current_tree_node != nullptr) ? &current_tree_node->result_list : nullptr;

    Node<Content> * node = contents.get_head();
    while (node != nullptr) {
        if (chosen_genre != 0 && node->info.get_genre() == chosen_genre) {
            recommended.insert_sorted(node->info, content_subgenre_then_rating_desc);
        }
        node = node->next;
    }

    //fallback: se nada bateu com o genero escolhido, mostra tudo (ainda
    //respeitando a prioridade de subgenero, se houver) ordenado por avaliacao
    if (recommended.get_head() == nullptr) {
        node = contents.get_head();
        while (node != nullptr) {
            recommended.insert_sorted(node->info, content_subgenre_then_rating_desc);
            node = node->next;
        }
    }

    g_subgenre_priority = nullptr;

    // Estatisticas do Sistema: registra essa rodada de recomendacao (tipo,
    // genero e o contador de total de recomendacoes realizadas).
    statistics.register_recommendation(recommended);
}

void Console::render_recommendations() {

    Ansi::clear_screen();
    Ansi::print_title("Recomendados para voce");

    const int MAX_SHOWN = 10;

    Node<Content> * node = recommended.get_head();
    if (node == nullptr) Ansi::print_info("(nenhuma recomendacao encontrada)");

    int shown = 0;
    while (node != nullptr && shown < MAX_SHOWN) {
        print_content_line(node->info);
        node = node->next;
        shown++;
    }

    int total_matched = recommended.size();
    if (total_matched > shown) {
        std::cout << Ansi::DIM << "\n(mostrando os " << shown << " melhores de "
                   << total_matched << " encontrados)" << Ansi::RESET << "\n";
    }

    int choice = read_int("\nDigite o ID do conteudo para assistir, ou 0 para ir ao catalogo completo: ");

    if (choice == 0) {
        actual_screen = ConsoleScreen::USER_DASHBOARD;
        return;
    }

    Content * content = contents.search(choice);
    if (content == nullptr) {
        Ansi::print_error("Conteudo nao encontrado.");
        return;
    }

    selected_content = content;
    interaction_service.watch_content(*content);
    actual_screen = ConsoleScreen::CONTENT_DETAIL;
}

void Console::render_user_dashboard() {

    Ansi::clear_screen();
    Ansi::print_title("Home");

    int total = count_contents();
    int total_pages = (total == 0) ? 1 : (total + PAGE_SIZE - 1) / PAGE_SIZE;

    if (user_page >= total_pages) user_page = total_pages - 1;
    if (user_page < 0) user_page = 0;

    std::cout << Ansi::BOLD << "Catalogo" << Ansi::RESET
               << Ansi::DIM << " (pagina " << (user_page + 1) << " de " << total_pages
               << ", " << total << " titulos no total)" << Ansi::RESET << "\n\n";

    Node<Content> * node = get_page_start(user_page);

    if (node == nullptr) Ansi::print_info("  (nenhum conteudo cadastrado ainda)");

    int shown = 0;
    while (node != nullptr && shown < PAGE_SIZE) {
        print_content_line(node->info);
        node = node->next;
        shown++;
    }

    std::cout << "\n";
    if (user_page > 0)               Ansi::print_menu_option("a", "Pagina anterior");
    if (user_page < total_pages - 1) Ansi::print_menu_option("p", "Proxima pagina");
    Ansi::print_menu_option("0", "Logout");

    std::string input = read_line("\nDigite o ID de um titulo para assistir, ou uma das opcoes acima: ");

    if (input == "p" || input == "P") {
        if (user_page < total_pages - 1) user_page++;
        return;
    }

    if (input == "a" || input == "A") {
        if (user_page > 0) user_page--;
        return;
    }

    bool numeric = !input.empty();
    for (char c : input) {
        if (!std::isdigit(static_cast<unsigned char>(c))) { numeric = false; break; }
    }

    if (!numeric) {
        Ansi::print_error("Entrada invalida.");
        return;
    }

    int choice = std::stoi(input);

    if (choice == 0) {
        auth_service.logout();
        actual_screen = ConsoleScreen::PROFILE_CHOOSE;
        user_page = 0;
        return;
    }

    Content * content = contents.search(choice);

    if (content == nullptr) {
        Ansi::print_error("Conteudo nao encontrado.");
        return;
    }

    selected_content = content;
    interaction_service.watch_content(*content);
    actual_screen = ConsoleScreen::CONTENT_DETAIL;
}

void Console::render_content_detail() {

    if (selected_content == nullptr) {
        Ansi::print_error("Nenhum conteudo selecionado.");
        actual_screen = ConsoleScreen::USER_DASHBOARD;
        return;
    }

    Ansi::clear_screen();
    Ansi::print_title("Assistindo: " + selected_content->get_title());

    std::cout << Ansi::BOLD << "Genero: " << Ansi::RESET << genre_to_string(selected_content->get_genre())
               << Ansi::BOLD << "  |  Tipo: " << Ansi::RESET << type_to_string(selected_content->get_type()) << "\n";
    std::cout << Ansi::BOLD << "Ano: " << Ansi::RESET << selected_content->get_year() << "\n";
    std::cout << Ansi::BOLD << "Views: " << Ansi::RESET << selected_content->get_views() << "\n";
    std::cout << Ansi::BOLD << "Avaliacao media: " << Ansi::RESET << Ansi::YELLOW
               << selected_content->get_rating() << Ansi::RESET
               << " (" << selected_content->get_rating_count() << " avaliacoes)\n";

    std::cout << "\n" << Ansi::BOLD << Ansi::MAGENTA << "Comentarios:" << Ansi::RESET << "\n";

    Node<Comment> * node = comments.get_head();
    bool has_comment = false;

    while (node != nullptr) {
        if (node->info.get_content_id() == selected_content->get_id()) {
            has_comment = true;
            User * author = auth_service.find_by_id(node->info.get_user_id());
            std::string author_name = (author != nullptr) ? author->get_name() : "Usuario desconhecido";
            std::cout << "  - " << Ansi::CYAN << author_name << Ansi::RESET
                       << ": " << node->info.get_comment() << "\n";
        }
        node = node->next;
    }

    if (!has_comment) Ansi::print_info("  (nenhum comentario ainda)");

    bool already_rated = auth_service.is_logged_in() &&
        interaction_service.has_rated(auth_service.get_current_user()->get_id(), selected_content->get_id());

    std::cout << "\n";
    Ansi::print_menu_option("1", "Comentar");
    if (!already_rated) Ansi::print_menu_option("2", "Avaliar (0 a 5)");
    Ansi::print_menu_option("0", "Voltar para Home");

    int option = read_int("\nEscolha uma opcao: ");

    if (option == 1) {
        std::string text = read_line("Digite seu comentario: ");
        if (!text.empty()) interaction_service.add_comment_to_content(*selected_content, text);
    } else if (option == 2 && !already_rated) {
        float nota = read_float("Nota (0.0 a 5.0): ");
        bool ok = interaction_service.rate_content(*selected_content, nota);
        if (!ok) Ansi::print_error("Nao foi possivel registrar a avaliacao.");
    } else if (option == 0) {
        actual_screen = ConsoleScreen::USER_DASHBOARD;
    }
}

void Console::render_admin_dashboard() {

    Ansi::clear_screen();
    Ansi::print_title("Painel Administrativo");

    int total = count_contents();
    int total_pages = (total == 0) ? 1 : (total + PAGE_SIZE - 1) / PAGE_SIZE;

    if (admin_page >= total_pages) admin_page = total_pages - 1;
    if (admin_page < 0) admin_page = 0;

    std::cout << Ansi::DIM << "(pagina " << (admin_page + 1) << " de " << total_pages
               << ", " << total << " titulos no total)" << Ansi::RESET << "\n\n";

    Node<Content> * node = get_page_start(admin_page);

    if (node == nullptr) Ansi::print_info("  (nenhum conteudo cadastrado ainda)");

    int shown = 0;
    while (node != nullptr && shown < PAGE_SIZE) {
        print_content_line(node->info);
        node = node->next;
        shown++;
    }

    std::cout << "\n";
    Ansi::print_menu_option("1", "Adicionar novo conteudo");
    Ansi::print_menu_option("2", "Editar conteudo");
    Ansi::print_menu_option("3", "Remover conteudo");
    if (admin_page > 0)               Ansi::print_menu_option("4", "Pagina anterior");
    if (admin_page < total_pages - 1) Ansi::print_menu_option("5", "Proxima pagina");
    Ansi::print_menu_option("0", "Sair do painel");

    int option = read_int("\nEscolha uma opcao: ");

    if (option == 1) {
        selected_content = nullptr;
        render_admin_formulary(false);
    } else if (option == 2) {
        int id = read_int("Digite o ID do conteudo a editar: ");
        Content * target = contents.search(id);
        if (target == nullptr) {
            Ansi::print_error("Conteudo nao encontrado.");
            return;
        }
        selected_content = target;
        render_admin_formulary(true);
    } else if (option == 3) {
        int id = read_int("Digite o ID do conteudo a remover: ");
        if (selected_content != nullptr && selected_content->get_id() == id) selected_content = nullptr;
        bool removed = content_admin_service.remove_content(id);
        if (removed) Ansi::print_success("Conteudo removido.");
        else Ansi::print_error("Conteudo nao encontrado.");
    } else if (option == 4 && admin_page > 0) {
        admin_page--;
    } else if (option == 5 && admin_page < total_pages - 1) {
        admin_page++;
    } else if (option == 0) {
        actual_screen = ConsoleScreen::PROFILE_CHOOSE;
        admin_page = 0;
    }
}

void Console::render_admin_formulary(bool editing) {

    Ansi::clear_screen();
    Ansi::print_title(editing ? "Editar Item" : "Cadastrar Novo Item");

    std::string titulo = read_line("Nome: ");

    if (titulo.empty()) {
        Ansi::print_error("Nome nao pode ser vazio. Operacao cancelada.");
        return;
    }

    std::cout << Ansi::DIM << "Tipo: 0-Filme 1-Serie 2-Documentario 3-Anime 4-Desenho" << Ansi::RESET << "\n";
    int type_option = read_int("Escolha o tipo: ");
    while (type_option < 0 || type_option > 4) {
        type_option = read_int("Opcao invalida, escolha o tipo (0 a 4): ");
    }

    std::cout << Ansi::DIM << "Genero: 0-Acao 1-Comedia 2-Romance 3-Terror 4-Suspense 5-Drama 6-Ficcao Cientifica 7-Slice of Life" << Ansi::RESET << "\n";
    int genre_option = read_int("Escolha o genero: ");
    while (genre_option < 0 || genre_option > 7) {
        genre_option = read_int("Opcao invalida, escolha o genero (0 a 7): ");
    }

    int year = read_int("Ano: ");
    if (year < 0) year = 0;

    int views = read_int("Views iniciais: ");
    if (views < 0) views = 0;

    float rating = read_float("Avaliacao inicial (0.0 a 5.0): ");

    Type type = static_cast<Type>(type_option);
    Genre::Value genre = static_cast<Genre::Value>(genre_option + 1);


    std::string subgenre = "";

    Node<Genre> * genre_node = genres.get_head();
    while (genre_node != nullptr && genre_node->info.get_value() != genre) genre_node = genre_node->next;

    if (genre_node != nullptr) {

        std::vector<std::string> subgenre_options;
        DoublyLinkedList<std::string> subgenres = genre_node->info.get_subgenres();
        Node<std::string> * sub_node = subgenres.get_head();
        while (sub_node != nullptr) {
            subgenre_options.push_back(sub_node->info);
            sub_node = sub_node->next;
        }

        if (!subgenre_options.empty()) {

            std::cout << Ansi::DIM << "Subgenero (opcional):" << Ansi::RESET << "\n";
            std::cout << "  0 - (nenhum)\n";
            for (std::size_t i = 0; i < subgenre_options.size(); i++) {
                std::cout << "  " << (i + 1) << " - " << subgenre_options[i] << "\n";
            }

            int sub_option = read_int("Escolha o subgenero: ");
            if (sub_option >= 1 && static_cast<std::size_t>(sub_option) <= subgenre_options.size()) {
                subgenre = subgenre_options[sub_option - 1];
            }
        }
    }

    if (!editing) {
        content_admin_service.add_content(titulo, type, genre, year, views, rating, subgenre);
        Ansi::print_success("\nConteudo cadastrado com sucesso.");
    } else {
        bool ok = content_admin_service.edit_content(selected_content->get_id(), titulo, type, genre, year, views, rating, subgenre);
        if (ok) Ansi::print_success("\nConteudo atualizado com sucesso.");
        else Ansi::print_error("\nFalha ao atualizar conteudo.");
    }

    selected_content = nullptr;
}

void Console::render_watch_history() {

    Ansi::clear_screen();
    Ansi::print_title("Historico de Mais Assistidos");

    const DoublyLinkedList<WatchedEntry> & history = interaction_service.get_watch_history();
    Node<WatchedEntry> * node = history.get_head();

    if (node == nullptr) Ansi::print_info("  (nenhum conteudo assistido ainda)");

    int position = 1;
    while (node != nullptr) {
        print_watched_entry_line(node->info, position);
        node = node->next;
        position++;
    }

    Ansi::print_menu_option("0", "Voltar");
    read_int("\nDigite 0 para voltar: ");

    actual_screen = auth_service.is_logged_in() ? ConsoleScreen::USER_DASHBOARD : ConsoleScreen::ADMIN_DASHBOARD;
}

void Console::render_statistics() {

    Ansi::clear_screen();
    Ansi::print_title("Estatisticas do Sistema");

    if (statistics.get_total_recommendations() == 0) {

        Ansi::print_info("  Ainda nao foi gerada nenhuma recomendacao (responda o questionario pelo menos uma vez).");

    } else {

        std::cout << Ansi::BOLD << "Tipo mais recomendado: " << Ansi::RESET
                   << type_to_string(statistics.get_most_recommended_type()) << "\n";
        std::cout << Ansi::BOLD << "Tipo menos recomendado: " << Ansi::RESET
                   << type_to_string(statistics.get_least_recommended_type()) << "\n";
        std::cout << Ansi::BOLD << "Genero mais recomendado: " << Ansi::RESET
                   << genre_to_string(statistics.get_most_recommended_genre()) << "\n";
        std::cout << Ansi::BOLD << "Genero menos recomendado: " << Ansi::RESET
                   << genre_to_string(statistics.get_least_recommended_genre()) << "\n";
    }

    std::cout << Ansi::BOLD << "Quantidade total de recomendacoes realizadas: " << Ansi::RESET
               << statistics.get_total_recommendations() << "\n";
    std::cout << Ansi::BOLD << "Quantidade total de visualizacoes: " << Ansi::RESET
               << StatisticsService::get_total_views(contents) << "\n";

    std::cout << "\n" << Ansi::BOLD << Ansi::MAGENTA << "Titulo mais assistido por tipo:" << Ansi::RESET << "\n";
    for (int t = 0; t < TYPE_COUNT; t++) {
        Type type = static_cast<Type>(t);
        Content * best = StatisticsService::get_most_watched_by_type(contents, type);
        std::cout << "  " << type_to_string(type) << ": ";
        if (best == nullptr) std::cout << Ansi::DIM << "(nenhum cadastrado)" << Ansi::RESET << "\n";
        else std::cout << best->get_title() << Ansi::DIM << " (" << best->get_views() << " views)" << Ansi::RESET << "\n";
    }

    std::cout << "\n" << Ansi::BOLD << Ansi::MAGENTA << "Titulo mais assistido por genero:" << Ansi::RESET << "\n";
    for (int g = 1; g < GENRE_COUNT; g++) {
        Genre::Value genre = static_cast<Genre::Value>(g);
        Content * best = StatisticsService::get_most_watched_by_genre(contents, genre);
        std::cout << "  " << genre_to_string(genre) << ": ";
        if (best == nullptr) std::cout << Ansi::DIM << "(nenhum cadastrado)" << Ansi::RESET << "\n";
        else std::cout << best->get_title() << Ansi::DIM << " (" << best->get_views() << " views)" << Ansi::RESET << "\n";
    }

    std::cout << "\n" << Ansi::BOLD << Ansi::MAGENTA << "Titulos nunca assistidos:" << Ansi::RESET << "\n";
    Node<Content> * node = contents.get_head();
    bool any_never_watched = false;
    while (node != nullptr) {
        if (node->info.get_views() == 0) {
            any_never_watched = true;
            std::cout << "  - " << node->info.get_title() << "\n";
        }
        node = node->next;
    }
    if (!any_never_watched) Ansi::print_info("  (todos os titulos ja foram assistidos ao menos uma vez)");

    Ansi::print_menu_option("0", "Voltar");
    read_int("\nDigite 0 para voltar: ");

    actual_screen = auth_service.is_logged_in() ? ConsoleScreen::USER_DASHBOARD : ConsoleScreen::ADMIN_DASHBOARD;
}

void Console::run() {

    while (actual_screen != ConsoleScreen::EXIT) {

        switch (actual_screen) {

            case ConsoleScreen::PROFILE_CHOOSE:   render_profile_choose();   break;
            case ConsoleScreen::LOGIN:             render_login();            break;
            case ConsoleScreen::QUESTIONARY:       render_questionary();      break;
            case ConsoleScreen::RECOMMENDATIONS:   render_recommendations();  break;
            case ConsoleScreen::USER_DASHBOARD:   render_user_dashboard();   break;
            case ConsoleScreen::CONTENT_DETAIL:   render_content_detail();   break;
            case ConsoleScreen::ADMIN_DASHBOARD:  render_admin_dashboard();  break;
            case ConsoleScreen::EXIT: break;
        }
    }

    Ansi::print_success("\nAte mais!");
}