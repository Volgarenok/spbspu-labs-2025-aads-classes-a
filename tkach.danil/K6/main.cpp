#include <iostream>
#include <functional>

namespace
{
  template< class T >
  struct BiTree {
    T data;
    BiTree< T > * left, * right, * parent;
  };

  template< class T >
  BiTree< T > * rotate_right(BiTree< T > * root);

  template< class T >
  BiTree< T > * rotate_left(BiTree< T > * root);

  template< class T, class Cmp >
  BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp)
  {
    while (root != nullptr)
    {
      if (value == root->data)
      {
        return root;
      }
      if (cmp(value, root->data))
      {
        root = root->left;
      }
      else if (!(cmp(value, root->data)))
      {
        root = root->right;
      }
    }
    return nullptr;
  }

  template< class T >
  void clear(BiTree< T >* root)
  {
    if (root)
    {
      clear(root->left);
      clear(root->right);
      delete root;
    }
  }

  template< class T, class Cmp >
  BiTree< T >* insertValue(BiTree< T >* root, T value, Cmp cmp)
  {
    if (root == nullptr)
    {
      return new BiTree< T >{value, nullptr, nullptr, nullptr};
    }
    if (cmp(value, root->data))
    {
      root->left = insertValue(root->left, value, cmp);
      if (root->left->parent == nullptr)
      {
        root->left->parent = root;
      }
    }
    else
    {
      root->right = insertValue(root->right, value, cmp);
      if (root->right->parent == nullptr)
      {
        root->right->parent = root;
      }
    }
    return root;
  }
}

int main()
{
  size_t size = 0;
  std::cin >> size;
  if (size == 0)
  {
    return 0;
  }
  BiTree< int >* root = nullptr;
  int value = 0;
  for (size_t i = 0; i < size; ++i)
  {
    if (!(std::cin >> value))
    {
      clear(root);
      std::cerr << "Wrong input\n";
      return 1;
    }
    try
    {
      root = insertValue(root, value, std::less<int>());
    }
    catch (const std::bad_alloc&)
    {
      clear(root);
      std::cerr << "Memory error\n";
      return 1;
    }
  }
  std::string rotate_command = "";
  int num = 0;
  while (std::cin >> rotate_command)
  {
    if (!(std::cin >> num))
    {
      clear(root);
      std::cerr << "INVALID COMMAND\n";
      return 1;
    }
    
  }

  return 0;
}
