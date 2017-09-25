#include <iostream>
#include <vector>
using namespace std;

class chip  //оƬ��������װ
{
private:
    bool working_well;  //�û�״̬���ɼ���������ĿҪ��
public:
    unsigned id;
    chip(unsigned id, bool working_well):id(id), working_well(working_well) {}
    friend bool test (const chip& A, const chip& B)
    {
        return A.working_well==B.working_well;
    }
};

int TEST_FUNCTION (vector<chip> & V)
{
    if(V.size()==0) return -1; //�˻������û��оƬ��ֻ���������������ʱ��ȡ��������һ����Ϊ�õ�оƬ
    if(V.size()==1) return V[0].id; //�˻������ֻ��һ��оƬ���ǿ϶��Ǻõ�
    if(V.size()==2)
    {
        if(test(V[0],V[1])==false) return -1; //��������ԣ���ζ�ź�оƬ�Ȼ�оƬ��һ���������������
        else return V[0].id; //�����Ϊ�õ�оƬ
    }
    if(V.size()%2) //�������
    {
        vector<chip> VN;
        chip RES = V[0]; //ѡȡһ���������ճ�ż��
        V.erase(V.begin());
        //��ʼ�������
        for(int i=0;i<V.size()/2;i++)
        {
            if(test(V[i],V[i+1]))
                VN.push_back(V[i]); //�������˫�����Ǻõ����ҳ�һ��������һ�εݹ�ļ�����
        }
        int r=TEST_FUNCTION(VN);
        if(r!=-1) return r;
        else return RES.id;
    }
    else  //ż�������ֱ�ӷ����⼴��
    {
        vector<chip> VN;
        for(int i=0;i<V.size()/2;i++)
        {
            if(test(V[i],V[i+1]))
                VN.push_back(V[i]);
        }
        return TEST_FUNCTION(VN);
    }
}

int main()
{
    vector<chip> V;
    int n;
    while(cin>>n)
    {
        for(int i=0;i<n;i++)
        {
            unsigned id; bool is_well;
            cin>>id>>is_well;
            V.push_back(chip(id,is_well));
        }
        int r=TEST_FUNCTION(V);
        cout<<r<<endl;
        V.clear();
    }
}