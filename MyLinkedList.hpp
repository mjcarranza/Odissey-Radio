//
// Created by alejandrojqc on 16/10/20.
//
#pragma once
template<typename T>
/**
 * @brief in-file declaration of a node structure to work as auxiliary data storage for the linked list structure.
 * @tparam T generic T-type template used for every value stored inside a node.
 * @author AleQuesada2012
 */
struct Node {
    Node<T> *nextPtr;
    T data;
};

template<typename T>
/**
 * @brief Class declaration for a custom LinkedList implementation.
 * @tparam T generic T-type template used for every value stored in the linked list.
 * @author AleQuesada2012
 */
class MyLinkedList{
private:
    int len{}; /**< an integer for the length of the structure */
    Node<T> * head; /**< Node type pointer that references the head of the list */
    Node<T> * tail; /**< Node type pointer that references the last element of the list */
public:
    MyLinkedList();
    ~MyLinkedList();
    void add(T data);
    T get(int index);
    Node<T> * getHead();
    Node<T> * getTail();
    int getLen();
};

template<typename T>
/**
 * @brief default constructor for MyLinkedList class
 * @tparam T generic T data type for the data structure
 */
MyLinkedList<T>::MyLinkedList() {
    this->len = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

template<typename T>
/**
 * @brief add method to append or insert data at the end of the list
 * @tparam T Generic data type for the linked list data structure
 * @param data value or object to be appended to the linked list instance
 * @author AleQuesada2012
 */
void MyLinkedList<T>::add(T data) {
    if (!head) {
        //the list is empty (no head)
        head = new Node<T>;
        head->data = data;
        head->nextPtr = nullptr;
        tail = head;
    }
    else {
        //the list is not empty
        if (tail == head) {
            tail = new Node<T>;
            tail->data = data;
            tail->nextPtr = nullptr;
            head->nextPtr = tail;
        }
        else {
            //list has more than one element
            Node<T> *toAdd = new Node<T>;
            toAdd->data = data;
            toAdd->nextPtr = nullptr;
            tail->nextPtr = toAdd;
            tail = toAdd;
        }
    }
    len++;
}

template<typename T>
/**
 * @brief get method, uses index to obtain the object in the specified position of the list
 * @tparam T generic data type for the data structure
 * @param index integer position of the desired value to obtain
 * @return generic type object contained in the specified position of the list starting from head
 * @author AleQuesada2012
 */
T MyLinkedList<T>::get(int index) {
    if (index == 0) {
        // get the first element
        return this->head->data;
    }
    else {
        // get the element in the index position
        Node<T> * current = this->head;
        for (int i = 0; i < index; ++i) {
            current = current->nextPtr;
        }
        return current->data;
    }
}
/**
 * @brief accessor method for the head attribute of the list instance
 * @tparam T generic type equivalent to the object type contained in each node of the list
 * @return the object contained in the first node of the referenced list instance
 * @author AleQuesada2012
 */
template<typename T>
Node<T> * MyLinkedList<T>::getHead() {
    return this->head;
}

/**
 * @brief accessor method for the tail attribute of the list instance.
 * @tparam T generic type equivalent to the object type contained in every node of the list
 * @return the object contained in the last node of the referenced list instance
 * @author AleQuesada2012
 */
template<typename T>
Node<T> * MyLinkedList<T>::getTail() {
    return this->tail;
}

/**
 * @brief accessor method for the length attribute of this list instance.
 * @tparam T generic type contained in every node of the list.
 * @return integer value corresponding to the amount of objects contained in this list instance.
 * @author AleQuesada2012
 */
template<typename T>
int MyLinkedList<T>::getLen() {
    return this->len;
}

/**
 * @brief custom Linkedlist destructor method
 * @tparam T generic template used in every declared method of this class
 * @author AleQuesada2012
 */
template<typename T>
MyLinkedList<T>::~MyLinkedList() {
    Node<T> * current = head;
    while (current != 0) {
        Node<T> *next = current->nextPtr;
        delete current;
        current = next;
    }
    head = 0;
}
