#include <iostream>
#include <functional>
#include <string>

template< class T, class Cmp >
struct BiTree
{
  T data;
  Cmp cmp;
  BiTree* left = nullptr;
  BiTree* right = nullptr;
  BiTree* parent = nullptr;
};
template< class T, class Cmp >
BiTree< T, Cmp >* rotate_right(BiTree< T, Cmp >* root)
{
  if ((root == nullptr) || (root->left == nullptr))
  {
    return nullptr;
  }
  BiTree< T, Cmp >* result = root->left;
  result->parent = root->parent;
  if (root->parent != nullptr)
  {
    if (root->parent->left == root)
    {
      root->parent->left = result;
    }
    else
    {
      root->parent->right = result;
    }
  }
  root->parent = result;
  root->left = result->right;
  result->right = root;
  return result;
}
template< class T, class Cmp >
BiTree< T, Cmp >* insert(BiTree< T, Cmp >* root, const T& value)
{
  BiTree< T, Cmp >* result = root;
  if (root == nullptr)
  {
    return new BiTree< T, Cmp >{value};
  }
  while (true)
  {
    if (root->cmp(value, root->data))
    {
      if (root->left == nullptr)
      {
        root->left = new BiTree< T, Cmp >{value, {}, nullptr, nullptr, root};
        break;
      }
      else
      {
        root = root->left;
      }
    }
    else
    {
      if (root->right == nullptr)
      {
        root->right = new BiTree< T, Cmp >{value, {}, nullptr, nullptr, root};
        break;
      }
      else
      {
        root = root->right;
      }
    }
  }
  return result;
}
template< class T, class Cmp >
void destroy(BiTree< T, Cmp >* root)
{
  if (root == nullptr)
  {
    return;
  }
  destroy(root->left);
  destroy(root->right);
  delete root;
}
template< class T, class Cmp >
BiTree< T, Cmp >* find(BiTree< T, Cmp >* root, const T& value)
{
  while (root != nullptr)
  {
    if (root->cmp(value, root->data))
    {
      root = root->left;
    }
    else if (root->cmp(root->data, value))
    {
      root = root->right;
    }
    else
    {
      return root;
    }
  }
  return nullptr;
}
template< class T, class Cmp >
BiTree< T, Cmp >* extract(BiTree< T, Cmp >* root, const T& value, BiTree< T, Cmp >** extracted)
{
  BiTree< T, Cmp >* result = find(root, value);
  *extracted = result;
  return root;
}
template< class T, class Cmp >
BiTree< T, Cmp >* begin(BiTree< T, Cmp >* root)
{
  if (root == nullptr)
  {
    return nullptr;
  }
  while (root->left != nullptr)
  {
    root = root->left;
  }
  return root;
}
template< class T, class Cmp >
BiTree< T, Cmp >* next(BiTree< T, Cmp >* node)
{
  if (node->right == nullptr)
  {
    BiTree< T, Cmp >* prev = node;
    node = node->parent;
    for (; (node != nullptr) && (node->right == prev); node = node->parent)
    {}
    return node;
  }
  node = node->right;
  for (; node->left != nullptr; node = node->left)
  {}
  return node;
}

int main()
{
  size_t size = 0;
  if (!(std::cin >> size))
  {
    std::cerr << "failed to read size\n";
    return 1;
  }
  using node_type = BiTree< int, std::less< int > >;
  node_type* root = nullptr;
  int number = 0;
  for (; (size != 0) && (std::cin >> number); size--)
  {
    try
    {
      root = insert(root, number);
    }
    catch (...)
    {
      std::cerr << "failed to construct tree\n";
      destroy(root);
      return 2;
    }
  }
  if (size != 0)
  {
    std::cerr << "failed to read tree\n";
    destroy(root);
    return 1;
  }

  while (std::cin >> number)
  {
    node_type* extracted = nullptr;
    root = extract(root, number, &extracted);
    if (extracted == nullptr)
    {
      std::cerr << "<INVALID NODE>\n";
    }
    else
    {
      std::cout << extracted->data << '\n';
    }
  }
  if (!std::cin.eof())
  {
    std::cerr << "wrong input\n";
    char space[2] = "\0";
    for (node_type* i = begin(root); i != nullptr; i = next(i))
    {
      std::cout << space << i->data;
      space[0] = ' ';
    }
    std::cout << '\n';
    destroy(root);
    return 1;
  }
  destroy(root);
}
