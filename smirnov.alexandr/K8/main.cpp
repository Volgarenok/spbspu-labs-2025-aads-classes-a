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
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & rhs, BiTree< T, Cmp > ** extracted)
{
  if (root == nullptr)
  {
    extracted = nullptr;
    return nullptr;
  }
  if (root->cmp(rhs, root->data))
  {
    root->left = extract(root->left, rhs, extracted);
    if (root->left != nullptr)
    {
      root->left->parent = root;
    }
    return root;
  }
  if (root->cmp(root->data, rhs))
  {
    root->right = extract(root->right, rhs, extracted);
    if (root->right != nullptr)
    {
      root->right->parent = root;
    }
    return root;
  }
  *extracted = root;
  if (root->left == nullptr)
  {
    BiTree< T, Cmp > * right_child = root->right;
    if (right_child != nullptr)
    {
      right_child->parent = root->parent;
    }
    root->right = nullptr;
    return right_child;
  }
  if (root->right == nullptr)
  {
    BiTree< T, Cmp > * left_child = root->left;
    if (left_child != nullptr)
    {
      left_child->parent = root->parent;
    }
    root->left = nullptr;
    return left_child;
  }
  BiTree< T, Cmp > * min_node = root->right;
  while (min_node->left != nullptr)
  {
    min_node = min_node->left;
  }
  root->data = min_node->data;
  root->right = extract(root->right, min_node->data, extracted);
  return root;
}

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

template< class T, class Cmp >
void print(BiTree< T, Cmp > * root)
{
  bool first = true;
  if (root != nullptr)
  {
    if (first)
    {
      print(root->left);
    }
    else
    {
      std::cout << " ";
    }
    std::cout << root->data;
    print(root->right);
    first = false;
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
    print(root);
    clear(root);
    return 1;
  }
  clear(root);
}
