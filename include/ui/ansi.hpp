#pragma once

#include <iostream>
#include <string>

// Helpers simples de formatacao para terminal usando codigos ANSI puros.
// Funciona em qualquer terminal moderno (Linux, macOS, Windows Terminal, VS Code)
// sem precisar instalar nenhuma biblioteca externa.
namespace Ansi {

    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string DIM     = "\033[2m";

    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN    = "\033[36m";
    const std::string WHITE   = "\033[37m";

    // Limpa a tela e volta o cursor para o topo.
    inline void clear_screen() {
        std::cout << "\033[2J\033[1;1H";
    }

    // Titulo em destaque, dentro de uma caixa simples desenhada com "=".
    inline void print_title(const std::string & text) {
        std::string border(text.size() + 4, '=');
        std::cout << "\n" << CYAN << BOLD << border << "\n"
                   << "= " << text << " =\n"
                   << border << RESET << "\n";
    }

    inline void print_success(const std::string & text) {
        std::cout << GREEN << text << RESET << "\n";
    }

    inline void print_error(const std::string & text) {
        std::cout << RED << text << RESET << "\n";
    }

    inline void print_info(const std::string & text) {
        std::cout << DIM << text << RESET << "\n";
    }

    // Uma linha de menu tipo "1 - Fazer algo", com o numero destacado.
    inline void print_menu_option(const std::string & key, const std::string & label) {
        std::cout << YELLOW << BOLD << key << RESET << " - " << label << "\n";
    }

}
