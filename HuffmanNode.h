#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <string>

namespace nabiullin
{
  struct HuffmanNode
  {
    size_t key_;
    unsigned char value_;
    HuffmanNode* left_;
    HuffmanNode* right_;
    HuffmanNode() = default;
    HuffmanNode(size_t key, char value, HuffmanNode* left = nullptr, HuffmanNode* right = nullptr) :
        key_(key), value_(value), left_(left), right_(right)
    {}
    HuffmanNode(HuffmanNode* left, HuffmanNode* right)
    {
      value_ = '\0';
      left_ = left;
      right_ = right;
      key_ = left->key_ + right->key_;
    }
    HuffmanNode(HuffmanNode* src)
    {
      swap(*src);
    }
    ~HuffmanNode();
    void deleteHuffmanNode(HuffmanNode* node);
    void swap(HuffmanNode& src);
    HuffmanNode& operator=(HuffmanNode&& src) noexcept;
  };

  bool operator>(const HuffmanNode&, const HuffmanNode&);
  bool operator<(const HuffmanNode&, const HuffmanNode&);
}
#endif
