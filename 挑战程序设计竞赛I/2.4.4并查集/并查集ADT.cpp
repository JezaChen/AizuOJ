#include <iostream>

using namespace std;
static const int MAX_N = 99999;

int parent [MAX_N]; //����
int rank[MAX_N]; //�߶�
void init(int n)
{
    for(int i=0;i<n;i++)
    {
        rank[i] = 0;
        parent[i] = i; //����Ϊ����ĸ���
    }
}

int find(int x) //��ѯ�õ����ڵ���������
{
    if(parent[x]==x) return x;
    else return find(parent[x]); //�ݹ�Ѱ��
}

void unite(int x, int y) //�ϲ�x��y�ļ���
{
    x = find(x);
    y = find(y);
    if(x==y) return; //����ͬ����ζ��x��y������ͬһ������
    if(rank[x]<rank[y]) parent[x]=y;
    else
    {
        parent[y]=x;
        if(rank[x]==rank[y]) rank[x]++; //��x��y�ĸ߶���ȣ�x�ĸ߶���Ҫ����
    }
}

bool same(int x,int y) //�ж�x��y�Ƿ�������ͬһ������
{
    return find(x)==find(y); 
}

int main()
{
}