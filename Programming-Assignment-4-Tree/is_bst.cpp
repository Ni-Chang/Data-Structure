#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

struct Node
{
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTree(const vector<Node>& tree, int t, int min, int max)
{
  if(tree.size()==0)
    return true;
  if(tree[t].key<min||tree[t].key>max)
    return false;
  if(tree[t].left==-1&&tree[t].right==-1)
    return true;
  if(tree[t].left==-1)
    return IsBinarySearchTree(tree, tree[t].right, tree[t].key, max);
  if(tree[t].right==-1)
    return IsBinarySearchTree(tree, tree[t].left, min, tree[t].key);
  return IsBinarySearchTree(tree, tree[t].left, min, tree[t].key) && IsBinarySearchTree(tree, tree[t].right, tree[t].key, max);
}

bool isBST(vector<Node> tree)
{
  return IsBinarySearchTree(tree, 0, INT_MIN, INT_MAX);
}


int main()
{
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i)
  {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (isBST(tree))
  {
    cout << "CORRECT" << endl;
  } 
  else
  {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
