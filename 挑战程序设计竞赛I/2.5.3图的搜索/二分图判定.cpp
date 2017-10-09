#include <iostream>
#include <vector>

using namespace std;
static const int MAX_N = 201;

vector<int> G[MAX_N]; //�ڽӾ���
int color[MAX_N]; //�ڵ���ɫ

bool dfs(int u, int c)
{
    color[u]=c; //Ⱦ����ɫc
    //�����ڽӵ�
    for(int i=0;i<G[u].size();i++)
    {
        if(color[G[u][i]]==c) return false; //����ڽӵ�ͬɫ������true����ζ�Ų��Ƕ���ͼ
        if(color[G[u][i]]==0 && !dfs(G[u][i],-c)) return false; //��û�н���Ⱦɫ��Ⱦ���෴������������һ����ɫ�����еݹ�
    }
    return true;
}

void solve(int n)
{
    for(int i=0;i<n;i++)
    {
        if (color[i] == 0)
        {
            if (!dfs(i, 1))
            {
                cout << "NOT BICOLORABLE." << endl;
                return; //�ǵ�Ҫ��ʱ����
            }
        }
    }
    cout<<"BICOLORABLE."<<endl;
}
int main()
{
    int n,m;
    while(cin>>n>>m)
    {
        //init
        for(int i=0;i<n;i++)
        {
            G[i].clear();
            color[i]=0;
        }

        int st, ed;
        for (int i = 0; i < m; i++)
        {
            cin >> st >> ed;
            G[st].push_back(ed);
            G[ed].push_back(st);
        }
        solve(n);
    }
}