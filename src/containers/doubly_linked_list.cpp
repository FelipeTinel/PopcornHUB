#include <iostream>

#include "containers/doubly_linked_list.hpp"
#include "containers/node.hpp"

void DoublyLinkedList::insert(const Content &content) {

    Node * new_node = new Node(content);
    if (head == nullptr) tail = new_node;
    else head->previous = new_node;
    new_node->next = head;
    head = new_node;
    current = head;

}

Content DoublyLinkedList::pop (const Content &content) {

    Node * temp = tail;

    while (temp != nullptr) {

        if (content.get_id() == temp->content.get_id()) {

            if (temp->previous != nullptr) temp->previous->next = temp->next;
            else head = temp->next;

            if (temp->next != nullptr) temp->next->previous = temp->previous;
            else tail = temp->previous;

            Content save_content = temp->content;
            
            if (current == temp) current = head;

            delete temp;
            return save_content;

        }

        temp = temp->previous;

    }

    return content;

}

void DoublyLinkedList::go_next () {

    if (current == nullptr) return;

    if (current->next == nullptr) current = head;
    else current = current->next;

}

void DoublyLinkedList::go_previous() {

    if (current == nullptr) return;

    if (current->previous == nullptr) current = tail;
    else current = current->previous;

}

Content DoublyLinkedList::get_current() const {

    if (current != nullptr) return current->content;
    return Content();

}

Content DoublyLinkedList::remove_current() {

    if (current == nullptr) return Content();

    if (current->previous != nullptr) current->previous->next = current->next;
    if (current->next != nullptr) current->next->previous = current->previous;

    Node * temp = current;
    current = current->next;
    delete temp;

}

