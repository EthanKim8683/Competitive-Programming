#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
pair<I,I>prbs[N];
vector<I>curs;
I n,k;
B cmp(I a,I b){
  return prbs[a].second<prbs[b].second;
}
void run(I x){
  curs.clear();
  for(I i=0;i<n;i++){
    auto[a,t]=prbs[i];
    if(a>=x)curs.push_back(i);
  }
  sort(curs.begin(),curs.end(),cmp);
}
B chk(I x){
  run(x);
  if(curs.size()<x)return 0;
  I tot=0;
  for(I i=0;i<x;i++)tot+=prbs[curs[i]].second;
  return tot<=k;
}
I fnd(){
  I l=0,r=n;
  while(l<r){
    I m=l+(r-l+1)/2;
    chk(m)?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>k;
  for(I i=0;i<n;i++){
    I a,t;cin>>a>>t;
    prbs[i]={a,t};
  }
  I x=fnd();
  run(x);
  printf("%i\n%i\n",x,x);
  for(I i=0;i<x;i++)printf("%i ",curs[i]+1);
}