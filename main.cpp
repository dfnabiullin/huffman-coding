#include <climits>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include "HuffmanNode.h"
#include "PriorityQueue.h"

namespace nabiullin
{
  std::string reverse(std::string const& s)
  {
    std::string rev(s.rbegin(), s.rend());
    return rev;
  }

  void fillFrequencyTable(unsigned short* frequencyTable, std::string data)
  {
    for (size_t i = 0; i < data.size(); i++)
    {
      frequencyTable[data[i]]++;
    }
  }

  void fillPriorityQueue(PriorityQueue* huffmanQueue, unsigned short* frequencyTable)
  {
    for (size_t i = 0; i < UCHAR_MAX; i++)
    {
      if (frequencyTable[i])
      {
        HuffmanNode* temp = new HuffmanNode(frequencyTable[i], i);
        addPriorityQueue(*huffmanQueue, temp, frequencyTable[i]);
      }
    }
    while (huffmanQueue->size_ > 1)
    {
      unsigned short priority = huffmanQueue->first_->priority_;
      priority += huffmanQueue->first_->next_->priority_;
      HuffmanNode* left_ = getPriorityQueue(*huffmanQueue);
      HuffmanNode* right_ = getPriorityQueue(*huffmanQueue);
      HuffmanNode* temp = new HuffmanNode(left_, right_);
      addPriorityQueue(*huffmanQueue, temp, priority);
    }
  }

  void fillEncodeTable(HuffmanNode* node, std::string* encodeTable, std::string& encodedChar, size_t& level)
  {
    if (node->value_ == '\0')
    {
      level++;
      encodedChar += "0";
      fillEncodeTable(node->left_, encodeTable, encodedChar, level);
      encodedChar += "1";
      fillEncodeTable(node->right_, encodeTable, encodedChar, level);
    }
    else
    {
      encodeTable[node->value_] = encodedChar;
    }
    if (encodedChar != "")
    {
      encodedChar.erase(encodedChar.end() - 1, encodedChar.end());
    }
    level--;
  }

  void printEncodedData(std::string* encodeTable, std::string data)
  {
    std::ofstream out("encodedFile.txt");
    std::string strEncodedCharacters = "";
    bool checker = false;
    for (size_t i = 0; i < data.size(); i++)
    {
      std::string ttt = data;
      unsigned char ctt = ttt[i];
      std::string encodedData = encodeTable[ctt];
      if (strEncodedCharacters.size())
      {
        if ((strEncodedCharacters + encodedData).size() > 8)
        {
          while (strEncodedCharacters.size() > 8)
          {
            unsigned char temp = std::stoi(strEncodedCharacters.substr(0, 8), nullptr, 2);
            out << temp;
            strEncodedCharacters.erase(0, 8);
          }
          while (strEncodedCharacters.size() < 8 && !encodedData.empty())
          {
            strEncodedCharacters += encodedData[0];
            encodedData.erase(encodedData.begin());
          }
          unsigned char temp = std::stoi(strEncodedCharacters, nullptr, 2);
          out << temp;
          checker = false;
          strEncodedCharacters = "";
        }
      }
      strEncodedCharacters += encodedData;
      checker = true;
    }
    if (checker)
    {
      unsigned char temp = std::stoi(strEncodedCharacters, nullptr, 2);
      out << temp;
    }
    out.close();
  }

  void printDecodedData(HuffmanNode* node, std::string& data, std::ofstream& out)
  {
    if (node->value_ != '\0')
    {
      out << node->value_;
    }
    else if (data[0] == '0')
    {
      data.erase(data.begin(), data.begin() + 1);
      printDecodedData(node->left_, data, out);
    }
    else if (data[0] == '1')
    {
      data.erase(data.begin(), data.begin() + 1);
      printDecodedData(node->right_, data, out);
    }
  }

  unsigned short* encode(std::string data)
  {
    unsigned short* frequencyTable = new unsigned short[UCHAR_MAX];
    for (int i = 0; i < UCHAR_MAX; ++i)
    {
      frequencyTable[i] = '\0';
    }
    fillFrequencyTable(frequencyTable, data);
    PriorityQueue* huffmanQueue = new PriorityQueue[1];
    fillPriorityQueue(huffmanQueue, frequencyTable);
    std::string encodeTable[UCHAR_MAX];
    std::string encodedChar = "";
    size_t level = 0;
    fillEncodeTable(huffmanQueue->first_->val_, encodeTable, encodedChar, level);
    printEncodedData(encodeTable, data);
    delete[] huffmanQueue;
    return frequencyTable;
  }

  void decode(std::string data, unsigned short* frequencyTable)
  {
    PriorityQueue* huffmanQueue = new PriorityQueue[1];
    fillPriorityQueue(huffmanQueue, frequencyTable);
    std::ofstream out("decodedFile.txt");
    std::string encodedLine = "";
    for (size_t i = 0; i < data.size(); i++)
    {
      unsigned char temp = data[i];
      std::string strTemp = "";
      for (size_t i = 0; i < 8; i++)
      {
        if (temp % 2)
        {
          strTemp += '1';
        }
        else
        {
          strTemp += '0';
        }
        temp = temp >> 1;
      }
      strTemp = reverse(strTemp);
      encodedLine += strTemp;
    }
    while (encodedLine.size() > 1)
    {
      printDecodedData(huffmanQueue->first_->val_, encodedLine, out);
    }
    out.close();
    delete[] huffmanQueue;
  }
}

int main()
{
  std::string data;

  std::stringstream buffer;
  std::ifstream inEncode("file.txt");
  buffer << inEncode.rdbuf();
  inEncode.close();
  data = buffer.str();
  unsigned short* frequencyTable = nabiullin::encode(data);
  std::ofstream outFrequencyTable("frequencyTable_encodedFile.txt");
  for (size_t i = 0; i < UCHAR_MAX; i++)
  {
    outFrequencyTable << frequencyTable[i] << '\n';
  }
  outFrequencyTable.close();
  std::string encodedData;

  std::ifstream inDecode("encodedFile.txt");
  std::stringstream ss;
  ss << inDecode.rdbuf();
  inDecode.close();
  encodedData = ss.str();
  std::ifstream inFrequencyTable("frequencyTable_encodedFile.txt");
  for (size_t i = 0; i < UCHAR_MAX; i++)
  {
    inFrequencyTable >> frequencyTable[i];
  }
  inFrequencyTable.close();
  nabiullin::decode(encodedData, frequencyTable);
  delete[] frequencyTable;
  return 0;
}
