#pragma once

#include <vector>
#include <string>
#include "containers/binary_tree.hpp"
#include "containers/node.hpp"
#include "core/content.hpp"

class ScoreCalculator {

    private:

        BinaryTree* questions_tree;

        // Helper to check if a question is about a specific genre and maps it
        bool is_genre_question(const std::string& question, Genre& out_genre) const;

    public:

        ScoreCalculator();
        ~ScoreCalculator();

        // Gets the binary tree
        BinaryTree* get_questions_tree() const;

        // Builds the default questions binary tree
        void build_default_tree();

        // Calculates the score of a single content based on the liked genres
        void calculate_score(Content* content, const std::vector<Genre>& liked_genres);

        // Runs interactive user questions and returns a sorted singly linked list of recommendations
        Node* recommend(const std::vector<Content*>& catalog);

        // Utility to free the singly linked list
        static void free_list(Node* head);

};
