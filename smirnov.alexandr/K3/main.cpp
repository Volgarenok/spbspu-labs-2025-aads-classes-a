#include <iostream>
#include <cstddef>
#include <stdexcept>

template< class T >
struct List
{
  T data;
  List< T > * next;
};

int main()
{
  size_t m;
  std::cin >> m;
  if (!std::cin)
  {
    throw std::runtime_error("Invalid input for number of arrays");
  }
  size_t * n = new size_t[m];
  for (size_t i = 0; i < m; ++i)
  {
    std::cin >> n[i];
    if (!std::cin)
    {
      throw std::runtime_error("Invalid input for array size");
    }
  }
}
