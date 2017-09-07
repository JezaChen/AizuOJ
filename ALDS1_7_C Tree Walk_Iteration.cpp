#include <iostream>
#include <algorithm>
#include <stack>
#define INF -1
#define MAX 26
using namespace std;
struct BinNode
{
    int parent;

    int left_child;
    int right_child;

};
BinNode nodes[MAX];
void print(int u)
{
    cout<<" "<<u;
}
//ǰ����������㷨
void visit_Along_Left_Branch(int u,stack<int>& S)
{
    while(u!=INF)
    {
        print(u);
        S.push(nodes[u].right_child);
        u=nodes[u].left_child; //��������
    }
}

void PreOrder(int r)
{
    stack<int> S;
    while(true)
    {
        visit_Along_Left_Branch(r,S);
        if(S.empty()) break;
        r=S.top();S.pop();
    }
}

void InOrder(int r)
{
    stack<int> S;
    while(true)
    {
        if(r!=INF)
        {
            S.push(r);
            r=nodes[r].left_child;
        }
        else if(!S.empty())
        {
            r=S.top();S.pop();
            print(r);
            r=nodes[r].right_child; //ת���ҽڵ�
        }
        else
            break;
    }
}

void gotoHLVFL(stack<int>& S)
{
    int x;
    while((x=S.top())!=INF)
    {
        if(nodes[x].left_child!=INF) //����������
        {
            if(nodes[x].right_child!=INF)
                S.push(nodes[x].right_child); //�Һ�����ջ
            S.push(nodes[x].left_child); //Ȼ��������ջ
        }
        else
            S.push(nodes[x].right_child); //ʵ���Ȳ����ѣ��Һ�����ջ�������Һ����ǲ��ǿսڵ㣬���ǿսڵ�ͽ���ѭ��
    }
    S.pop(); //�����սڵ�
}

void PostOrder(int r)
{
    stack<int> S; //����ջ
    if(r!=INF) S.push(r); //���ڵ���ջ
    while(!S.empty())
    {
        if(S.top()!=nodes[r].parent) //��ջ���ǵ�ǰ�ڵ�֮��
            gotoHLVFL(S); //��ʱӦ������������Ϊ���������У��ҵ�HLVFL
        r=S.top();S.pop();
        print(r);
    }
}

int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++) nodes[i].parent=nodes[i].left_child=nodes[i].right_child=INF;
    for(int i=0;i<n;i++)
    {
        int j,lc,rc;
        cin>>j>>lc>>rc;
        //�϶���
        nodes[j].left_child=lc;nodes[j].right_child=rc;
        //�ϵ�
        if(lc!=INF) nodes[lc].parent=j;
        if(rc!=INF) nodes[rc].parent=j;
    }
    //�ҵ����ڵ�
    int root;
    for(int i=0;i<n;i++)
        if(nodes[i].parent==INF)
        {
            root=i; break;
        }
    cout<<"Preorder"<<endl;
    PreOrder(root);
    cout<<endl;
    cout<<"Inorder"<<endl;
    InOrder(root);
    cout<<endl;
    cout<<"Postorder"<<endl;
    PostOrder(root);
    cout<<endl;
}