#include <iostream>
#include <functional>

template< class T, class Cmp >
struct BiTree
{
  T data;
  Cmp cmp;
  BiTree< T, Cmp > * left, * right, * parent;
};

template< class T, class Cmp >
BiTree< T, Cmp > * getTree(std::istream & in)
{}

template< class T, class Cmp >
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & value, BiTree< T, Cmp > ** result)
{}

template< class T, class Cmp >
void clear(BiTree< T, Cmp > * root)
{}


int main()
{
  BiTree< int, std::less< int > > * root = getTree< int, std::less< int > >(std::cin);
  if (!std::cin)
  {
    clear(root);
    std::cerr << "ERROR: input\n";
    return 1;
  }
  int value = 0;
  while (!(std::cin >> value).eof() && !std::cin.fail())
  {
    BiTree< int, std::less< int > > * extracted = nullptr;
    root = extract(root, value, std::addressof(extracted));
    if (extracted)
    {
      delete extracted;
    }
    else
    {
      std::cout << "<INVALID NODE>";
    }
  }
  if (!std::cin)
  {
    clear(root);
    std::cerr << "ERROR: input\n";
    return 1;
  }
  clear(root);
}
