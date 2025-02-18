#include <iostream>

struct FwdList
{
  int value;
  FwdList * next;
};

FwdList * toFwdList(const int * arr, size_t size);
void clearFwdList(FwdList * head);
void duplicateElements(FwdList * head, int index, const int * arr, int count);
void print(std::ostream & out, FwdList * head);

int main()
{
  constexpr size_t size = 10;
  int index = 0;
  int count = 0;
  FwdList * head = nullptr;
  const int arr[size] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  try
  {
    head = toFwdList(arr, size);
  }
  catch(std::bad_alloc &)
  {
    return 1;
  }
  while (std::cin >> index && !std::cin.eof())
  {
    if (index > 10 || index < 1)
    {
      clearFwdList(head);
      std::cerr << "out of range";
      return 1;
    }
    if (std::cin >> count)
    {
      try
      {
        duplicateElements(head, index, arr, count);
      }
      catch (const std::exception & e)
      {
        return 1;
      }
    }
    else
    {
      break;
    }
  }
  print(std::cout, head);
  std::cout << "\n";
}

FwdList * toFwdList(const int * arr, size_t size)
{
  FwdList * head = new FwdList{arr[0], nullptr};
  FwdList * subhead = head;
  for (size_t i = 1; i < size; ++i)
  {
    FwdList * record = nullptr;
    try
    {
      record = new FwdList{arr[i], nullptr};
    }
    catch (const std::bad_alloc &)
    {
      clearFwdList(head);
      throw;
    }
    subhead->next = record;
    subhead = record;
  }
  return head;
}

void clearFwdList(FwdList * head)
{
  FwdList * subhead = head;
  while (subhead != nullptr)
  {
    FwdList * next = subhead->next;
    delete subhead;
    subhead = next;
  }
}

void duplicateElements(FwdList * head, int index, const int * arr, int count)
{
  FwdList * subhead = head;
  while(subhead->value != arr[index - 1])
  {
    subhead = subhead->next;
  }
  FwdList * next = subhead->next;
  for(int i = 0; i < count; i++)
  {
    FwdList * record = nullptr;
    try
    {
      record = new FwdList{arr[index - 1], nullptr};
    }
    catch (const std::bad_alloc &)
    {
      clearFwdList(head);
      throw;
    }
    subhead->next = record;
    subhead = record;
  }
  subhead->next = next;
}

void print(std::ostream & out, FwdList * head)
{
  FwdList * subhead = head;
  while (subhead->next)
  {
    out << subhead->value << " ";
    subhead = subhead->next;
  }
  out << subhead->value;
}
