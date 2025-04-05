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
BiTree< T, Cmp > * getTree(const T * arr, size_t size, Cmp cmp)
{
  BiTree< T, Cmp > * root = nullptr;
  try
  {
    for (size_t i = 0; i < size; ++i)
    {
      BiTree< T, Cmp > * new_node = new BiTree< T, Cmp >{arr[i], cmp, nullptr, nullptr, nullptr};
      if (root == nullptr)
      {
        root = new_node;
      }
      else
      {
        BiTree< T, Cmp > * current = root;
        bool flag = true;
        while (flag)
        {
          if (cmp(arr[i], current->data))
          {
            if (current->left == nullptr)
            {
              current->left = new_node;
              new_node->parent = current;
              flag = false;
            }
            else
            {
              current = current->left;
            }
          }
          else
          {
            if (current->right == nullptr)
            {
              current->right = new_node;
              new_node->parent = current;
              flag = false;
            }
            else
            {
              current = current->right;
            }
          }
        }
      }
    }
  }
  catch (const std::bad_alloc & e)
  {
    clear(root);
    throw;
  }
  return root;
}

template< class T, class Cmp >
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & rhs, BiTree< T, Cmp > ** extracted)
{
  if (root == nullptr)
  {
    *extracted = nullptr;
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
  else if (root->cmp(root->data, rhs))
  {
    root->right = extract(root->right, rhs, extracted);
    if (root->right != nullptr)
    {
      root->right->parent = root;
    }
    return root;
  }
  else
  {
    *extracted = root;
    if (root->left == nullptr)
    {
      BiTree< T, Cmp > * right_child = root->right;
      if (right_child != nullptr)
      {
        right_child->parent = root->parent;
      }
      return right_child;
    }
    else if (root->right == nullptr)
    {
      BiTree< T, Cmp > * left_child = root->left;
      if (left_child != nullptr)
      {
        left_child->parent = root->parent;
      }
      return left_child;
    }
    else
    {
      BiTree< T, Cmp > * minRight = root->right;
      while (minRight->left != nullptr)
      {
        minRight = minRight->left;
      }
      root->data = minRight->data;
      root->right = extract(root->right, minRight->data, extracted);
      return root;
    }
  }
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
  size_t size = 0;
  if (!(std::cin >> size))
  {
    std::cerr << "Input error\n";
    return 1;
  }
  int * arr = nullptr;
  try
  {
    arr = new int[size];
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << "Out of memory\n";
    return 1;
  }
  for (size_t i = 0; i < size; ++i)
  {
    if (!(std::cin >> arr[i]))
    {
      delete[] arr;
      std::cerr << "Input error\n";
      return 1;
    }
  }

  BiTree< int, std::less< int > > * root = nullptr;
  try
  {
    root = getTree< int, std::less< int > >(arr, size, std::less< int >());
  }
  catch (const std::bad_alloc & e)
  {
    delete[] arr;
    std::cerr << "Out of memory\n";
    return 1;
  }
  if (!std::cin)
  {
    clear(root);
    std::cerr << "Input error!\n";
    return 1;
  }
  delete[] arr;
  int a = 0;
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
    if (!std::cin)
    {
      std::cerr << "Input error\n";
      print(root);
      clear(root);
      return 1;
    }
  }
  print(root);
  clear(root);
}
