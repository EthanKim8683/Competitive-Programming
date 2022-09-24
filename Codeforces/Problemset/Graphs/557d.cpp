#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=1e5;

vector<I>adjs[N];
I cols[N];
B viss[N];
I cnts[N][2];
I rots[N];

B dfs(I a,I r,I c){
  if(viss[a])return cols[a]==c;
  viss[a]=1;
  cols[a]=c;
  rots[a]=r;
  cnts[r][c]++;
  for(auto b:adjs[a])if(!dfs(b,r,!c))return 0;
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  if(m==0)printf("3 %lli\n",(Lli)n*(n-1)*(n-2)/6),exit(0);
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  for(I i=0;i<n;i++)if(!dfs(i,i,cols[i]))printf("0 1\n"),exit(0);
  Lli res1=0,res2=0;
  for(I i=0;i<n;i++){
    I r=rots[i],c=cols[i];
    cnts[r][c]--;
    res1+=cnts[r][c];
    res2+=(Lli)cnts[r][!c]*(n-2);
  }
  if(res1)printf("1 %lli\n",res1),exit(0);
  printf("2 %lli\n",res2);
}