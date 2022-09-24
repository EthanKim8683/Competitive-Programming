#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I K=1e5;

vector<pair<I,I>>adjs[2*K];
I sizs[2*K];
Lli maxs[2*K-1];
Lli mins[2*K-1];
I t_arr[2*K-1];
I k;

void dfs(I a,I p=-1){
  for(auto[b,i]:adjs[a])if(b!=p){
    dfs(b,a);
    sizs[a]+=sizs[b];
  }
  for(auto[b,i]:adjs[a])if(b!=p){
    I siz1=sizs[b],siz2=2*k-siz1;
    maxs[i]=(Lli)min(siz1,siz2)*t_arr[i];
    mins[i]=(Lli)(siz1%2)*t_arr[i];
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>k;
    fill_n(sizs,2*k,1);
    for(I i=0;i<2*k;i++)adjs[i].clear();
    for(I i=0;i<2*k-1;i++){
      I a,b,t;cin>>a>>b>>t,a--,b--;
      adjs[a].push_back({b,i});
      adjs[b].push_back({a,i});
      t_arr[i]=t;
    }
    dfs(0);
    Lli res1=0,res2=0;
    for(I i=0;i<2*k-1;i++)
      res1+=mins[i],res2+=maxs[i];
    printf("%lli %lli\n",res1,res2);
  }
}