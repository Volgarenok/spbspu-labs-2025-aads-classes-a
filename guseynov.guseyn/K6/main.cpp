#include <iostream>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right, * parent;
};
// 1
template< class T >
BiTree< T > * rotate_right(BiTree< T > * root);

// 2
template< class T >
BiTree< T > * rotate_left(BiTree< T > * root);

// 3
template< class T, class Cmp >
BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp);

Bitree * createTree(int * arr, size_t current);

int main()
{
  size_t length = 0;
  std::cin >> length;
  int * arr;
  try
  {
    arr = new int[length];
  }
  catch(std::bad_alloc &e)
  {
    std::cerr << "Bad alloc";
    return 1;
  }
  for(size_t i = 0; i < length; i++)
  {
    std::cin >> arr[i];
  }
  if(!std::good)
  {
    std::cerr << "Bad reading";
    return 1;
  }

}

BiTree * createTree(BiTree * Tree,int * arr, size_t current)
{

}
