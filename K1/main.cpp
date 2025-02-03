#include <iostream>
struct BiList 
{
  int value;
  BiList * prev, * next;
};

int main()
{
  int massive[10] = {};
  for (size_t i = 0; i < 10; i++)
  {
    std::cin >> massive[i];
  }
}