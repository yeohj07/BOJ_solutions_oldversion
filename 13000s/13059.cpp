#include <cstdio>
#include <vector>
#define MAX 200001
using namespace std;

int Parent[MAX][20], Dist[MAX][20] = {}, Depth[MAX], H = 0;
vector<int> Line[MAX];

void setParent(int Par, int Node, int Dep) {
    if(!Line[Node].size()) return;
    Parent[Node][0] = Par;
    Dist[Node][0] = 1;
    Depth[Node] = Dep;
    for(int i=0; i<Line[Node].size(); i++)
        if(Line[Node][i] != Par) setParent(Node, Line[Node][i], Dep+1);
}

int findLCADis(int A, int B) {
    int Dis = 0;
    if(Depth[A] != Depth[B]) {
        if(Depth[A] < Depth[B]) swap(A, B);
        int Diff = Depth[A] - Depth[B];
        for(int i=0; Diff>0; i++) {
            if(Diff%2) {
                Dis += Dist[A][i];
                A = Parent[A][i];
            }
            Diff >>= 1;
        }
    }
    if(A != B) {
        for(int i=H; i>=0; i--)
            if(Parent[A][i] != 0 && Parent[A][i] != Parent[B][i]) {
                Dis += (Dist[A][i] + Dist[B][i]);
                A = Parent[A][i];
                B = Parent[B][i];
            }
        Dis += (Dist[A][0] + Dist[B][0]);
        A = Parent[A][0];
    }
    return Dis;
}

int main() {
    int N, M, A, B, temp;
    long long Sum = 0;
    scanf("%d", &N);
    temp = N;
    while(temp > 1) {
        temp /= 2;
        H++;
    }
    for(int i=0; i<N-1; i++) {
        scanf("%d %d", &A, &B);
        Line[A].push_back(B);
        Line[B].push_back(A);
    }
    setParent(0, 1, 0);
    for(int i=1; i<=H; i++)
        for(int j=2; j<=N; j++)
            if(Parent[j][i-1]) {
                Parent[j][i] = Parent[Parent[j][i-1]][i-1];
                Dist[j][i] = Dist[j][i-1] + Dist[Parent[j][i-1]][i-1];
            }
    for(int i=1; i<=N; i++)
        for(int j=i*2; j<=N; j+=i)
            Sum += (long long)(findLCADis(i, j)+1);
    printf("%lld", Sum);
}
