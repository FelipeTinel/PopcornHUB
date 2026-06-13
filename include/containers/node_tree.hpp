#pragma once

#include <iostream>

#include "core/content.hpp"

struct NodeTree {

    Content content;
    NodeTree * left, * right;

};