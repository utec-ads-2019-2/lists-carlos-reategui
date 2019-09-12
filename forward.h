#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include "iterators/forward_iterator.h"

template <typename T>
class ForwardList : public List<T> {
    public:
        ForwardList() : List<T>() {}

        T back() {
            if (this->empty()) throw out_of_range("List is empty (forward)");
            return this->tail->data;

        }

        void push_front(T value) {
            auto newNode = new Node<T>();
            newNode->data = value;
            newNode->next = this->head;
            if (this->head == nullptr) this->tail = newNode;
            this->head = newNode;
            this->nodes++;
        }

        void push_back(T value) {
            auto newNode = new Node<T>();
            newNode->data = value;
            if (this->head == nullptr) {
                this->head = newNode;
                this->tail = newNode;
            } else {
                this->tail->next = newNode;
                this->tail = newNode;
            }
            this->tail->next = nullptr;
            this->nodes++;
        }

        void pop_front() {
            if(this->head != nullptr){
                auto tempHead = this->head;
                this->head = this->head->next;
                delete tempHead;
                this->nodes--;
                if (this->nodes == 0) this->tail = nullptr;
            }
        }

        void pop_back() {
            if (this->nodes != 0) {
                auto secondLastNode = this->head;
                auto tempTail = this->tail;
                while (secondLastNode->next->next != nullptr) secondLastNode = secondLastNode->next;
                this->tail = secondLastNode;
                this->tail->next = nullptr;
                delete tempTail;
                this->nodes--;
                if (this->nodes == 0) {
                    this->head = nullptr;
                    this->tail = nullptr;
                }
            }
        }

        T operator[](int index) {
            if (index < this->size() and this->head != nullptr) {
                auto temp = this->head;
                for (unsigned int i = 0; i < index; i++) temp = temp->next;
                return temp->data;
            }
            throw out_of_range("Index out of range (operator)");
        }

        void reverse() {
            if (this->nodes > 1) {
                auto currentNode = this->head; Node<T> *ptrToNext = nullptr, *ptrToPrev = nullptr;
                while (currentNode != nullptr) {
                    ptrToNext = currentNode->next;
                    currentNode->next = ptrToPrev;
                    ptrToPrev = currentNode;
                    currentNode = ptrToNext;
                }
                std::swap(this->head, this->tail);
            }
        }

        string name() {
            return "Forward List";
        }

        ForwardIterator<T> begin() {
            return ForwardIterator<T>(this->head);
        }

        ForwardIterator<T> end() {
            return ForwardIterator<T>(this->tail->next);
        }

        void merge(ForwardList<T> list) {
            for (unsigned int i = 0; i < list.size(); i++) this->push_back(list[i]);
        }
};

#endif