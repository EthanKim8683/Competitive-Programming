#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=30;

Lli di[]{-1,0,1,0},dj[]{0,-1,0,1};
vector<Lli>adjs[N];
pair<Lli,Lli>ress[N];

void dfs(I a,Lli d,Lli i=0,Lli j=0,I k=-1,I p=-1){
  ress[a]={i,j};
  I l=0;
  for(auto b:adjs[a])if(b!=p){
    l+=l==k;
    dfs(b,d>>1,i+di[l]*d,j+dj[l]*d,(l+2)%4,a);
    l++;
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  for(I i=0;i<n;i++)if(adjs[i].size()>4)printf("NO\n"),exit(0);
  dfs(0,(Lli)1<<(N+1));
  printf("YES\n");
  for(I i=0;i<n;i++){
    auto[a,b]=ress[i];
    printf("%lli %lli\n",a,b);
  }
}