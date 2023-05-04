#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int n = 18, m = 18;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
vector<pair<int, int>> way;
int a[20][20];

bool inside(int x, int y)
{
    return (0 <= x && x < n && 0 <= y && y < m);
}

void BFS(int a[20][20], vector<pair<int, int>>& way, pair<int, int> start, pair<int, int> target)
{
    int miniWay[20][20] = {};
    pair<int, int> trace[20][20] = {};
    queue<pair<int, int>> q;
    trace[start.first][start.second] = { start.first, start.second };
    miniWay[start.first][start.second] = 1;
    q.push(start);
    while (q.size())
    {
        int u = q.front().first;
        int v = q.front().second;
        q.pop();
        if (u == target.first && v == target.second) break;
        for (int i = 0; i < 4; i++){

            int x = u + dx[i];
            int y = v + dy[i];

            if (inside(x, y) && !miniWay[x][y] && a[x][y] != 1){
                miniWay[x][y] = miniWay[u][v] + 1;
                //cout<<x<<' '<<y<<' '<<u<<' '<<v<<endl;
                trace[x][y] = { u, v };
                q.push({ x, y });
            }
        }
    }
    stack<pair<int, int>> road;
    int u = target.first, v = target.second;
        //cout<<miniWay[u][v]<<endl;
    if (!miniWay[u][v]) return;
    road.push({ u, v });
    while (u != start.first || v != start.second){
        int u1 = u;
        u = trace[u][v].first;
        v = trace[u1][v].second;
        //cout<<u<<' '<<v<<endl;
        road.push({ u, v });
    }
    while (!road.empty()){
        way.push_back(road.top());
        road.pop();
    }
    cout<<endl;
}

int main(){
    //freopen("in.inp", "r", stdin);
    //freopen("out.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    pair<int, int> start, target; // thay cho st1, st2, fi1, fi2
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    cin >> start.first >> start.second >> target.first >> target.second;
    BFS(a, way, start, target);
    for (auto z : way){
        cout << z.first << ' ' << z.second << '\n';
    }
}
