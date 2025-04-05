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
      BiTree<T, Cmp> * current = root;
      BiTree<T, Cmp> * parent = nullptr;
      while (current != nullptr)
      {
        parent = current;
        if (cmp(arr[i], current->data))
        {
          current = current->left;
        }
        else
        {
          current = current->right;
        }
      }
      BiTree<T, Cmp>* newNode = new BiTree<T, Cmp>{arr[i], cmp, nullptr, nullptr, parent};
      if (parent == nullptr)
      {
        root = newNode;
      }
      else if (cmp(arr[i], parent->data))
      {
        parent->left = newNode;
      }
      else
      {
        parent->right = newNode;
      }
    }
  }
  catch (const std::bad_alloc& e)
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
void print(std::ostream & out, BiTree< T, Cmp > * root)
{
  static bool first = true;
  if (!root)
  {
    return;
  }
  print(out, root->left);
  if (!first)
  {
    out << " ";
  }
  out << root->data;
  first = false;
  print(out, root->right);
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
    root = getTree(arr, size, std::less< int >());
  }
  catch (const std::bad_alloc & e)
  {
    delete[] arr;
    std::cerr << "Out of memory\n";
    return 1;
  }
  delete[] arr;
  if (!std::cin)
  {
    clear(root);
    std::cerr << "Input error!\n";
    return 1;
  }
  int a = 0;
  while (!(std::cin >> a).eof())
  {
    if (!std::cin)
    {
      std::cerr << "Input error\n";
      print(std::cout, root);
      std::cout << "\n";
      clear(root);
      return 1;
    }
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
  print(std::cout, root);
  std::cout << "\n";
  clear(root);
}
