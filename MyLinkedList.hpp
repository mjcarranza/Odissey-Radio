//
// Created by alejandrojqc on 16/10/20.
//
#pragma once
template<typename T>
struct Node {
    Node<T> *nextPtr;
    T data;
};

template<typename T>
class MyLinkedList{
private:
    int len{};
    Node<T> * head;
    Node<T> * tail;
public:
    MyLinkedList();
    void add(T data);
    T get(int index);
    Node<T> * getHead();
    Node<T> * getTail();
    int getLen();
};

template<typename T>
MyLinkedList<T>::MyLinkedList() {
    this->len = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

template<typename T>
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

template<typename T>
Node<T> * MyLinkedList<T>::getHead() {
    return this->head;
}

template<typename T>
Node<T> * MyLinkedList<T>::getTail() {
    return this->tail;
}

template<typename T>
int MyLinkedList<T>::getLen() {
    return this->len;
}
