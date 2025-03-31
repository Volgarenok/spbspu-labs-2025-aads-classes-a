#include <iostream>
#include <function>

template< class T, class Cmp >
struct BiTree
{
  T data;
  Cmp cmp;
  BiTree< T, Cmp > * left, * right, * parent;
};

template< class T, class Cmp >
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & value, BiTree< T, Cmp > ** result);


int main()
{
  size_t length = 0;
  if (!std::cin >> length)
  {
    std::cerr << "ERROR: input length\n";
    return 1;
  }
  if (length == 0)
  {
    return 0;
  }
  int * elements = new int[length];
  for (size_t i = 0; i < length; i++)
  {
    if (!std::cin >> elements[i])
    {
      std::cerr << "ERROR: input elements\n";
      delete[] elements;
      return 1;
    }
  }
}
