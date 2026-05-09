#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include "Nodo.h"

template <typename T>
class LinkedList {
private:
    Nodo<T>* head;
    int length;

public:
    LinkedList() {
        head = nullptr;
        length = 0;
    }

    ~LinkedList() {
        while (!isEmpty()) {
            Nodo<T>* temp = head;
            head = head->next;
            delete temp;
            length--;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int size() const {
        return length;
    }

    void append(T data) {
        Nodo<T>* newNode = new Nodo<T>(data);
        if (head == nullptr) {
            head = newNode;
        } else {
            Nodo<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        length++;
    }

    T getFirst() const {
        if (head == nullptr) {
            throw std::out_of_range("La lista esta vacia");
        }
        return head->data;
    }

    T get(int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Indice fuera de rango");
        }
        Nodo<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Asigna un valor a un índice específico
    void set(int index, T data) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Indice fuera de rango");
        }
        Nodo<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->data = data;
    }

    void display() const {
        Nodo<T>* current = head;
        if (current == nullptr) {
            std::cout << "La lista esta vacia.\n";
            return;
        }
        int index = 1;
        while (current != nullptr) {
            std::cout << index << ". " << current->data.getNombreCancion()
                      << " - " << current->data.getNombreArtista() << "\n";
            current = current->next;
            index++;
        }
    }
};

#endif+