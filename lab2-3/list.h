#ifndef LIST_H
#define LIST_H
#include "item.h"
#include <stdexcept>
#include <iostream>

template <class T>  class List
{
private:
    Item<T>* _items;
public:
    List();
    ~List();

    void addToTail(const T& val);
    void addToHead(const T&  val);

    void deleteFromHead();
    void deleteFromTail();

    T head() const;
    T tail() const;

    // Linker gave an error for the implementation of an operator outside the class
    friend std::ostream& operator<<(std::ostream& out, const List<T>& object)
    {
        if (object._items == nullptr)
        {
            out << "No elements\n";
            return out;
        }
        Item<T>* tmp = object._items;

        int cnt = 1;
        do
        {
            out << cnt << ") " << tmp->data;
            
            tmp = tmp->next;
            cnt++;
        } while (tmp != object._items);
        
        return out;
    }
};

template <typename T>
List<T>::List(): _items(nullptr) {}

template <typename T>
List<T>::~List() 
{
    while (_items != nullptr)
    {
        this->deleteFromHead();
    }
} 

template <typename T>
void List<T>::addToTail(const T&  val)
{
    Item<T>* tmp = new Item<T>(val);
    if (_items == nullptr)
    {
        _items = tmp;
        return;
    }

    tmp->prev = _items->prev;
    tmp->next = _items;

    _items->prev->next = tmp;
    _items->prev = tmp;
    
    return;
}

template <typename T>
void List<T>::addToHead(const T&  val)
{
    Item<T>* tmp = new Item<T>(val);
    if (_items == nullptr)
    {
        _items = tmp;
        return;
    }
    
    tmp->prev = _items->prev;
    tmp->next = _items;
    
    _items->prev->next = tmp;
    _items->prev = tmp;

    _items = _items->prev;
}

template <typename T>
void List<T>::deleteFromHead()
{
    if (_items == nullptr)
        throw std::logic_error("Container has no elements");
    
    if (_items->next == _items)
    {
        delete _items;
        _items = nullptr;
        return;
    }
    
    Item<T>* tmp = _items->next;

    _items->prev->next = _items->next;
    _items->next->prev = _items->prev;

    delete _items;

    _items = tmp;
}

template <typename T>
void List<T>::deleteFromTail()
{
    if (_items == nullptr)
        throw std::logic_error("Container has no elements");

    
    if (_items->next == _items)
    {
        delete _items;
        _items = nullptr;
        return;
    }
    
    _items = _items->prev;
    this->deleteFromHead();
}

template <typename T>
T List<T>::head() const
{
    if (_items != nullptr)
    {
        return _items->data;
    }
    else
    {
        throw std::logic_error("Container has no elements");
    }
}

template <typename T>
T List<T>::tail() const
{
    if (_items != nullptr)
    {
        return _items->prev->data;
    }
    else
    {
        throw std::logic_error("Container has no elements");
    }
}

#endif /* LIST_H */