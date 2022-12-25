#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

vector<I>adjs[N];
Lli dp1[N][2]; // 0=subtree size,1=sum distances
Lli dp2[N]; // sum distances

void dfs1(I a,I p=-1){
  dp1[a][0]+=1;
  for(const auto b:adjs[a]){
    if(b!=p){
      dfs1(b,a);
      dp1[a][0]+=dp1[b][0];
      dp1[a][1]+=dp1[b][1]+dp1[b][0];
    }
  }
}

void dfs2(I a,I p=-1){
  for(const auto b:adjs[a]){
    if(b!=p){
      dp2[b]+=dp2[a]+
        dp1[a][1]-(dp1[b][1]+dp1[b][0])+
        (dp1[0][0]-dp1[b][0]);
      dfs2(b,a);
    }
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for(I i=0;i<n-1;i++){
    I a,b;
    cin>>a>>b;
    a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs1(0);
  dfs2(0);
  for (I i=0;i<n;i++)
    printf("%lli ",dp1[i][1]+dp2[i]);
  return 0;
}