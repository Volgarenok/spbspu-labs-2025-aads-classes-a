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
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & value, BiTree< T, Cmp > ** result)
{
  *result = find(root, value, root->cmp);
}

template< class T, class Cmp >
std::ostream & outputBiTree(BiTree< T, Cmp > * root);

template< class T, class Cmp >
BiTree< T , Cmp > * convert(const T * array, size_t size, Cmp cmp)
{
  if (!array)
  {
    return nullptr;
  }
  BiTree< T, Cmp > * root = new BiTree< T, Cmp >{ array[0], cmp, nullptr, nullptr, nullptr };
  try
  {
    for (size_t i = 1; i < size; i++)
    {
      auto temp = root;
      while (temp->left || temp->right)
      {
        if (cmp(array[i], temp->data) && temp->left)
        {
          temp = temp->left;
        }
        else if (!cmp(array[i], temp->data) && temp->right)
        {
          temp = temp->right;
        }
        else
        {
          break;
        }
      }
      if (cmp(array[i], temp->data))
      {
        temp->left = new BiTree< T, Cmp >{ array[i], cmp, nullptr, nullptr, temp };
      }
      else
      {
        temp->right = new BiTree< T, Cmp >{ array[i], cmp, nullptr, nullptr, temp };
      }
    }
  }
  catch(const std::bad_alloc & e)
  {
    clearBiTree(root);
    throw;
  }
  return root;
}

template< class T, class Cmp >
BiTree< T, Cmp > * find(BiTree< T, Cmp > * root, const T & value, Cmp cmp)
{
  if (!root)
  {
    return root;
  }
  while (root->data != value)
  {
    if (cmp(value, root->data) && root->left)
    {
      root = root->left;
    }
    else if (!cmp(value, root->data) && root->right)
    {
      root = root->right;
    }
    else
    {
      root = nullptr;
      break;
    }
  }
  return root;
}

template< class T, class Cmp >
void clearBiTree(BiTree< T, Cmp > * root)
{
  if (!root)
  {
    return;
  }
  while (root->left)
  {
    root = root->left;
  }
  while (root->parent)
  {
    auto todelete = root;
    root = root->parent;
    delete todelete;
  }
  while (root->right)
  {
    auto todelete = root;
    root = root->right;
    delete todelete;
  }
  delete root;
}

int main()
{
  size_t sequence_length = 0;
  if (!(std::cin >> sequence_length))
  {
    std::cerr << "ERROR: Invalid argument" << "\n";
    return 1;
  }
  else if (std::cin.eof())
  {
    std::cerr << "End of file" << "\n";
    return 2;
  }
  int * elements_array = nullptr;
  BiTree< int, std::less< int > > * root = nullptr;
  try
  {
    if (sequence_length)
    {
      elements_array = new int[sequence_length];
    }
    else
    {
      elements_array = nullptr;
    }
    size_t i = 0;
    while(i != sequence_length && std::cin && !std::cin.eof())
    {
      std::cin >> elements_array[i++];
    }
    if (!std::cin)
    {
      throw std::invalid_argument("ERROR: Invalid argument");
    }
    else if (std::cin.eof())
    {
      throw std::logic_error("End of file");
    }
    root = convert(elements_array, sequence_length, std::less< int >());
  }
  catch (const std::invalid_argument & e)
  {
    clearBiTree(root);
    delete[] elements_array;
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::logic_error & e)
  {
    clearBiTree(root);
    delete[] elements_array;
    std::cerr << e.what() << "\n";
    return 2;
  }
  catch (const std::bad_alloc & e)
  {
    clearBiTree(root);
    delete[] elements_array;
    std::cerr << "ERROR: Out of memory" << "\n";
    return 3;
  }
  int number = 0;
  while (!std::cin.eof())
  {
    std::cin >> number;
    if (std::cin.eof())
    {
      break;
    }
    else if (!std::cin)
    {
      outputBiTree(root);
      clearBiTree(root);
      delete[] elements_array;
      std::cerr << "ERROR: Invalid argument";
      std::cerr << "\n";
      return 4;
    }
    BiTree< int, std::less< int > > * extracted = nullptr;
    root = extract(root, number, std::addressof(extracted));
    if (extracted)
    {
      delete extracted;
    }
    else
    {
      std::cout << "<INVALID NODE>";
      std::cout << "\n";
    }
  }
}
