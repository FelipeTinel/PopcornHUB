# PopcornHUB

Sistema de recomendação de conteúdo para streaming, feito em C++ para a disciplina de Estrutura de Dados I (UNEB, 2026.1).

## Funcionalidades

- Cadastro, edição e remoção de conteúdos (Admin)
- Login/cadastro de usuário
- Questionário de recomendação baseado em uma **árvore binária de decisão** (gênero → subgênero)
- Lista de recomendados ordenada por avaliação, respeitando a prioridade de subgênero
- Comentários e avaliação por estrelas
- Histórico de mais assistidos (lista duplamente encadeada)
- Estatísticas do sistema (tipo/gênero mais e menos recomendado, títulos mais assistidos, etc.)
- Persistência em arquivos de texto (`data/`)

## Estruturas de dados utilizadas

- **Árvore binária** (`BinaryTree` / `NodeTree`) — navegação do questionário de recomendação
- **Lista duplamente encadeada** (`DoublyLinkedList<T>`) — armazena conteúdos, usuários, comentários, gêneros e histórico

## Como rodar

Requer `g++` (C++17) e `make`.

```bash
make        # compila, gera build/ecv_terminal
make run    # compila (se necessário) e já executa
```

No Windows, usar o terminal MSYS2 (UCRT64/MinGW64) ou qualquer terminal com `g++`/`make` no PATH.

## Os melhores programadores:

Marcelo Líryo, Janderson Blanski e Felipe Tinel.
