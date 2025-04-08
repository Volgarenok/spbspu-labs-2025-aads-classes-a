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
BiTree< T, Cmp > * getTree(const T * elements, size_t length, Cmp cmp)
{
  if (length == 0)
  {
    return nullptr;
  }
  BiTree< T, Cmp > * root = new BiTree< T, Cmp >{elements[0], cmp, nullptr, nullptr, nullptr};
  for (size_t i = 1; i < length; ++i)
  {
    BiTree< T, Cmp > * newNode = nullptr;
    try
    {
      newNode = new BiTree< T, Cmp >{elements[i], cmp, nullptr, nullptr, nullptr};
    }
    catch (const std::bad_alloc &)
    {
      clear(root);
      throw;
    }
    BiTree< T, Cmp > * current = root;
    BiTree< T, Cmp > * parent = nullptr;
    while (current)
    {
      parent = current;
      if (cmp(elements[i], current->data))
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }
    newNode->parent = parent;
    if (cmp(elements[i], parent->data))
    {
      parent->left = newNode;
    }
    else
    {
      parent->right = newNode;
    }
  }
  return root;
}

template< class T, class Cmp >
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & value, BiTree< T, Cmp > ** result)
{
  *result = nullptr;
  if (!root)
  {
    return nullptr;
  }
  BiTree< T, Cmp > * current = root;
  while (current && (current->data != value))
  {
    if (current->cmp(value, current->data))
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  if (!current)
  {
    return root;
  }
  BiTree< T, Cmp > * deleteNode = root;
  *result = deleteNode;
  if (!current->left || !current->right)
  {
    if (current->left)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
    if (current)
    {
      current->parent = deleteNode->parent;
    }
  }
  else
  {
    BiTree< T, Cmp > * minNode = current->right;
    while (minNode->left)
    {
      minNode = minNode->left;
    }
    current->data = minNode->data;
    if (minNode->parent->left == minNode)
    {
      minNode->parent->left = minNode->right;
    }
    else
    {
      minNode->parent->right = minNode->right;
    }
    if (minNode->right)
    {
      minNode->right->parent = minNode->parent;
    }
    *result = minNode;
  }
  return root;
}

template< class T, class Cmp >
void clear(BiTree< T, Cmp > * root)
{
  if (root)
  {
    clear(root->left);
    clear(root->right);
    delete root;
  }
}

template< class T, class Cmp >
void printTree(std::ostream & out, BiTree< T, Cmp > * root)
{
  if (!root)
  {
    return;
  }
  static bool isFirst = true;
  printTree(out, root->left);
  if (!isFirst)
  {
    out << " ";
  }
  out << root->data;
  isFirst = false;
  printTree(out, root->right);
}

int main()
{
  size_t length = 0;
  if (!(std::cin >> length))
  {
    std::cerr << "ERROR: input\n";
    return 1;
  }
  int * elements = new int[length];
  for (size_t i = 0; i < length; ++i)
  {
    if (!(std::cin >> elements[i]))
    {
      delete[] elements;
      std::cerr << "ERROR: input\n";
      return 1;
    }
  }
  BiTree< int, std::less< int > > * root = nullptr;
  try
  {
    root = getTree(elements, length, std::less< int >());
  }
  catch (const std::bad_alloc &)
  {
    delete[] elements;
    std::cerr << "ERROR: memory\n";
    return 1;
  }
  delete[] elements;
  int value = 0;
  while (!(std::cin >> value).eof())
  {
    if (!std::cin)
    {
      printTree(std::cout, root);
      std::cout << "\n";
      clear(root);
      std::cerr << "ERROR: input\n";
      return 1;
    }
    BiTree< int, std::less< int > > * extracted = nullptr;
    root = extract(root, value, std::addressof(extracted));
    if (extracted)
    {
      delete extracted;
    }
    else
    {
      std::cout << "<INVALID NODE>\n";
    }
  }
  printTree(std::cout, root);
  std::cout << "\n";
  clear(root);
}
