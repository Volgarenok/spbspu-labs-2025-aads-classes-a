#include <iostream>
#include <cstddef>

template< class T >
struct List
{
  T data;
  List< T > * next;
};
List< List< int > * > * convert(const int * const * d, size_t m, const size_t * n)
{
  List< List< int > * > * head = nullptr;
  for (size_t i = 0; i < m; ++i)
  {
    List< int > * inHead = nullptr;
    List< int > * inTail = nullptr;
    try
    {
      inHead = new List< int >{d[i][0], nullptr};
      inTail = inHead;
      for (size_t j = 1; j < n[i]; ++j)
      {
        List< int > * newElement = new List< int >{d[i][j], nullptr};
        inTail->next = newElement;
        inTail = newElement;
      }
    }
    catch (const std::bad_alloc &)
    {}
  }
  return head;
}
void deleteArray(int ** array, size_t numArray)
{
  for (size_t i = 0; i < numArray; ++i)
  {
    delete[] array[i];
  }
  delete[] array;
}

int main()
{
  size_t numArray = 0;
  if (!(std::cin >> numArray))
  {
    std::cerr << "error input number of arrays\n";
    return 1;
  }
  int ** array = new int*[numArray];
  size_t * numElements = new size_t[numArray];
  for (size_t i = 0; i < numArray; i++)
  {
    if (!(std::cin >> numElements[i]))
    {
      std::cerr << "error input\n";
      deleteArray(array, i);
      delete[] numElements;
      return 1;
    }
    try
    {
      array[i] = new int[numElements[i]];
    }
    catch (const std::bad_alloc & e)
    {
      std::cerr << "memory error\n";
      deleteArray(array, i);
      delete[] numElements;
      return 1;
    }
    for (size_t j = 0; j < numElements[i]; j++)
    {
      if (!(std::cin >> array[i][j]))
      {
        std::cerr << "error input\n";
        deleteArray(array, i);
        delete[] numElements;
        return 1;
      }
    }
  }
  deleteArray(array, numArray);
}
