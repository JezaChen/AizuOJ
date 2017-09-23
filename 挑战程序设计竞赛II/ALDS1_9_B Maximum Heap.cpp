#include <iostream>
#include <vector>
#include <algorithm>
#define In_Heap(n,i)  ((-1)<(i))&&((i)<(n)) //�ж�PQ[i]�Ƿ�Ϸ�
#define lt(i,j) ((i)>(j)) //���ȼ���Ŀǰȡ��������
#define Parent(i)  ((i-1)>>1) //�󸸽ڵ�
#define Last_Internal(n)  Parent(n-1) //���һ���ڲ��ڵ㣬Ҳ����ĩ�ڵ�ĸ���
#define LChild(i) (((i)<<1)+1) //����
#define RChild(i) ((1+(i))<<1) //�Һ���
#define Parent_Valid(i) (0<i) //�ڵ�i�Ƿ��и��ף�ֻҪ���Ǹ��ڵ㶼���и��׵�
#define LChildValid(n,i)   In_Heap(n,LChild(i)) //�жϽڵ�i�Ƿ�������
#define RChildValid(n,i)    In_Heap(n,RChild(i)) //�жϽڵ�i�Ƿ����Һ���
#define Bigger(PQ,i,j)  (lt(PQ[i],PQ[j])?i:j) //�ж�������
#define ProperParent(PQ,n,i) \
((RChildValid(n,i))?((LChildValid(n,i))?\
Bigger(PQ,Bigger(PQ,i,LChild(i)),RChild(i)):Bigger(PQ,i,RChild(i))):\
((LChildValid(n,i))?Bigger(PQ,i,LChild(i)):(i)))//����Floyd�㷨����ýڵ��Լ��������Ӽ�������


using namespace std;
class Heap
{
public:
    vector<int> V;
    int percolate_Up(int pos); //�����㷨
    int percolate_Down(int pos); //�����㷨
    //�������㷨�ķ���ֵ�����յ�λ��
    void insert(int u); //�������
    int del_Max(int u); //ɾ����ֵ
    int get_Max() {return V[0];} //��ȡ���/��Сֵ
    void heapify(); //�����㷨
};

int Heap::percolate_Up(int pos) //�����㷨
{
    while(Parent_Valid(pos)) //ֻҪ�ڵ����и���
    {
        int parent_pos=Parent(pos); //��¼���׽ڵ��λ��
        if(lt(V[parent_pos],V[pos])) break; //ֻҪ˳����ˣ�������ѭ��
        swap(V[parent_pos],V[pos]); //���򽻻�λ�ã�������һ�ֵ�ѭ��
        pos=parent_pos; //���µ�ǰ�ڵ��λ��
    }
    return pos;
}

int Heap::percolate_Down(int pos) //�����㷨
{
    int j; //��ʱ����
    while(pos!=(j=ProperParent(V,V.size(),pos))) //������ʺϵĸ��ײ��ǵ�ǰ�ڵ㣬����Ҫ��һ�����˲���
    {
        swap(V[pos],V[j]); //����λ��
        pos=j; //���µ�ǰ�ڵ��λ��
    }
    return pos;
}

void Heap::insert(int u)
{
    V.push_back(u); //������׷��u
    percolate_Up(V.size()-1); //����һ�����˲���
}

int Heap::del_Max(int u)
{
    int temp=V[0];
    swap(V[0],V[V.size()-1]); //���ڵ��ĩ�ڵ㽻��λ��
    V.pop_back(); //����ĩ�ڵ㣬�൱��ɾ����ԭ�ȵ�ͷ���
    percolate_Down(0); //��ͷ���������˲���
    return temp;

}

void Heap::heapify() //Floyd����
{
    for(int i=Last_Internal(V.size());In_Heap(V.size(),i);i--)
    {
        percolate_Down(i); //����ÿһ���ڲ��ڵ㶼����һ�����˲���
    }
}

int main()
{
    int n;
    while(cin>>n)
    {
        Heap heap;
        for(int i=0;i<n;i++)
        {
            int j;cin>>j;
            heap.V.push_back(j);
        }
        heap.heapify();
        for(int i=0;i<n;i++)
            cout<<" "<<heap.V[i];
        cout<<endl;
    }
}