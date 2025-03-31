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
BiTree< T, Cmp > * getTree(std::istream & is);

template< class T, class Cmp >
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & rhs, BiTree< T, Cmp > ** extracted);

template< class T, class Cmp >
void clear(BiTree< T, Cmp > * root)
{
  if (root != nullptr)
  {
    clearBiTree(root->left);
    clearBiTree(root->right);
    delete root;
  }
}

int main()
{
BiTree< int, std::less< int > > * root = getTree< int, std::less< int > >(std::cin);
  if (!std::cin)
  {
    clear(root);
    std::cerr << "Input error!\n";
    return 1;
  }
  int a;
  while (!(std::cin >> a).eof() && !std::cin.fail())
  {
    BiTree< int, std::less< int > > * extracted = nullptr;
    root = extract(root, a, std::addressof(extracted));
    if (extracted)
    {
      delete extracted;
    }
    else
    {
      std::cout << "<INVALID NODE>\n";
    }
  }
  if (!std::cin)
  {
    std::cerr << "Input error!\n";
    clear(root);
    return 1;
  }
  clear(root);
}
