#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I x_arr[N];
vector<pair<I,Lli>>upds;
Lli ps[N+1];
I siz;
I n;
void bld(){
  for(I i=0;i<n;i++)ps[i+1]=ps[i]+x_arr[i];
}
void upd(I i,I v){
  upds.push_back({i,v-x_arr[i]});
  x_arr[i]=v;
}
Lli qry(I l,I r){
  if(upds.size()>=siz)bld(),upds.clear();
  Lli res=ps[r]-ps[l];
  for(auto[i,v]:upds)if(i>=l&&i<r)res+=v;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  siz=sqrt(n);
  bld();
  while(q--){
    I t;cin>>t;
    if(t==1){
      I k,u;cin>>k>>u,k--;
      upd(k,u);
    }
    if(t==2){
      I a,b;cin>>a>>b,a--,b--;
      printf("%lli\n",qry(a,b+1));
    }
  }
}