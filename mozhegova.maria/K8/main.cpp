#include <iostream>
#include <functional>

template< class T, class Cmp >
struct BiTree {
  T data;
  Cmp cmp;
  BiTree< T, Cmp > * left, * right, * parent;
};

template< class T, class Cmp >
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & value, BiTree< T, Cmp > ** result)
{
  if (!root)
  {
    return root;
  }
  BiTree< T, Cmp > * temp = root;
  while (temp && temp->data != value)
  {
    if (root->cmp(value, temp->data))
    {
      temp = temp->left;
    }
    else
    {
      temp = temp->right;
    }
  }
  if (!temp)
  {
    return root;
  }
  BiTree< T, Cmp > * newTemp = temp;
  if (newTemp->left)
  {
    newTemp = newTemp->left;
    while (newTemp->right)
    {
      newTemp = newTemp->right;
    }
  }
  else if (newTemp->right)
  {
    newTemp = newTemp->right;
    while (newTemp->left)
    {
      newTemp = newTemp->left;
    }
  }
  if (newTemp->parent->left == newTemp)
  {
    newTemp->parent->left = nullptr;
  }
  else
  {
    newTemp->parent->right = nullptr;
  }
  newTemp->parent = temp->parent;
  newTemp->left = temp->left;
  newTemp->right = temp->right;
  temp->left = nullptr;
  temp->right = nullptr;
  if (newTemp->left)
  {
    newTemp->left->parent = temp;
  }
  if (newTemp->right)
  {
    newTemp->right->parent = temp;
  }
  if (temp->parent)
  {
    if (temp->parent->left == temp)
    {
      temp->parent->left = newTemp;
    }
    else
    {
      temp->parent->right = newTemp;
    }
    temp->parent = nullptr;
    *result = temp;
    return root;
  }
  else
  {
    *result = temp;
    return newTemp;
  }
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
BiTree< T, Cmp > * createBiTree(const T * nums, size_t n, Cmp cmp)
{
  if (n == 0)
  {
    return nullptr;
  }
  BiTree< T, Cmp > * root = new BiTree< T, Cmp >{nums[0], cmp, nullptr, nullptr, nullptr};
  for (size_t i = 1; i < n; i++)
  {
    BiTree< T, Cmp > * current = root;
    BiTree< T, Cmp > * parent = nullptr;
    while (current)
    {
      parent = current;
      if (cmp(nums[i], current->data))
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
      newTree = new BiTree< T, Cmp >{nums[i], cmp, nullptr, nullptr, parent};
    }
    catch (const std::bad_alloc &)
    {
      clear(root);
      throw;
    }
    if (cmp(nums[i], parent->data))
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
void printTree(std::ostream & out, BiTree< T, Cmp > * root)
{
  if (!root)
  {
    return;
  }
  static size_t i = 0;
  printTree(out, root->left);
  if (i != 0)
  {
    out << " ";
  }
  out << root->data;
  i++;
  printTree(out, root->right);
}

int main()
{
  size_t n = 0;
  if (!(std::cin >> n))
  {
    std::cerr << "invalid input\n";
    return 1;
  }
  int * nums = nullptr;
  try
  {
    nums = new int[n];
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "out of memory\n";
    return 1;
  }
  for (size_t i = 0; i < n; i++)
  {
    if (!(std::cin >> nums[i]))
    {
      delete[] nums;
      std::cerr << "invalid input\n";
      return 1;
    }
  }

  BiTree< int, std::less< int > > * root = nullptr;
  try
  {
    root = createBiTree(nums, n, std::less< int >());
  }
  catch (const std::bad_alloc &)
  {
    delete[] nums;
    std::cerr << "Out of memory\n";
    return 1;
  }
  delete[] nums;

  int a = 0;
  while (!(std::cin >> a).eof())
  {
    if (!std::cin)
    {
      std::cerr << "invalid input\n";
      printTree(std::cout, root);
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
  printTree(std::cout, root);
  std::cout << "\n";
  clear(root);
}
