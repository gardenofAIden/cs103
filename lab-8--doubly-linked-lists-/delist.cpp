#include <iostream>
#include "delist.h"

using namespace std;

// Constructs an empty Double-Ended List
DEList::DEList()
{
  head = NULL;
  tail = NULL;
  _size = 0;
}

DEList::~DEList()
{
  while(!empty())
  {
    pop_front();
  }
}

// returns a Boolean 'true' if the list is empty
bool DEList::empty()
{
  if(_size == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// returns number of items in the list
int DEList::size()
{
  return _size;
}

// returns front item or -1 if empty list
int DEList::front()
{
  if (empty())
  	return -1;
  else
  	return head -> val;
}

// returns back item or -1 if empty list
int DEList::back()
{
  if (empty())
  	return -1;
  else
  	return tail -> val;
}

// Adds a new integer to the front of the list
void DEList::push_front(int new_val)
{
  DEItem* item = new DEItem;
  if(empty())
  {
  	tail = item;
  }
  else
  {
    item -> next = head;
    head -> prev = item;
  }
  item -> val = new_val;
  item -> prev = NULL;
  head = item;
  _size++;
}

// Adds a new integer to the back of the list
void DEList::push_back(int new_val)
{
  DEItem* end_item = new DEItem;
  if (empty())
  {
    head = end_item;
  }
  else
  {
    end_item -> prev = tail;
    tail -> next = end_item;
  }
  end_item -> val = new_val;
  end_item -> next = NULL;
  tail = end_item;
  _size++;
}

// Removes the front item of the list (if it exists)
void DEList::pop_front()
{
  if(_size == 1)
  {
    delete head;
    _size--;
    head = NULL;
    tail = NULL;
  }
else if (_size > 1)
{
  head = head -> next;
  delete head -> prev;
  head -> prev = NULL;
  _size--;
}
}

// Removes the back item of the list (if it exists)
void DEList::pop_back()
{
  if(_size == 1)
  {
    delete head;
    _size--;
    head = NULL;
    tail = NULL;
  }
  else if (_size > 1)
  {
    tail = tail -> prev;
    delete tail -> next;
    tail -> next =NULL;
    _size--;
  }
}