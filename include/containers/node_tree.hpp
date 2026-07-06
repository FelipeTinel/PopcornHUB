#pragma once

#include <iostream>

#include <string>

#include "core/content.hpp"

struct NodeTree {

    Content* content;
    std::string question;
    NodeTree * left, * right;

    NodeTree() : content(nullptr), question(""), left(nullptr), right(nullptr) {}

};