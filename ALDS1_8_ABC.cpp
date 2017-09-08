#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

class BinNode
{
public:
    int data;
    BinNode* parent,*left_child,*right_child;
    BinNode(int d=-1,BinNode* p=NULL,BinNode* l=NULL,BinNode* r=NULL):data(d),parent(p),left_child(l),right_child(r){}
    BinNode* insertAsLc(int u)
    {
        return left_child=new BinNode(u,this);
    }
    BinNode* insertAsRc(int u)
    {
        return right_child=new BinNode(u,this);
    }
    BinNode* succ() //���������ֱ�Ӻ��
    {
        if(right_child) //������Һ���
        {
            BinNode* u=right_child;
            while(u->left_child)
            {
                u=u->left_child; //���������֧����
            }
            return u;
        }
        else //���û���Һ��ӣ����ҵ�������Ϊ�����������������
        {
            BinNode* u=this;
            BinNode* p=u->parent;
            while(u!=p->right_child)
            {
                u=p;
                p=p->parent;
            }
            return p; //���ظ��������
        }
    }
};
void printNode(BinNode* u)
{
    cout<<" "<<u->data;
}
class BST
{
    BinNode* _root;
    BinNode* _hot;
public:
    BST() {_root=_hot=NULL;}
    bool remove(BinNode*& u);
    BinNode*& search(int u);
    BinNode*& searchIn(BinNode* p,int u,BinNode*& hot);
    BinNode* insert(int u);
    bool del(int u);
    void visitLeftbranch(BinNode* u,stack<BinNode*>& S);
    void print_preOrder(); //ǰ��������
    void print_inOrder(); //����������
};
BinNode*& BST::searchIn(BinNode* p,int u,BinNode*& hot)
{
    if(p==NULL) return hot; //�ݹ��
    hot=p; //���_hot�ڵ�
    if(p->data==u) return p;
    return searchIn((u<p->data?p->left_child:p->right_child),u,hot); //�ݹ�ʵ��
}

BinNode*& BST::search(int u)
{
    BinNode* hot=NULL;
    BinNode* t=searchIn(_root,u,hot);
    return t;
   // if(t) return t;
   // return hot; //��������ڸ�ֵ���򷵻����һ�������Ľ��
}

BinNode* BST::insert(int u)
{
    if(!_root) return _root=new BinNode(u); //�����Ͳ�����Ϊ�����
    BinNode* t=search(u);
    if(t->data==u) return t; //Ҫ��֤��Ӧ�Ľ�㲻����
    return (u<t->data?t->insertAsLc(u):t->insertAsRc(u)); //ʵ�ֲ���
}
bool BST::remove(BinNode *&u) //u���뱣֤��Ҷ��
{
    if(u)
    {  //�ж��븸�׵���ϵ
       // u == u->parent->left_child ? (u->parent->left_child = NULL) : (u->parent->right_child = NULL);
       // u->parent = NULL;
       //��ע���ڶ�����������ɾ���������Ѿ��ж����븸�׵���ϵ
        delete u;
        u=NULL;
        return true;
    }
    return false;
}
bool BST::del(int x)
{
    BinNode*& u=search(x);
    BinNode* w=u;
    BinNode* succ=NULL; //ʵ��ɾ��λ�õĽ�����
    if(u->data!=x) return false; //Ҫ��֤������

    //������˫�����������
    if(!u->left_child) //�����������ڵ������
    {
        succ=u->right_child;
        (u->parent->left_child==u)?(u->parent->left_child=succ):(u->parent->right_child=succ);
    }
    else if(!u->right_child) //�����������ڵ������
    {
        succ=u->left_child;
        (u->parent->left_child==u)?(u->parent->left_child=succ):(u->parent->right_child=succ);
    }
    else //˫���������
    {
        w=w->succ(); //�ҵ�ֱ�Ӻ��
        swap(w->data,u->data); //�������ߵ�����
        BinNode* p=w->parent; //ʵ��ɾ�����ĸ���
        ((u==p)?(p->right_child):(p->left_child))=succ=w->right_child;
    }
    //��������ߵĺ��֮��
    _hot=w->parent; //��¼ʵ�ʱ�ɾ�����ĸ���
    if(succ) //��������߲��ǿսڵ�
        succ->parent=_hot; //�Ǿ��ϵ���
    remove(w);
    return true;
}
void BST::visitLeftbranch(BinNode *u, stack<BinNode*> &S)
{
    while(u)
    {
        printNode(u); //�ȷ���
        S.push(u->right_child); //�Һ�����ջ
        u=u->left_child;
    }
}
void BST::print_preOrder()
{
    BinNode* u=_root;
    stack<BinNode*> S;
    while(true)
    {
        visitLeftbranch(u,S);
        if(!S.empty()) {u=S.top();S.pop();}
        else break;
    }
}
void BST::print_inOrder()
{
    stack<BinNode*> S;
    BinNode* u=_root;
    while(true)
    {
        if(u)
        {
            S.push(u);
            u=u->left_child;
        }
        else if(!S.empty())
        {
            u=S.top();S.pop(); //����ջ��
            printNode(u);
            u=u->right_child; //ת���Һ���
        }
        else break;
    }
}
int main()
{
    BST Tree;
    int order_num;
    char order[10];
    int target_num;
    cin>>order_num;
    for(int i=0;i<order_num;i++)
    {
        cin>>order;
        switch(order[0])
        {
            case 'i': cin>>target_num; Tree.insert(target_num);break;
            case 'p': Tree.print_inOrder();cout<<endl;
                      Tree.print_preOrder();cout<<endl;
                      break;
            case 'f': cin>>target_num;
                if(Tree.search(target_num)->data==target_num) cout<<"yes"<<endl;
                else cout<<"no"<<endl;
                break;
            case 'd': cin>>target_num;Tree.del(target_num);
                break;
        }
    }
}