#include <iostream>
#include <set>
#include <vector>
#include <cstdio>
#define MAX_N 100001
#define MAX_M 500001
using namespace std;

set<int> in[MAX_N];
set<int> out[MAX_N];
bool visited[MAX_N];
int N,M;

void delNode(int n)
{
    if ( ! out[n].empty() ) return ;
    
    for (int tmp : in[n]) 
    {
      out[ tmp ].erase( n ) ;
      delNode(tmp);
    }
    
    in[n].clear();

}

void ps(const set<int> &s) {
 string sep("");
 printf("[");
 for (int tmp : s) { printf("%s%d", sep.c_str(), tmp); sep = ","; }
 printf("]\n");
}

//void p() {
//  puts(" --- ");
//  for (int n = 0; n < N; n++) {
//    if (in[n].size() == 0 && out[n].size() == 0) { continue; }
//    ps(in[n]);
//    printf(" -> %d%s -> ", n, visited[n] ? "*" : "");
//    ps(out[n]);
//    puts("");
//  }
//  puts(" --- ");
//}

void reduce() {
  vector<int> ones;
  for (int n = 0; n < N; n++) {
    if (out[n].size() == 1) {
      ones.push_back(n);
      visited[n] = true;
    }
  }

  while (ones.size() > 0) {
    int curr = ones.back();
    ones.pop_back();
    printf("current one is curr = %d\n", curr);

    auto &cO = out[curr];
    //if (cO.size() != 1) { throw runtime_error("BADBADNOTGOOD"); }

    int next = *cO.begin();
    if (curr == next) { continue; }

    auto &cI = in[curr], &nI = in[next];

    nI.erase(curr);
    nI.insert(cI.begin(), cI.end());

    for (int prev : in[curr]) {
      auto &pO = out[prev];

      pO.erase(curr);
      pO.insert(next);
      printf("curr = %d, prev = %d\n", curr, prev);
      if (pO.size() == 1 && !visited[prev]) {
        ones.push_back(prev);
        visited[prev] = true;
      }
    }

    out[curr].clear();
    in[curr].clear();
  }
}

int main() 
{
#ifndef ONLINE_JUDGE
    freopen("data.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif 
    ::std::ios::sync_with_stdio(false); ::std::cin.tie(0); ::std::cout.tie(0);
    
    //cin >> N >> M ;
  scanf("%d %d",&N,&M);
  int a, b;
  for (int i = 0; i < M; i++) {
    scanf("%d %d",&a,&b);
    //  cin >> a >> b ;
    a--; b--;
    out[a].insert(b);
    in[b].insert(a);
    in[a].insert(b);
    out[b].insert(a);
  }

  for (int n = 0; n < N; n++) {
    if ( out[n].empty() ) {
      delNode(n);
    }
  }

  reduce();
  printf("After reduce\n");
  for (int u = 0; u < N; ++u) {
      printf("in[%d]: ", u); ps(in[u]);
      printf("out[%d]: ",u); ps(out[u]);
  }

  int answer = -1;
  bool flag = false;

  for (int n = 0; n < N; n++) 
  {
    if ( ! out[ n ].empty() )
    {
      if (answer == -1 && !flag) 
      {
        flag = true;
        answer = n+1;
      } 
      else 
      {
        answer = -1;
        break;
      }
    }
  }
  
  //cout << answer << endl;
  printf("%d\n", answer);
  
  return 0;
}