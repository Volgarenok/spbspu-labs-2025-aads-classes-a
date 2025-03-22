#include <iostream>
#include <string>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right, * parent;
};

template< class T >
BiTree< T > * rotate_right(BiTree< T > * root)
{
  if (root->left == nullptr)
  {
    throw std::logic_error("invalid rotate");
  }
  BiTree< int > * newRoot = root->left;
  BiTree< int > * temp = newRoot->right;
  root->left = temp;
  if (temp)
  {
    temp->parent = root;
  }
  newRoot->right = root;
  newRoot->parent = root->parent;
  root->parent = newRoot;
  return newRoot;
}

template< class T >
BiTree< T > * rotate_left(BiTree< T > * root)
{
  if (root->right == nullptr)
  {
    throw std::logic_error("invalid rotate");
  }
  BiTree< int > * newRoot = root->right;
  BiTree< int > * temp = newRoot->left;
  root->right = temp;
  if (temp)
  {
    temp->parent = root;
  }
  newRoot->left = root;
  newRoot->parent = root->parent;
  root->parent = newRoot;
  return newRoot;
}

template< class T, class Cmp >
BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp)
{
  BiTree< int > * temp = root;
  while (temp && temp->data != value)
  {
    if (cmp(value, temp->data))
    {
      temp = temp->left;
    }
    else
    {
      temp = temp->right;
    }
  }
  return temp;
}

template< class T >
void clear(BiTree< T > * root)
{
  while (root)
  {
    clear(root->left);
    clear(root->right);
    delete root;
  }
}

template< class T >
BiTree< T > * createBiTree(const T * nums, size_t n)
{
  BiTree< int > * root = new BiTree< int >{nums[0], nullptr, nullptr, nullptr};
  for (size_t i = 1; i < n; i++)
  {
    BiTree< int > * temp = root;
    while (temp->left && temp->right)
    {
      if (nums[i] > temp->data)
      {
        temp = temp->right;
      }
      else
      {
        temp = temp->left;
      }
    }
    while (temp->right && nums[i] > temp->data)
    {
      temp = temp->right;
    }
    while (temp->left && nums[i] < temp->data)
    {
      temp = temp->left;
    }
    BiTree< int > * newTree = nullptr;
    try
    {
      newTree = new BiTree< int >{nums[i], nullptr, nullptr, temp};
    }
    catch (const std::bad_alloc &)
    {
      clear(root);
      throw;
    }
    if (nums[i] > temp->data)
    {
      temp->right = newTree;
    }
    else
    {
      temp->left = newTree;
    }
  }
  return root;
}

int main()
{
  size_t n = 0;
  std::cin >> n;
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

  BiTree< int > * root = nullptr;
  try
  {
    root = createBiTree(nums, n);
  }
  catch (const std::bad_alloc &)
  {
    delete[] nums;
    std::cerr << "Out of memory\n";
  }

  std::string direct;
  int num = 0;
  while (!std::cin.eof())
  {
    std::cin >> direct;
    if ((direct != "left" && direct != "right") || !(std::cin >> num))
    {
      delete[] nums;
      clear(root);
      std::cout << "INVALID COMMAND\n";
      return 1;
    }
    BiTree< int > * findNode = find(root, num, std::less< int>());
    if (findNode == nullptr)
    {
      delete[] nums;
      clear(root);
      std::cout << "INVALID ROTATE\n";
      return 1;
    }
    BiTree< int > * temp = nullptr;
    try
    {
      if (direct == "left")
      {
        temp = rotate_left(findNode);
      }
      else
      {
        temp = rotate_right(findNode);
      }
    }
    catch(const std::logic_error &)
    {
      delete[] nums;
      clear(root);
      std::cout << "INVALID ROTATE\n";
      return 1;
    }
    std::cout << temp->data << '\n';
  }
  delete[] nums;
  clear(root);
}
