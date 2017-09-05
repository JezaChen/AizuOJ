#include <iostream>
#include <algorithm>
using namespace std;

static const int N_MAX=1000;
static const int W_MAX=10000;

int n; //��Ŀ
int A[N_MAX],B[N_MAX]; //A���������飬B���Ѿ��ź������Ŀ
int s;//s��ȫ���������Сֵ
int T[W_MAX+1]; //��������Ӧ���ź����������±�ֵ

int solve()
{
    int ans=0; //�ɱ���
    bool V[N_MAX]; //�Ƿ񱻷��ʹ�
    for(int i=0;i<n;i++)
    {
        B[i]=A[i]; //�����鸴�ƹ�ȥ
        V[i]=false; //��ʼ��
    }
    sort(B,B+n); //����
    for(int i=0;i<n;i++) T[B[i]]=i; //��ʼ��ĳ��ֵ��Ӧ�ź����������±�
    for(int i=0;i<n;i++)
    {
        if(V[i]) continue; //��������ʹ��ˣ�����
        int cur=i; //��ǰ�±�
        int S=0; //S��¼ĳ��Ȧ�����нڵ��ֵ֮��
        int m=W_MAX; //m�����ڼ�¼��Ȧ���нڵ����Сֵ
        int an=0; //anΪȦ��Ԫ����Ŀ
        while(1) //��ʼ����
        {
            V[cur]=true; //��ʼ���
            an++; //��Ŀ��һ
            int v=A[cur]; //vΪ��ǰ�ڵ��ֵ
            m=min(m,v); //��¼Ȧ�ڵ���Сֵ
            S+=v; //��Ȧ���нڵ��ֵ�ܺͼ��ϵ�ǰ�ڵ��ֵ
            cur=T[v]; //������һ���ڵ�Ĳ������ҵ���һ���±�
            if(V[cur]) break; //�����һ���ڵ��Ѿ��������������Ȧ�����еĽڵ��Ѿ�ȫ��������
        }
        ans+=min(S+(an-2)*m,m+S+(an+1)*s);
    }
    return ans;
}
int main()
{
    cin>>n;
    s=W_MAX;
    for(int i=0;i<n;i++)
    {
        cin>>A[i];
        s=min(s,A[i]);
    }
    cout<<solve()<<endl;
}