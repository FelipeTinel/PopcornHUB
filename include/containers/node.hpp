#pragma once

#include <iostream>

#include "core/content.hpp"

struct Node {

    Content content;
    Node * next, * previous;

    Node(const Content &_content): content(_content), next(nullptr), previous(nullptr) {}
};

