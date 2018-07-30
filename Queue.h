// Programmer: Sadeem Khan
// Programmer's ID: 1549921

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

template <typename V>
class Queue
{
  struct Node
  {
    V value;
    Node* next;
  };

  Node* firstNode;
  int siz = 0;
  Node* lastNode;

  public:
  Queue(); // may have a defaulted parameter
  void push(const V&);
  V& front() ; // return a mutable reference to the oldest node
  V& back(); // return a mutable reference to the newest node
  void pop(); // remove the oldest
  int size() const {return siz;}
  bool empty() const {return siz==0;}
  void clear();
  ~Queue(){clear();}
  Queue<V>& operator=(const Queue<V>&);
  Queue(const Queue<V>&); 
};

template <typename V>
Queue<V>::Queue()
{
  lastNode = 0;
  siz = 0;
}

template <typename V>
void Queue<V>::push(const V& value)
{
  Node* temp = new Node;
  temp->value = value;
  temp->next = 0;
  if (lastNode) lastNode->next = temp;
  else firstNode = temp;
  lastNode = temp;
  ++siz;
}

template <typename V>
V& Queue<V>::front()
{
  return firstNode->value;
}

template <typename V>
V& Queue<V>::back()
{
  return lastNode->value;
}

template <typename V>
void Queue<V>::pop()
{
  if (firstNode)
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
    --siz;
  }
  if(siz == 0)
  {
    lastNode = 0; // before Queue::pop ends, it needs to check if the siz is now zero, because if it is, the tail pointer needs to be zeroed out.
  }
}

template <typename V>
void Queue<V>::clear()
{
  while (firstNode)
  {
    Node* p = firstNode;
    firstNode = firstNode->next;
    delete p;
    --siz;
  }
  lastNode = 0; // The tail pointer needs to be zeroed out in Queue::clear
}

template <typename V>
Queue<V>::Queue(const Queue<V>& original)
{
  firstNode = 0;
  lastNode = 0;
  siz = original.siz;
  for (Node* p = original.firstNode; p; p = p->next)
  {
    Node* temp = new Node;
    temp->value = p->value;
    temp->next = 0;
    if (lastNode) lastNode->next = temp;
    else firstNode = temp;
    lastNode = temp;
  }
}

template <typename V>
Queue<V>& Queue<V>::operator=(const Queue<V>& original)
{
  if (this != &original)
  {
    // deallocate existing list
    while (firstNode)
    {
      Node* p = firstNode->next;
      delete firstNode;
      firstNode = p;
    }

    // build new queue
    lastNode = 0; // temporary tail
    for (Node* p = original.firstNode; p; p = p->next)
    {
      Node* temp = new Node;
      temp->value = p->value;
      temp->next = 0;
      if (lastNode) lastNode->next = temp;
      else firstNode = temp;
      lastNode = temp;
    }
    siz = original.siz;
  }
  return *this;
}
#endif //QUEUE_QUEUE_H