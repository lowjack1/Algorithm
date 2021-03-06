/*input
15   
15 14
14 11
11 9
11 13
9 6
6 3
3 4
3 2
3 5
2 1
5 7
5 8
7 10
10 12
3 8
*/

/* Lowest Common Ancestor */

#include <iostream>
#include <vector> 

const int INF = 1e9;
const int N = 100005;
const int LGN = 20;

std::vector < int > v[N];

int dp[LGN][N];
int level[N];

void dfs1(int u)
{
    for(auto x: v[u]) {
        if(x != dp[0][u]) {
            level[x] = level[u] + 1;
            dp[0][x] = u;
            dfs1(x);
        }
    }
}

void preprocess(int n)
{
    level[0] = 0;
    dp[0][0] = 0;
    dfs1(0);
    for(int i = 1; i < LGN; i ++) {
        for(int j = 0; j < n; j ++) {
            dp[i][j] = dp[i - 1][dp[i - 1][j]];
        }
    }
}

int lca(int a, int b)
{
    if(level[a] > level[b]) {
        std::swap(a, b);
    }
    int d = level[b] - level[a];
    for(int i = 0; i < LGN; i ++) {
        if(d & (1 << i)) {
            b = dp[i][b];
        }
    }
    if(a == b) {
        return a;
    }
    for(int i = LGN - 1; i >= 0; i --) {
        if(dp[i][a] != dp[i][b]) {
            a = dp[i][a];
            b = dp[i][b];
        }
    }
    return dp[0][a];
}

/* Used to find distance between two node in a tree */
int dist(int u, int v)
{
    return level[u] + level[v] - 2 * level[lca(u, v)];
}


int main()
{
    int n;
    std::cin >> n;
    
    for(int i = 1; i < n; ++ i) {
        int x, y;
        std::cin >> x >> y;
        x --, y --;
        v[x].push_back(y);
        v[y].push_back(x);
    }

    preprocess(n);
    int src, dest;
    std::cin >> src >> dest;
    std::cout << "LCA of " << src << " and " << dest << " is ";
    std::cout << lca(src, dest);
    return 0;
}

/*  Expected Output
    
    LCA of 3 and 8 is 2

*/