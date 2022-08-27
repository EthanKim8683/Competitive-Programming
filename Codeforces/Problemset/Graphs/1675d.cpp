#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

I p_arr[N];
I inds[N];
vector<I>cons[N];
B viss[N];

void dfs(I a,I r){
  if(viss[a])return;
  viss[a]=true;
  cons[r].push_back(a);
  dfs(p_arr[a],r);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(inds,n,0);
    fill_n(viss,n,false);
    for(I i=0;i<n;i++)cons[i].clear();
    for(I i=0;i<n;i++){I p;cin>>p,p_arr[i]=p-1;}
    for(I i=0;i<n;i++)if(p_arr[i]!=i)inds[p_arr[i]]++;
    I cnt=0;
    for(I i=0;i<n;i++)if(inds[i]==0)cnt++,dfs(i,i);
    printf("%i\n",cnt);
    for(I i=0;i<n;i++){
      auto& con=cons[i];
      if(con.size()){
        reverse(con.begin(),con.end());
        printf("%i\n",cons[i].size());
        for(auto a:cons[i])printf("%i ",a+1);
        printf("\n");
      }
    }
    printf("\n");
  }
  return 0;
}