#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=1e9+7;
Lli v_arr[N];
vector<I>adjs[N];
Lli sizs[N][2];
Lli sums[N][2];
Lli res=0;
void dfs(I a,I p=-1){
  sizs[a][1]=1;
  sums[a][1]=v_arr[a];
  (res+=v_arr[a])%=MOD;
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    (res+=2*(sums[a][0]*sizs[b][1]+sizs[a][0]*sums[b][1]))%=MOD;
    (res+=2*(sums[a][1]*sizs[b][0]+sizs[a][1]*sums[b][0]))%=MOD;
    (sums[a][0]+=sums[b][1]+sizs[b][1]*-v_arr[a])%=MOD;
    (sums[a][1]+=sums[b][0]+sizs[b][0]*v_arr[a])%=MOD;
    sizs[a][0]+=sizs[b][1];
    sizs[a][1]+=sizs[b][0];
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>v_arr[i];
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs(0);
  printf("%lli\n",(res+MOD)%MOD);
}
/*
we can use dynamic programming on trees
 
note that for any (u, v) with even distance, A(u, v) = -A(v, u), meaning even
length paths don't contribute to the sum
 
meanwhile, A(u, v) = A(v, u) for (u, v) with odd distance, meaning odd length
paths are counted twice
*/