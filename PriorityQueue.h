#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "HuffmanNode.h"

namespace nabiullin
{
  struct PriorityQueueNode
  {
    HuffmanNode* val_;
    unsigned short priority_;
    PriorityQueueNode* next_;
    PriorityQueueNode() = default;
    PriorityQueueNode(HuffmanNode* val, unsigned short priority, PriorityQueueNode* next = nullptr) :
        val_(val), priority_(priority), next_(next)
    {}
    ~PriorityQueueNode() = default;
  };

  struct PriorityQueue
  {
    size_t size_;
    PriorityQueueNode* first_;
    PriorityQueue(size_t size = 0, PriorityQueueNode* first = nullptr) : size_(size), first_(first) {}
    ~PriorityQueue();
  };

  //void deletePriorityQueue(PriorityQueueNode* node);
  void addPriorityQueue(PriorityQueue& queue, HuffmanNode* val, unsigned short priority);
  HuffmanNode* getPriorityQueue(PriorityQueue& queue);
}
#endif
