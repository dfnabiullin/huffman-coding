#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"

namespace nabiullin
{

  PriorityQueue::~PriorityQueue()
  {
    delete this->first_->val_;
    delete this->first_;
  }

  void addPriorityQueue(PriorityQueue& queue, HuffmanNode* val, unsigned short priority)
  {
    // If the queue is full we don't have to add the specified value.
    // We output an error message to the console and return.
    // if ((*queue)->size == UCHAR_MAX)
    //{
    //  printf("\nQueue is full.\n");
    //  return;
    //}

    PriorityQueueNode* aux = new PriorityQueueNode(val, priority);

    // If the queue is empty we add the first value.
    // We validate twice in case the structure was modified abnormally at runtime (rarely happens).
    if (queue.size_ == 0 || queue.first_ == nullptr)
    {
      aux->next_ = nullptr;
      queue.first_ = aux;
      queue.size_ = 1;
      return;
    }
    else
    {
      // If there are already elements in the queue and the priority of the element
      // that we want to add is greater than the priority of the first element,
      // we'll add it in front of the first element.

      // Be careful, here we need the priorities to be in descending order
      if (priority <= queue.first_->priority_)
      {
        aux->next_ = queue.first_;
        queue.first_ = aux;
        queue.size_++;
        return;
      }
      else
      {
        // We're looking for a place to fit the element depending on it's priority
        PriorityQueueNode* iterator = queue.first_;
        while (iterator->next_ != nullptr)
        {
          // Same as before, descending, we place the element at the begining of the
          // sequence with the same priority for efficiency even if
          // it defeats the idea of a queue.
          if (priority <= iterator->next_->priority_)
          {
            aux->next_ = iterator->next_;
            iterator->next_ = aux;
            queue.size_++;
            return;
          }
          iterator = iterator->next_;
        }
        // If we reached the end and we haven't added the element,
        // we'll add it at the end of the queue.
        if (iterator->next_ == nullptr)
        {
          aux->next_ = nullptr;
          iterator->next_ = aux;
          queue.size_++;
          return;
        }
      }
    }
  }

  HuffmanNode* getPriorityQueue(PriorityQueue& queue)
  {
    HuffmanNode* temp = new HuffmanNode(queue.first_->val_);
    // We get elements from the queue as long as it isn't empty
    if (queue.size_ > 0)
    {
      PriorityQueueNode* temp = queue.first_;
      queue.first_ = queue.first_->next_;
      queue.size_--;
      delete temp;
    }
    // else
    //{
    //   // If the queue is empty we show an error message.
    //   // The function will return whatever is in the memory at that time as returnValue.
    //   // Or you can define an error value depeding on what you choose to store in the queue.
    //   printf("\nQueue is empty.\n");
    // }
    return temp;
  }
}