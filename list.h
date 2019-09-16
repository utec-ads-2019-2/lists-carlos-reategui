#ifndef LIST_H
#define LIST_H

#include "node.h"

template <typename T>
class List {
    protected:
        Node<T>* head;
        Node<T>* tail;
        int nodes;

    public:
        List() : head(nullptr), tail(nullptr), nodes(0) {};

        T front() {
            if(this->empty()) throw out_of_range("List is empty (front)");
            return this->head->data;
        };
        virtual T back() = 0;
        virtual void push_front(T) = 0;
        virtual void push_back(T) = 0;
        virtual void pop_front() = 0;
        virtual void pop_back() = 0;
        virtual T operator[](int) = 0;
        bool empty() {
            return this->nodes == 0;
        }
        int size() {
            return this->nodes;
        }
        void clear() {
            // Esto no va funcionar para la lista circular
            this->head->killSelf();
            this->head = nullptr;
            this->tail = nullptr;
            this->nodes = 0;
        }
        void sort() {
            if (this->head != nullptr) {
                T copyOfList[this->nodes];
                auto currentNode = this->head;
                for (unsigned int i = 0; i < this->nodes; i++) {
                    copyOfList[i] = currentNode->data;
                    currentNode = currentNode->next;
                }
                for (unsigned int i = 0; i < this->size(); i++) {
                    unsigned minIndex = i;
                    for (unsigned int j = i + 1; j < this->size(); j++)
                        if (copyOfList[minIndex] > copyOfList[j]) minIndex = j;
                    std::swap(copyOfList[minIndex], copyOfList[i]);
                }
                currentNode = this->head;
                for (unsigned int i = 0; i < this->size(); i++) {
                    currentNode->data = copyOfList[i];
                    currentNode = currentNode->next;
                }
            }
        }
        virtual void reverse() = 0;
        virtual string name() = 0;
        void print(){
            std::cout << "Elements: ";
            for (unsigned int i = 0; i < this->nodes; i++) std::cout << this->operator[](i) << " ";
            std::cout << std::endl << "Size: " << this->size() << std::endl;
            std::cout << "Front: " << this->front() << std::endl;
            std::cout << "Back: " << this->back() << std::endl;
        }
        ~List() {
            auto current = this->head;
            for (unsigned int i = 0; i < this->nodes; i++) {
                auto temp = current;
                if (temp != nullptr) {
                    delete temp;
                    current = current->next;
                }
            }
        }
};

#endif