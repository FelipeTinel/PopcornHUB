#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

#include "core/score_calculator.hpp"
#include "containers/binary_tree.hpp"
#include "containers/node.hpp"
#include "containers/node_tree.hpp"

ScoreCalculator::ScoreCalculator() {
    questions_tree = new BinaryTree();
}

ScoreCalculator::~ScoreCalculator() {
    delete questions_tree;
}

BinaryTree* ScoreCalculator::get_questions_tree() const {
    return questions_tree;
}

void ScoreCalculator::build_default_tree() {
    std::vector<std::string> questions = {
        "Do you like action?",
        "Do you like romance?",
        "Do you like horror?",
        "Do you like comedy?",
        "Do you like slice-of-life stories?"
    };

    // Construct a perfect binary tree recursively where each level represents the same question
    auto build_level = [&](auto& self, int depth) -> NodeTree* {
        if (depth >= static_cast<int>(questions.size())) {
            return nullptr;
        }
        NodeTree* node = new NodeTree();
        node->question = questions[depth];
        node->left = self(self, depth + 1);
        node->right = self(self, depth + 1);
        return node;
    };

    // Clean up old root dynamically if it exists since questions_tree destructor does it
    NodeTree* old_root = questions_tree->get_root();
    if (old_root != nullptr) {
        questions_tree->set_root(nullptr);
        // Let BinaryTree destructor or manual recursive destroy handle old nodes if necessary,
        // but here we just delete the old tree structure.
        delete old_root; // BinaryTree destructor handles root, but since we overwrite it:
    }

    NodeTree* root = build_level(build_level, 0);
    questions_tree->set_root(root);
}

bool ScoreCalculator::is_genre_question(const std::string& question, Genre& out_genre) const {
    std::string lower = question;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c){ return std::tolower(c); });

    if (lower.find("action") != std::string::npos) {
        out_genre = Genre::ACTION;
        return true;
    } else if (lower.find("romance") != std::string::npos) {
        out_genre = Genre::ROMANCE;
        return true;
    } else if (lower.find("horror") != std::string::npos) {
        out_genre = Genre::HORROR;
        return true;
    } else if (lower.find("comedy") != std::string::npos) {
        out_genre = Genre::COMEDY;
        return true;
    } else if (lower.find("slice-of-life") != std::string::npos) {
        out_genre = Genre::SLICE_OF_LIFE;
        return true;
    }
    return false;
}

void ScoreCalculator::calculate_score(Content* content, const std::vector<Genre>& liked_genres) {
    if (content == nullptr) return;

    double score = 0.0;

    // 1. Movie/Series: 10 points for the selected item
    bool is_movie_or_series = (content->get_type() == Type::MOVIE || content->get_type() == Type::SERIES);
    if (is_movie_or_series) {
        score += 10.0;
    }

    // 2. Popular/Highly Rated: (views/10) + (rating) -> if Movie/Series, multiplied by 1.5 before the sum
    double popularity = (content->get_views() / 10.0) + content->get_rating();
    if (is_movie_or_series) {
        popularity *= 1.5;
    }
    score += popularity;

    // 3. New Release/Classic: Classic -> multiply by the difference from 2026; New Release -> divide by the difference from 2026
    // Classic threshold: year <= 2015 (11+ years old in 2026)
    // New Release threshold: year > 2015
    int diff = 2026 - content->get_year();
    if (diff <= 0) {
        diff = 1; // Guard against negative/zero division/multiplication
    }

    if (content->get_year() <= 2015) {
        score *= diff;
    } else {
        score /= static_cast<double>(diff);
    }

    // 4. Genres: +10 per matching genre (matches any of the liked genres)
    for (Genre g : liked_genres) {
        if (content->get_genre() == g) {
            score += 10.0;
        }
    }

    content->set_score(score);
}

Node* ScoreCalculator::recommend(const std::vector<Content*>& catalog) {
    std::vector<Genre> liked_genres;
    NodeTree* current = (questions_tree != nullptr) ? questions_tree->get_root() : nullptr;

    while (current != nullptr) {
        std::cout << current->question << " (y/n): ";
        std::string ans;
        if (!(std::cin >> ans)) {
            break;
        }

        if (ans == "y" || ans == "Y" || ans == "yes" || ans == "Yes" || ans == "sim" || ans == "Sim") {
            Genre g;
            if (is_genre_question(current->question, g)) {
                liked_genres.push_back(g);
            }
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Recalculate scores for all contents in the catalog
    for (Content* c : catalog) {
        calculate_score(c, liked_genres);
    }

    // Build sorted singly linked list of Node* (descending score order)
    Node* head = nullptr;

    for (Content* c : catalog) {
        Node* newNode = new Node();
        newNode->content = c;
        newNode->next = nullptr;

        if (head == nullptr || c->get_score() > head->content->get_score()) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* prev = head;
            while (prev->next != nullptr && prev->next->content->get_score() >= c->get_score()) {
                prev = prev->next;
            }
            newNode->next = prev->next;
            prev->next = newNode;
        }
    }

    return head;
}

void ScoreCalculator::free_list(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        Node* next_node = current->next;
        delete current;
        current = next_node;
    }
}
