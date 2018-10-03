//
//  main.cpp
//  rope
//
//  Created by xiaonizi on 2017/12/30.
//  Copyright © 2017年 xiaonizi. All rights reserved.
//

#include <cstdio>
#include <string>
#include <iostream>
#include <string>

using namespace std;

class Rope
{
public:
    Rope *left, *right, *parent;
    char letter;
    int lCount;
    Rope(Rope* left, Rope* right, Rope* parent, char letter, int lCount)
    : left(left), right(right), parent(parent), letter(letter), lCount(lCount) {}
};

int n;

Rope* root=NULL;

void createRopeStructure(Rope *&node, Rope *par, string a, int l, int r)
{
    node = new Rope(NULL, NULL, par, 0, (r-l)/2+1);
    if (l!=r)
    {
        int m = (l + r)/2;
        createRopeStructure(node->left, node, a, l, m);
        createRopeStructure(node->right, node, a, m+1, r);
    }
    else
    {
        node->letter = a[l];
    }
    return;
}

Rope* concatenate(Rope* root1, Rope* root2)
{
    if(root1==NULL)
        return root2;
    if(root2==NULL)
        return root1;
    Rope* tmp = new Rope(root1, root2, NULL, 0, root1->lCount);
    root1->parent =tmp;
    root2->parent =tmp;
    Rope* findright=root1;
    while(findright->right!=NULL)
    {
        tmp->lCount+=findright->right->lCount;
        findright=findright->right;
    }
    return tmp;
}

Rope* find(Rope* root, int pos)
{
    if(pos>=n||pos<0)
        return NULL;
    pos++;
    int subt;
    Rope* node=root;
    while(node->letter==0)
    {
        subt=pos-node->lCount;
        if (subt<=0)
        {
            node=node->left;
        }
        else if(subt>0)
        {
            pos-=node->lCount;
            node=node->right;
        }
    }
    return node;
}

bool IsRightChildNeedMerge(Rope* node)
{
    bool flag=0;
    if(node->parent==NULL)
        return flag;
    if(node->parent->right==node&&node->parent->left!=NULL)
    {
        flag=1;
    }
    return flag;
}

bool IsLeftChildNeedMerge(Rope* node)
{
    bool flag=0;
    if(node->parent==NULL)
        return flag;
    if(node->parent->left==node&&node->parent->right!=NULL)
    {
        flag=1;
    }
    return flag;
}


void AdjustlCount(Rope* node)
{
    int subt=node->lCount;
    Rope* findright=node->right;
    while(findright!=NULL)
    {
        subt+=findright->lCount;
        findright=findright->right;
    }
    Rope* serach=node;
    while(serach->parent!=NULL)
    {
        if(serach->parent->left==serach)
            serach->parent->lCount-=subt;
        serach=serach->parent;
    }
    return;
}

Rope* splitrightwithoutmerge(Rope* &node)
{
    while(node!=NULL && node->parent->left==node)
    {
        node=node->parent;
    }
    AdjustlCount(node);
    node->parent->right=NULL;
    node->parent=NULL;
    return node;
}

Rope* splitleftwithoutmerge(Rope* &node)
{
    while(node!=NULL && node->parent->right==node)
    {
        node=node->parent;
    }
    AdjustlCount(node);
    node->parent->left=NULL;
    node->parent=NULL;
    return node;
}

Rope* splitrihgtwithmerge(int pos, Rope* &RightTree)
{
    int initpos=pos;
    Rope* node=find(initpos);
    while(node!=NULL&&IsRightChildNeedMerge(node)==1&&pos<n)
    {
        node=find(++pos);
    }
    if(pos<n)
    {
        RightTree=concatenate(RightTree, splitrightwithoutmerge(node->parent));
    }
    while(pos>initpos)
    {
        node=find(--pos);
        AdjustlCount(node);
        node->parent->right=NULL;
        node->parent=NULL;
        RightTree= concatenate(node,RightTree);
    }
    return RightTree;
}

Rope* splitleftwithmerge(int pos, Rope* &LeftTree)
{
    Rope* node=find(--pos);
    while(node!=NULL&&IsLeftChildNeedMerge(node)==1&&pos>=0)
    {
        AdjustlCount(node);
        node->parent->left=NULL;
        node->parent=NULL;
        LeftTree=concatenate(node, LeftTree);
        node=find(--pos);
    }
    if(pos>=0)
    {
        LeftTree=concatenate(splitleftwithoutmerge(node->parent), LeftTree);
    }
    return LeftTree;
}

void split(Rope* root1, Rope* &LeftTree, Rope* &RightTree, int pos)
{
    if(pos==0)
    {
        RightTree=root1;
        return;
    }
    if(pos==n)
    {
        LeftTree=root1;
        return;
    }
    int cons=root1->lCount;
    if(pos>=cons)
    {
        LeftTree=root1;
        RightTree=splitrihgtwithmerge(pos, RightTree);
    }
    else
    {
        RightTree=root1;
        LeftTree=splitleftwithmerge(pos, LeftTree);
    }
    return;
}


void process(int i, int j, int k)
{
    Rope* left = NULL;
    Rope* middle = NULL;
    Rope* right = NULL;
    Rope* kleft=NULL;
    Rope* kright=NULL;
    split(root, middle, right, j+1);
    split(middle, left, middle, i);
    root=concatenate(left, right);
    split(root, kleft, kright, k);
    root=concatenate(concatenate(kleft, middle), kright);
    return;
}

void printstring(Rope *r)
{
    if (r==NULL)
        return;
    if (r->letter!=0)
        cout << r->letter;
    printstring(r->left);
    printstring(r->right);
    return;
}
void printlcount(Rope *r)
{
    if (r==NULL)
        return;
    printlcount(r->left);
    cout << " ";
    cout << r->lCount;
    cout<< " ";
    printlcount(r->right);
    cout<<"r";
    return;
}
int main()
{
    std::ios_base::sync_with_stdio(0);
    string s;
    cin >> s;
    n=s.size();
    createRopeStructure(root, NULL, s, 0, n-1);
    int actions;
    std::cin >> actions;
    for (int action_index = 0; action_index < actions; ++action_index)
    {
        int i, j, k;
        std::cin >> i >> j >> k;
        process(i, j, k);
    }
    printstring(root);
    /*printlcount(root);
     cout << endl;
     Rope* left = NULL;
     Rope* right = NULL;
     split(root, left, right, 6);
     printstring(left);
     cout << endl;
     printstring(right);
     cout << endl;
     printlcount(left);
     cout << endl;
     printlcount(right);*/
    cout << endl;
    return 0;
}

