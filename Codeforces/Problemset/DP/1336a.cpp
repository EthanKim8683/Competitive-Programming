#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

vector<I>adjs[N];
I deps[N];
I sizs[N];
I vals[N];

I dfs(I a,I p=-1,I d=1){
  deps[a]=d++,sizs[a]=1;
  for(auto b:adjs[a])if(b!=p)sizs[a]+=dfs(b,a,d);
  return sizs[a];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs(0);
  for(I i=0;i<n;i++)vals[i]=-(sizs[i]-deps[i]);
  sort(vals,vals+n);
  printf("%lli\n",-accumulate(vals,vals+n-k,(Lli)0));
}