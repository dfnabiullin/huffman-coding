#include <utility>
#include "HuffmanNode.h"

nabiullin::HuffmanNode::~HuffmanNode()
{
  deleteHuffmanNode(this);
}

void nabiullin::HuffmanNode::deleteHuffmanNode(HuffmanNode* node)
{
  if (node)
  {
    deleteHuffmanNode(node->left_);
    deleteHuffmanNode(node->right_);
    delete node;
  }
}

nabiullin::HuffmanNode& nabiullin::HuffmanNode::operator=(HuffmanNode&& src) noexcept
{
  if (this != &src)
  {
    swap(src);
  }
  return *this;
}

void nabiullin::HuffmanNode::swap(HuffmanNode& src)
{
  key_ = src.key_;
  value_ = src.value_;
  std::swap(left_, src.left_);
  std::swap(right_, src.right_);
}

bool nabiullin::operator>(const HuffmanNode& first, const HuffmanNode& second)
{
  return first.key_ > second.key_;
}

bool nabiullin::operator<(const HuffmanNode& first, const HuffmanNode& second)
{
  return first.key_ < second.key_;
}
