#include <iostream>

#include "node.hpp"
#include "content.hpp"

class DoublyLinkedList {

    Node * head, * tail, * current;

    public:

        DoublyLinkedList(): head(nullptr) {}
        DoublyLinkedList(Node * head): head(head) {}
    
        ~ DoublyLinkedList ();
    
        void insert (const Content &content);
        Content pop (const Content &content);
        
        void go_next ();
        void go_previous ();
        
        Content get_current () const;
        Content remove_current ();

};