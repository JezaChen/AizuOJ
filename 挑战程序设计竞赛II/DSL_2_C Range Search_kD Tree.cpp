#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

class Node  //�ڵ�
{
public:
    int location;
    int p,l,r;
    Node() {}
};

class Point
{
public:
    int id,x,y;
    Point() {}
    Point(int id, int x,int y):id(id),x(x),y(y) {}
    bool operator < (const Point& p)const {return id<p.id; }

    void print()
    {
        printf("%d\n",id);
    }
};

static const int MAX = 1000000;
static const int NIL = -1;

int N; //�ڵ���Ŀ
Point P[MAX]; //�㼯���±��ǽڵ���
Node T[MAX]; //�ڵ��ż���˳�����ǰ���������ʵ�������kd��������
int np;
//������Ҫ�õ��ĺ���
bool lessX(const Point& x, const Point& y) {return x.x<y.x;}
bool lessY(const Point& x, const Point& y) {return x.y<y.y;}

int makeKDTree(int l,int r,int depth)
{
    if(l>=r) return NIL;
    int mid = (l+r)>>1;
    int t=np++; //�ڵ�������
    if(depth%2==0) //ż���߶ȣ�����x
       sort(P+l,P+r,lessX);
    else sort(P+l,P+r,lessY); //�����߶ȣ�����y
    T[t].location=mid;
    //�ݹ鹹����������������
    T[t].l=makeKDTree(l,mid,depth+1);
    T[t].r=makeKDTree(mid+1,r,depth+1); //mmp

    return t; //�ǵ÷��ع����������ĸ��ڵ���
}

void find(int v,int sx,int tx,int sy,int ty,int depth,vector<Point> &ans)
{
    int x=P[T[v].location].x;
    int y=P[T[v].location].y;

    if(sx<=x && x<=tx && sy<=y && y<=ty)  ans.push_back(P[T[v].location]);

    if(depth%2==0) //ż���߶ȣ�����xѰ����������
    {
        if (T[v].l != NIL) {
            if (sx <= x) find(T[v].l, sx, tx, sy, ty, depth + 1, ans);
        }
        if (T[v].r != NIL) {
            if (x <= tx) find(T[v].r, sx, tx, sy, ty, depth + 1, ans);
        }
    }
    else  //�����߶ȣ�����yѰ����������
    {
        if(T[v].l!=NIL)
        {
            if(sy<=y) find(T[v].l,sx,tx,sy,ty,depth+1,ans);
        }
        if(T[v].r!=NIL)
        {
            if(y<=ty) find(T[v].r,sx,tx,sy,ty,depth+1,ans);
        }
    }
}

int main()
{
    int x,y;
    scanf("%d",&N);
    for(int i=0;i<N;i++)
    {
        scanf("%d %d",&x,&y);
        P[i]=Point(i,x,y); //create
        T[i].l=T[i].r=T[i].p=NIL; //init
    }

    np=0; //init
    int root=makeKDTree(0,N,0); //����kd������ȡ���ڵ�

    int q;
    scanf("%d",&q);
    int sx,tx,sy,ty;
    vector<Point> ans;
    for(int i=0;i<q;i++)
    {
        scanf("%d %d %d %d",&sx,&tx,&sy,&ty);
        ans.clear(); //init
        find(root,sx,tx,sy,ty,0,ans); //�Ӹ��ڵ㿪ʼ����
        sort(ans.begin(),ans.end());
        for(int j=0;j<ans.size();j++)
        {
            ans[j].print();
        }
        printf("\n");
    }

    return 0;
}