#include <iostream>

template< class T >
struct BiTree
{
  T data;
  BiTree< T > * left, * right, * parent;
};

void deleteTree(BiTree< int >* root)
{
  if (root == nullptr)
  {
    return;
  }

  deleteTree(root-> left);
  deleteTree(root->right);

  delete root;
}

void insertNode(BiTree< int >* root, int value)
{
  BiTree< int >* current = root;
  BiTree< int >* parent = nullptr;

  while (current)
  {
    parent = current;
    if (value < current->data)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  current = new BiTree< int >{ value, nullptr, nullptr, parent };
  if (value < parent->data)
  {
    parent->left = current;
  }
  else
  {
    parent->right = current;
  }
}

BiTree< int >* buildTree(size_t size)
{
  if (size <= 0)
  {
    return nullptr;
  }

  int value = 0;
  if (!(std::cin >> value))
  {
    throw std::invalid_argument("");
  }
  BiTree< int >* root = new BiTree< int >{ value, nullptr, nullptr, nullptr };

  for (size_t i = 1; i < size; i++)
  {
    if ((!std::cin >> value))
    {
      throw std::invalid_argument("");
    }
    insertNode(root, value);
  }

  return root;
}
int main()
{
  size_t size = 0;
  std::cin >> size;
  BiTree< int >* root = nullptr;

  try
  {
    root = buildTree(size);
  }
  catch (const std::bad_alloc& e)
  {
    deleteTree(root);
    std::cerr << "Memory allocation error!\n";
    return 2;
  }
  catch (const std::invalid_argument& e)
  {
    deleteTree(root);
    std::cerr << "Incorrect input!\n";
    return 1;
  }
}
