#include <iostream>

using namespace std;
static const int MAX_N = 399999;

int parent [MAX_N]; //����
int Rank[MAX_N]; //�߶�

void init(int n)
{
    for(int i=0;i<n;i++)
    {
        Rank[i] = 0;
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
    if(Rank[x]<Rank[y]) parent[x]=y;
    else
    {
        parent[y]=x;
        if(Rank[x]==Rank[y]) Rank[x]++; //��x��y�ĸ߶���ȣ�x�ĸ߶���Ҫ����
    }
}

bool same(int x,int y) //�ж�x��y�Ƿ�������ͬһ������
{
    return find(x)==find(y);
}

int N,K;
static const int MAX_K = 1000001;

void solve()
{
    cin>>N>>K;
    //init
    init(3*N);
    int order, x, y;
    int ans=0;
    for(int i=0;i<K;i++)
    {
        cin>>order>>x>>y;
        if(x>N||y>N) //��Ų�����Ҫ��
        {
            ans++;
            continue;
        }
        if(order==1) //��һ�������x��yΪͬһ�� same(x,y)
        {
            //�����ж϶Բ���
            if(same(x,y+N)||same(x,y+N*2)) //x��A��y��B����x��A��y��C
            {
                ans++;
            }
            else
            {
                unite(x,y);
                unite(x+N,y+N);
                unite(x+2*N,y+2*N);
            }
        }
        else //�ڶ��������x��y same(x,y+N)
        {
            if(same(x,y)||same(x,y+2*N))  ans++; //��x��A��y��A����x��A��y��C
            else
            {
                unite(x,y+N);
                unite(x+N,y+N*2);
                unite(x+N*2,y);
            }
        }
    }
    cout<<ans<<endl;
}
int main()
{
    solve();
    return 0;
}