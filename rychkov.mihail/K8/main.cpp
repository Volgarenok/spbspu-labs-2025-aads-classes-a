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

int main()
{
  size_t size = 0;
  if (!(std::cin >> size))
  {
    std::cerr << "failed to read size\n";
    return 1;
  }
  BiTree< int, std::less< int > >* root = nullptr;
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
  destroy(root);
}
