#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
vector<I>adjs[N];
I sizs[N];
I diss[N];
vector<I>ords;
I ress[N];
Lli res=0;
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p)sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto b:adjs[a])if(b!=p&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
void dfs3(I a,I p=-1,I d=0){
  ords.push_back(a);
  res+=d;
  for(auto b:adjs[a])if(b!=p)dfs3(b,a,d+1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  I a=dfs2(0,dfs1(0));
  for(auto b:adjs[a])dfs3(b,a,1);
  iota(ress,ress+n,0);
  if(n%2==0)ords.push_back(a);
  for(I i=0;i<n/2;i++){
    I a=ords[i],b=ords[i+n/2];
    ress[a]=b,ress[b]=a;
  }
  if(n%2==1)swap(ress[a],ress[(a+1)%n]);
  printf("%lli\n",2*res);
  for(I i=0;i<n;i++)printf("%i ",ress[i]+1);
}