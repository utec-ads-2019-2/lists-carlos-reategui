#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"

template <typename T>
class CircularLinkedList : public List<T> {
    public:
        CircularLinkedList() : List<T>() {}

        T back() {
            if (this->empty())
                throw out_of_range("List is empty (back cll)");
            return this->head->prev->data;
        }

        void push_front(T value) {
            push_back(value);
            this->head=this->head->prev;
        }

        void push_back(T value) {
            auto newNode = new Node<T>();
            newNode->data = value;
            newNode->next = this->head;
            if (this->empty()) {
                this->head = newNode;
                this->head->next = newNode;
                this->head->prev = newNode;
            } else {
                this->head->prev->next = newNode;
                newNode->prev = this->head->prev;
                this->head->prev = newNode;
            }
            this->nodes++;
        }

        void pop_front() {
            if (this->head != nullptr) {
                auto tempHead = this->head;
                this->nodes--;
                if (this->nodes == 0) this->head = nullptr;
                else {
                    this->head->prev->next = this->head->next;
                    this->head->next->prev = this->head->prev;
                    this->head = this->head->next;
                }
                delete tempHead;
            }
        }

        void pop_back() {
            if (this->head != nullptr) {
                auto tempHeadPrev = this->head->prev;
                this->nodes--;
                if (this->nodes == 0) this->head = nullptr;
                else {
                    this->head->prev->prev->next = this->head;
                    this->head->prev = this->head->prev->prev;
                }
                delete tempHeadPrev;
            }
        }

        T operator[](int index) {
            if (index < this->size() and this->head != nullptr) {
                auto temp = this->head; int count = 0;
                if (this->size() / 2 >= index) {
                    while (count != index) {
                        temp = temp->next;
                        count++;
                    }
                }
                else {
                    while (index + count < this->size()) {
                        temp = temp->prev;
                        count++;
                    }
                }
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
            return "Circular Linked List";
        }

        BidirectionalIterator<T> begin() {
            return BidirectionalIterator<T>(this->head);
        }

	    BidirectionalIterator<T> end() {
            return BidirectionalIterator<T>(this->head);
        }

        void merge(CircularLinkedList<T> list) {
            for (unsigned int i = 0; i < list.size(); i++) this->push_back(list[i]);
        }
};

#endif