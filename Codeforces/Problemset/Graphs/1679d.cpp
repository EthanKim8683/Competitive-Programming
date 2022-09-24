#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=2e5;
const I A=1e9+1;
const Lli MAX=1e18;
const Lli MIN=-1e18;

I a_arr[N];
vector<I>adjs[N];
Lli deps[N];
I viss[N];
I n;
Lli k;

Lli dfs(I a,I x){
  if(a_arr[a]>x)return MIN;
  if(viss[a]==1)return MAX;
  if(viss[a]==2)return deps[a];
  viss[a]=1;
  Lli res=1;
  for(auto b:adjs[a])
    res=max(res,dfs(b,x)+1);
  viss[a]=2;
  return deps[a]=res;
}

B chk(I x){
  fill_n(viss,n,0);
  Lli res=0;
  for(I i=0;i<n;i++)
    res=max(res,dfs(i,x));
  return res>=k;
}

I fnd(){
  I l=0,r=A;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk(m))r=m;
    else l=m+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b;
    adjs[a-1].push_back(b-1);
  }
  I res=fnd();
  if(res==A)printf("-1\n");
  else printf("%i\n",res);
  return 0;
}