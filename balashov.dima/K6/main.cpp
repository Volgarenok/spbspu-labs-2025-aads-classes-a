#include <iostream>
#include <stdexcept>

template <class T>
struct BiTree
{
  T data;
  BiTree< T >* left, * right;
};

// 1
template< class T >
BiTree< T >* rotate_right(BiTree< T >* root);

// 2
template< class T >
BiTree< T >* rotate_left(BiTree< T >* root);

// 3
template< class T, class Cmp >
BiTree< T >* find(BiTree< T >* root, const T& value, Cmp cmp);

template <class T, class Cmp>
BiTree<T>* insert(BiTree<T>* root, const T& value, Cmp cmp);

int main() {
  int count;
  std::cin >> count;
  if (count < 0)
  {
    throw std::invalid_argument("0>");
    return 1;
  }
  if (count == 0)
  {
    return 0;
  }
  BiTree<int>* root = nullptr;
  std::less<int> cmp;
  try
  {
    for (int i = 0; i < count; ++i)
    {
      int value;
      if (!(std::cin >> value))
      {
        throw std::invalid_argument(":(");
      }
      root = insert(root, value, cmp);
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "something do bad" << "\n";
    return 1;
  }
}
