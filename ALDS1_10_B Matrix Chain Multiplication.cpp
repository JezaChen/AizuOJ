#include <iostream>
#include <algorithm>
using namespace std;
static const int N=100;

int main()
{
   int n,p[N+1],m[N+1][N+1];  //˵�������ڵ�i����������p[i-1]*p[i]�ģ�m[i][j]ָ���Ǿ���i��j�е����е����Ž�
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>p[i]>>p[i+1];

    //init
    for(int i=1;i<=n;i++) m[i][i]=0;
    for(int l=2;l<=n;l++) //�ӳ���2�ľ�������ʼ����һֱ��������Ϊn
    {
        for(int i=1;i<=n-l+1;i++) //�Ӹó��ȵľ������ĵ�һ������ʼ����
        {
            int j=i+l-1; //ĩ��
            m[i][j]=1<<21; //��ȡһ������ֵ
            for(int k=i;k<j;k++)
            {
                m[i][j]=min(m[i][j],m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j]);  //����ȡ��Сֵ
            }
        }
    }
    cout<<m[1][n]<<endl;
}