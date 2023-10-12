#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
pair<I,I>nams[N];
I fens[N+2];
vector<I>accs[N];
I cnts[N];
I n;
void upd(I i,I val){
  for(;i<=n+1;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
void rem(I i){
  auto[x,y]=nams[i];
  if(cnts[x]!=-1)upd(cnts[x]+1,-1),cnts[x]--,upd(cnts[x]+1,1);
  if(cnts[y]!=-1)upd(cnts[y]+1,-1),cnts[y]--,upd(cnts[y]+1,1);
}
void add(I i){
  auto[x,y]=nams[i];
  if(cnts[x]!=-1)upd(cnts[x]+1,-1),cnts[x]++,upd(cnts[x]+1,1);
  if(cnts[y]!=-1)upd(cnts[y]+1,-1),cnts[y]++,upd(cnts[y]+1,1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I p;cin>>n>>p;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y,x--,y--;
    nams[i]={x,y};
    accs[x].push_back(i);
    accs[y].push_back(i);
    cnts[x]++,cnts[y]++;
  }
  for(I i=0;i<n;i++)upd(cnts[i]+1,1);
  Lli res=0;
  for(I i=0;i<n;i++){
    I cnt=cnts[i];
    upd(cnts[i]+1,-1),cnts[i]=-1;
    for(auto j:accs[i])rem(j);
    res+=qry(n+1)-qry(max(p-cnt,0));
    for(auto j:accs[i])add(j);
  }
  printf("%lli\n",res);
}