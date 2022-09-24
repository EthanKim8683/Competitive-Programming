#include<iostream>
#include<cstdio>
#include<vector>
#include<unordered_map>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=3e5;

unordered_map<I,I>adjs[N];
I cons[N];
I fens[N+1+1];
I n;

void upd(I i,I v){
  for(i++;i<=n+1;i+=i&-i)fens[i]+=v;
}

I qry(I i){
  I res=0;
  for(i=max(i,0);i>0;i-=i&-i)res+=fens[i];
  return res;
}

I qry(I l,I r){
  return qry(r)-qry(l);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I p;cin>>n>>p;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x][y]++,adjs[y][x]++;
    cons[x]++,cons[y]++;
  }
  for(I i=0;i<n;i++)upd(cons[i],1);
  Lli res=0;
  for(I i=0;i<n;i++){
    upd(cons[i],-1);
    for(auto[j,c]:adjs[i])if(j>i){
      upd(cons[j],-1);
      upd(cons[j]-c,1);
    }
    res+=qry(p-cons[i],n+1);
    for(auto[j,c]:adjs[i])if(j>i){
      upd(cons[j]-c,-1);
      upd(cons[j],1);
    }
  }
  printf("%lli\n",res);
  return 0;
}