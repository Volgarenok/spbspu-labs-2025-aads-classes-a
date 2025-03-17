#include <iostream>
#include <string>

template< class T >
struct BiTree
{
  T data;
  BiTree< T > * left, * right, * parent;
};

template< class T >
BiTree< T > * rotateRight(BiTree< T > * root)
{}

template< class T >
BiTree< T > * rotateLeft(BiTree< T > * root)
{}

template< class T, class Cmp >
BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp)
{}

template< class T, class Cmp >
BiTree< T > * convert(const T * data, size_t s, Cmp cmp)
{}

template< class T >
void deleteTree(BiTree< T > * root)
{}

int main()
{
  size_t count = 0;
  if (!(std::cin >> count))
  {
    std::cerr << "ERROR: wrong input\n";
    return 1;
  }
  if (count < 0)
  {
    std::cerr << "ERROR: count not negative\n";
    return 1;
  }
  int * elements = new int[count];
  for (size_t i = 0; i < count; i++)
  {
    if (!(std::cin >> elements[i]))
    {
      std::cerr << "EEROR: wrong input\n";
      delete[] elements;
      return 1;
    }
  }
  std::less< int > cmp;
  BiTree< int > * root = nullptr;
  try
  {
    root = convert(elements, count, cmp);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    delete[] elements;
    return 1;
  }
  delete[] elements;

  std::string name;
  int num = 0;
  while ((std::cin >> name >> num) && !std::cin.eof())
  {
    BiTree< int > * node = find(root, num, cmp);
    if (!node)
    {
      std::cout << "<INVALID ROTATE>\n";
      deleteTree(root);
      return 1;
    }
    BiTree< int > * rotateNode = nullptr;
    if (name == "left")
    {
      rotateNode = rotateLeft(node);
    }
    else if (name == "right")
    {
      rotateNode = rotateRight(node);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      deleteTree(root);
      return 1;
    }
    if (!rotateNode)
    {
      std::cout << "<INVALID ROTATE>\n";
      deleteTree(root);
      return 1;
    }
  }
}
