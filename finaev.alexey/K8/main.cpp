#include <iostream>
#include <functional>

template < class T, class Cmp >
struct BiTree
{
  T data;
  Cmp cmp;
  BiTree< T, Cmp > * left, * right, * parent;
};

template < class T, class Cmp >
void deleteTree(BiTree< T, Cmp >* root)
{
  if (root)
  {
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
  }
}

template < class T, class Cmp >
void insert(BiTree< T, Cmp >* head, BiTree< T, Cmp >* elem)
{
  BiTree< T, Cmp >* current = head;
  if (current->cmp(current->data, elem->data))
  {
    if (!current->right)
    {
      current->right = elem;
      elem->parent = current;
    }
    else
    {
      insert(current->right, elem);
    }
  }
  else
  {
    if (!current->left)
    {
      current->left = elem;
      elem->parent = current;
    }
    else
    {
      insert(current->left, elem);
    }
  }
}

template < class T, class Cmp >
BiTree< int, std::less< int > >* convert(const T* nums, size_t size)
{
  BiTree< T, Cmp >* head = new BiTree< T, Cmp >{nums[0], std::less< int >{}, nullptr, nullptr, nullptr};
  for (size_t i = 1; i < size; ++i)
  {
    BiTree< T, Cmp >* elem = nullptr;
    try
    {
      elem = new BiTree< T, Cmp >{nums[i], std::less< int >{}, nullptr, nullptr, nullptr};
      insert(head, elem);
    }
    catch(const std::bad_alloc& err)
    {
      deleteTree(head);
      throw;
    }
  }
  return head;
}

template< class T, class Cmp >
BiTree< T, Cmp >* find(BiTree< T, Cmp >* root, const T& value)
{
  if (!root)
  {
    return nullptr;
  }
  if (root->data == value)
  {
    return root;
  }
  else
  {
    if (root.cmp(value, root->data))
    {
      root = find(root->right, value);
      return root;
    }
    else
    {
      root = find(root->left, value);
      return root;
    }
  }
}

template < class T, class Cmp >
BiTree < T, Cmp >* minRightTree(BiTree< T, Cmp >* root)
{
  BiTree< T, Cmp >* current = root;
  current = current->right;
  while(current->left)
  {
    current = current->left;
  }
  return current;
}

template < class T, class Cmp >
BiTree < T, Cmp >* maxLeftTree(BiTree< T, Cmp >* root)
{
  BiTree< T, Cmp >* current = root;
  current = current->left;
  while(current->right)
  {
    current = current->right;
  }
  return current;
}

template< class T, class Cmp >
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & value, BiTree< T, Cmp > ** result)
{
  *result = find(root, value);
  if (*result == nullptr)
  {
    throw std::logic_error("<INVALID NODE>\n");
  }
  //else if ()
}

int main()
{
  size_t size = 0;
  std::cin >> size;
  if (size == 0)
  {
    return 0;
  }
  int* nums = new int[size];
  for (size_t i = 0; i < size; ++i)
  {
    int a = 0;
    std::cin >> a;
    if (!std::cin.good())
    {
      delete[] nums;
      std::cerr << "couldn't count the sequence\n";
      return 1;
    }
    nums[i] = a;
  }
  BiTree< int, std::less< int > >* head = nullptr;
  try
  {
    head = convert< int, std::less< int > >(nums, size);
    delete[] nums;
  }
  catch(const std::bad_alloc&)
  {
    delete[] nums;
    std::cerr << "bad_alloc!\n";
    return 1;
  }
  BiTree< int, std::less< int > >* leftMax = maxLeftTree(head);
  BiTree< int, std::less< int > >* rightMin = minRightTree(head);
  std::cout << leftMax->data << "\n" << rightMin->data << "\n";
  deleteTree(head);
}
