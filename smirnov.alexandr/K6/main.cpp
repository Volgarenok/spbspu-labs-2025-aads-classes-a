#include <iostream>
#include <cstddef>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right, * parent;
};

int main()
{
  size_t length = 0;
  std::cin >> length;
  int * arr = new int[length];
  for (size_t i = 0; i < length; ++i)
  {
    if (!(std::cin >> arr[i]))
    {
      delete[] arr;
      std::cerr << "Input error\n";
      return 1;
    }
  }
}
