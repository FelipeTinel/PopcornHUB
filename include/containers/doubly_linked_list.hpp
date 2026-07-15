#pragma once

#include <iostream>

#include "node.hpp"

template <typename T>
class DoublyLinkedList {

    Node<T> * head, * tail;

    public:

        DoublyLinkedList(): head(nullptr), tail(nullptr) {}
        DoublyLinkedList(Node<T> * head): head(head) {}
    
        ~ DoublyLinkedList ();
    
        void insert (const T &info);
        void insert_sorted (const T &info, bool (*comes_before)(const T&, const T&));

        T pop (int id);
        T * search (int id) const;

        Node<T> * get_head() const { return head; }
        Node<T> * get_tail() const { return tail; }


};


template <typename T>
void DoublyLinkedList<T>::insert(const T &info) {

    Node<T> * new_node = new Node<T>(info);
    
    new_node->previous = nullptr;

    if (head == nullptr) tail = new_node;
    else head->previous = new_node;

    new_node->next = head;

    head = new_node;

}

template <typename T>
void DoublyLinkedList<T>::insert_sorted(const T &info, bool (*comes_before)(const T&, const T&)) {

    Node<T> * new_node = new Node<T>(info);

    if (head == nullptr) { // SE A LISTA ESTIVER VAZIA
        new_node->previous = nullptr;
        new_node->next = nullptr;
        head = tail = new_node;
        return;
    }

    Node<T> * current = head;
    while (current != nullptr && comes_before(current->info, info)) {
        current = current->next;
    }

    if (current == nullptr) {
        //vai pro final da lista
        new_node->previous = tail;
        new_node->next = nullptr;
        tail->next = new_node;
        tail = new_node;
    } else if (current == head) {
        //vai pro início da lista
        new_node->next = head;
        new_node->previous = nullptr;
        head->previous = new_node;
        head = new_node;
    } else {
        //vai no meio
        Node<T> * prev = current->previous;
        new_node->previous = prev;
        new_node->next = current;
        prev->next = new_node;
        current->previous = new_node;
    }
}

template <typename T>
T DoublyLinkedList<T>::pop (int id) {

    Node<T> * temp = tail;

    while (temp != nullptr) {

        if (temp->info.get_id() == id) {

            if (temp->previous != nullptr) temp->previous->next = temp->next;
            else head = temp->next;

            if (temp->next != nullptr) temp->next->previous = temp->previous;
            else tail = temp->previous;

            T save_content = temp->info;
            delete temp;
            return save_content;
        
        }

        temp = temp->previous;

    }

    return T();

}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {

    Node<T>* actual = head;
    Node<T>* ahead = nullptr;

    while (actual != nullptr) {

        ahead = actual->next;
        
        delete actual;

        actual = ahead;
    }

    head = nullptr;
    tail = nullptr;
}

template <typename T>
T * DoublyLinkedList<T>::search(int id) const{
    
    Node<T>* node = head;
    
    while (node != nullptr) {
        if (node->info.get_id() == id) return &node->info;
        node = node->next;
    }
    
    return nullptr;
}