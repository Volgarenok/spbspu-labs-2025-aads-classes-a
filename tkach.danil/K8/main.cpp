#include <iostream>
#include <cstddef>
namespace
{
  template< class T, class Cmp >
  struct BiTree {
    T data;
    Cmp cmp;
    BiTree< T, Cmp > * left, * right, * parent;
  };


  template< class T, class Cmp >
  BiTree< T, Cmp >* findMin(BiTree< T, Cmp >* root)
  {
    while (root != nullptr && root->left != nullptr)
    {
      root = root->left;
    }
    return root;
  }

  template< class T, class Cmp >
  BiTree< T, Cmp >* findMax(BiTree< T, Cmp >* root)
  {
    while (root != nullptr && root->right != nullptr)
    {
      root = root->right;
    }
    return root;
  }

  template< class T, class Cmp >
  BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & value, BiTree< T, Cmp > ** result)
  {
    if (!root)
    {
      *result = nullptr;
      return nullptr;
    }
    if (root->cmp(value, root->data))
    {
      root->left = extract(root->left, value, result);
    }
    else if (root->cmp(root->data, value))
    {
      root->right = extract(root->right, value, result);
    }
    else
    {
      *result = root;
      if (root->left != nullptr)
      {
        BiTree< T, Cmp >* max_tree = findMax(root->left);
        root->data = max_tree->data;
        root->left = extract(root->left, max_tree->data, result);
      }
      else if (root->right != nullptr)
      {
        BiTree< T, Cmp >* min_tree = findMin(root->right);
        root->data = min_tree->data;
        root->right = extract(root->right, min_tree->data, result);
      }
      else
      {
        return nullptr;
      }
    }
    return root;
  }


  template< class T, class Cmp >
  void clear(BiTree< T, Cmp >* root)
  {
    if (root)
    {
      clear(root->left);
      clear(root->right);
      delete root;
    }
  }

  template< class T, class Cmp >
  BiTree< T, Cmp >* insertValue(BiTree< T, Cmp >* const root, const T value, Cmp cmp)
  {
    if (root == nullptr)
    {
      return new BiTree< T, Cmp >{value, cmp, nullptr, nullptr, nullptr};
    }
    else if (cmp(value, root->data))
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
  if (!std::cin >> size)
  {
    std::cerr << "Wrong input\n";
    return 1;
  }
  BiTree< int, std::less< int > >* root = nullptr;
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
  int num = 0;
  while (!(std::cin >> num).eof() && !std::cin.fail())
  {
    BiTree< int, std::less< int > >* extracted = nullptr;
    root = extract(root, num, std::addressof(extracted));
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
    std::cerr << "Not number\n";
    clear(root);
    return 1;
  }
  clear(root);
  return 0;
}
