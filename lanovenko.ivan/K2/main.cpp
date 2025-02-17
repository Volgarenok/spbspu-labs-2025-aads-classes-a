#include <iostream>

struct FwdList
{
  int value;
  FwdList* next;
};

FwdList* Insert(FwdList* head, size_t n, size_t k)
{
  FwdList* subhead = head;
  for (size_t i = 1; i < n; i++)
  {
    subhead = subhead->next;
  }
  for (size_t i = 0; i < k; i++)
  {
    FwdList* node = new FwdList{ subhead->value, nullptr };
    node->next = subhead->next;
    subhead->next = node;
  }
  return subhead;
}


void deleteList(FwdList* head)
{
  while (head != nullptr)
  {
    FwdList* subhead = head;
    head = head->next;
    delete subhead;
  }
}


FwdList* createList()
{
  FwdList* head = nullptr;
  FwdList* subhead = nullptr;
  try
  {
    head = new FwdList{ 0,nullptr };
    subhead = head;
    for (int i = 1; i < 10; i++)
    {
      head->next = new FwdList{ i, nullptr };
      head = head->next;
    }
  }
  catch (const std::bad_alloc& e)
  {
    deleteList(head);
    throw;
  }
  return subhead;
}

int main()
{
  int* array = new int[10000] {};
  std::size_t capacity = 0;
  int a = 0;
  while (std::cin >> a && !std::cin.eof())
  {
    array[capacity++] = a;
  }
  if (capacity % 2 != 0)
  {
    capacity--;
  }
  FwdList* buf = nullptr;
  try
  {
    buf = createList();
  }
  catch (const std::bad_alloc& e)
  {
    delete[] array;
    return 1;
  }
  for (size_t i = 0; i < capacity; i += 2)
  {
    try
    {
      if (array[0] > 0 && array[0] < 11)
      {
        Insert(buf, array[i], array[i + 1]);
      }
      else
      {
        std::cerr << "Bad Index\n";
        delete[] array;
        deleteList(buf);
        return 1;
      }
    }
    catch (const std::bad_alloc& e)
    {
      delete[] array;
      deleteList(buf);
      return 1;
    }
  }
  FwdList* temporary = buf;
  std::cout << temporary->value;
  for (temporary = temporary->next; temporary != nullptr; temporary = temporary->next)
  {
    std::cout << " " << temporary->value;
  }
  std::cout << '\n';
  delete[] array;
  deleteList(buf);
}

