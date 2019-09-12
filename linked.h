#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

template <typename T>
class LinkedList : public List<T> {
    public:
        LinkedList() : List<T>() {}

        T back() {
            if (this->empty())
                throw out_of_range("List is empty (back)");
            return this->tail->data;
        }

        void push_front(T value) {
            auto newNode = new Node<T>();
            newNode->data = value;
            newNode->next = this->head;
            if (this->head == nullptr) this->tail = newNode;
            else this->head->prev = newNode;
            this->head = newNode;
            this->nodes++;
        }

        void push_back(T value) {
            auto newNode = new Node<T>();
            newNode->data = value;
            newNode->next = nullptr;
            if (this->head == nullptr) {
                this->head = newNode;
                this->tail = newNode;
            } else {
                this->tail->next = newNode;
                newNode->prev = this->tail;
                this->tail = newNode;
            }
            this->nodes++;
        }

        void pop_front() {
            if (this->head != nullptr) {
                auto tempHead = this->head;
                this->head = this->head->next;
                delete tempHead;
                this->nodes--;
                if (this->nodes == 0) {
                    this->head = nullptr;
                    this->tail = nullptr;
                }
                else this->head->prev = nullptr;
            }
        }

        void pop_back() {
            if (this->head != nullptr) {
                auto tempTail = this->tail;
                this->tail = this->tail->prev;
                delete tempTail;
                this->tail->next = nullptr;
                this->nodes--;
                if (this->nodes == 0) {
                    this->tail = nullptr;
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
                    currentNode->prev = ptrToNext;
                    ptrToPrev = currentNode;
                    currentNode = ptrToNext;
                }
                std::swap(this->head, this->tail);
            }
        }

        string name() {
            return "Linked List";
        }

        BidirectionalIterator<T> begin() {
            return BidirectionalIterator<T> (this->head);
        }

	    BidirectionalIterator<T> end() {
            return BidirectionalIterator<T> (this->head->next);
        }

        void merge(LinkedList<T> list) {
            for (unsigned int i = 0; i < list.size(); i++) this->push_back(list[i]);
        }
};

#endif