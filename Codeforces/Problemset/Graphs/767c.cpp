#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

const I N=1e6;

vector<I>adjs[N];
I t_arr[N];
I dp[N][2];
I tot=0;
vector<I>cuts;
I r;

void dfs(I a){
  dp[a][0]=t_arr[a];
  for(auto b:adjs[a]){
    dfs(b);
    dp[a][0]+=dp[b][0];
    dp[a][1]+=dp[b][1];
  }
  if(dp[a][0]==tot&&a!=r){
    dp[a][0]=0;
    dp[a][1]++;
    cuts.push_back(a);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I a,t;cin>>a>>t;
    t_arr[i]=t;
    tot+=t;
    if(a)adjs[a-1].push_back(i);
    else r=i;
  }
  if(tot%3)printf("-1\n"),exit(0);
  tot/=3;
  dfs(r);
  if(dp[r][1]<2)printf("-1\n"),exit(0);
  printf("%i %i\n",cuts[0]+1,cuts[1]+1);
  return 0;
}