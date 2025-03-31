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
BiTree< T, Cmp >* getTree(std::istream& in)
{
   
}

int main()
{
  
}
