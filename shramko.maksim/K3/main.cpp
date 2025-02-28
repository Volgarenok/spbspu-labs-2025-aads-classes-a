#include <iostream>
#include <string>

template < class T >
struct List {
  T data;
  List< T > * next;
};

void rmArr(int** arr, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    delete[] arr[i];
  }
  delete[] arr;
}

void rmList(List< int > * head)
{
  while (head != nullptr)
  {
    List< int > * temp = head;
    head = head->next;
    delete temp;
  }
}

void rmList(List< List< int > * > * head)
{
  while (head != nullptr)
  {
    List< int > * temp = head->data;
    rmList(temp);
    List< List< int > * > * tempHead = head;
    head = head->next;
    delete tempHead;
  }
}

template< class T >
size_t countEven(const List< List< T > * > * head)
{
  size_t res = 0;
  const List< List< int > * > * tail = head;
  while (tail != nullptr)
  {
    List< T > * temp = tail->data;
    while (temp != nullptr)
    {
      if ((temp->data % 2) == 0)
      {
        res += 1;
      }
      temp = temp->next;
    }
    tail = tail->next;
  }

  return res;
}

template< class T >
size_t countOdd(const List< List< T > * > * head)
{
  size_t res = 0;
  const List< List< int > * > * tail = head;
  while (tail != nullptr)
  {
    List< T > * temp = tail->data;
    while (temp != nullptr)
    {
      if ((temp->data % 2) != 0)
      {
        res += 1;
      }
      temp = temp->next;
    }
    tail = tail->next;
  }

  return res;
}

template< class T, class C>
size_t count(const List< List< T > * > * head, C word)
{
  if (word)
  {
    return countEven(head);
  }
  else
  {
    return countOdd(head);
  }
}

List< int > * convert(const int* arr, size_t n)
{
  List< int > * head = new List< int >{ arr[0], nullptr };
  List< int > * tail = head;
  for (size_t i = 1; i < n; i++)
  {
    List< int > * temp = nullptr;
    try
    {
      temp = new List< int >{ arr[i], nullptr };
    }
    catch (std::bad_alloc&)
    {
      rmList(head);
      throw;
    }
    tail->next = temp;
    tail = temp;
  }

  return head;
}

List< List < int > * > * convert(const int* const* d, size_t m, const size_t* n)
{
  if (m == 0)
  {
    return nullptr;
  }

  List< List < int > * > * head = new List< List < int > * >{ convert(d[0], n[0]), nullptr };
  List< List < int > * > * tail = head;

  for (size_t i = 1; i < m; i++)
  {
    List< List < int > * > * temp = nullptr;
    try
    {
      temp = new List< List < int > * >{ convert(d[i], n[i]), nullptr };
    }
    catch (std::bad_alloc&)
    {
      rmList(head);
      throw;
    }
    tail->next = temp;
    tail = temp;
  }

  return head;
}

int main()
{
  size_t m = 0;

  std::cin >> m;
  if (std::cin.fail())
  {
    std::cerr << "Error: Main -> cin m.\n";
    return 1;
  }

  int** arr = nullptr;
  try
  {
    arr = new int*[m];
  }
  catch (const std::bad_alloc()&)
  {
    std::cerr << "Error: main -> arr bad_alloc\n";
    return 1;
  }

  size_t* size = nullptr;
  try
  {
    size = new size_t[m];
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Error: main -> size bad_alloc\n";
    rmArr(arr, m);
    return 1;
  }

  for (size_t i = 0; i < m; i++)
  {
    std::cin >> size[i];
    if (std::cin.fail())
    {
      std::cerr << "Error: Main -> cin size.\n";
      rmArr(arr, i);
      delete[] size;
      return 1;
    }

    try
    {
      arr[i] = new int[size[i]];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Error: main -> arr bad_alloc\n";
      rmArr(arr, i);
      delete[] size;
      return 1;
    }

    for (size_t j = 0; j < size[i]; j++)
    {
      int temp = 0;
      std::cin >> temp;
      if (std::cin.fail())
      {
        std::cerr << "Error: main -> cin arr[i][j].\n";
        rmArr(arr, i + 1);
        delete[] size;
        return 1;
      }
      arr[i][j] = temp;
    }
  }

  List< List < int > * > * head = nullptr;
  try
  {
    head = convert(arr, m, size);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Error: main -> convert bad_alloc\n";
    rmArr(arr, m);
    delete[] size;
    return 1;
  }

  std::string word = "";
  std::cin >> word;
  if (word == "even")
  {
    std::cout << count(head, 1);
  }
  else if (word == "odd")
  {
    std::cout << count(head, 0);
  }
  else
  {
    std::cout << count(head, 0) << " " << count(head, 1);
  }
  std::cout << "\n";

  rmArr(arr, m);
  delete[] size;
  rmList(head);
}
