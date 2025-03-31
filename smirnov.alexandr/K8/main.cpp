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
BiTree< T, Cmp > * getTree(std::istream & is)
{
  size_t size;
  if (!(is >> size))
  {
    return nullptr;
  }
  BiTree< T, Cmp > * root = nullptr;
  for (size_t i = 0; i < size; ++i)
  {
    T value;
    if (!(is >> value))
    {
      clear(root);
      return nullptr;
    }
    BiTree< T, Cmp > * current = root;
    BiTree< T, Cmp > * parent = nullptr;
    while (current != nullptr)
    {
      parent = current;
      if (current->cmp(value, current->data))
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }
    BiTree< T, Cmp > * newTree = nullptr;
    try
    {
      newTree = new BiTree< T, Cmp >{value, Cmp(), nullptr, nullptr, parent};
    }
    catch (const std::bad_alloc & e)
    {
      clear(root);
      throw;
    }
    if (parent == nullptr)
    {
      root = newTree;
    }
    else if (parent->cmp(value, parent->data))
    {
      parent->left = newTree;
    }
    else
    {
      parent->right = newTree;
    }
  }
  return root;
}

template< class T, class Cmp >
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & rhs, BiTree< T, Cmp > ** extracted);

template< class T, class Cmp >
void clear(BiTree< T, Cmp > * root)
{
  if (root != nullptr)
  {
    clear(root->left);
    clear(root->right);
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
