#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=200000;
const I Q=200000;
pair<I,I>dols[N];
pair<I,I>qrys[Q];
I inds[Q];
I ress[Q];
vector<I>dp;
B cmp1(pair<I,I>a,pair<I,I>b){
  auto[h1,r1]=a;auto[h2,r2]=b;
  return h1==h2?r1>r2:h1<h2;
}
B cmp2(I a,I b){
  return qrys[a]<qrys[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++){
    I r,h;cin>>r>>h;
    dols[i]={h,r};
  }
  for(I i=0;i<q;i++){
    I a,b;cin>>a>>b;
    qrys[i]={b,a};
  }
  sort(dols,dols+n,cmp1);
  iota(inds,inds+q,0);
  sort(inds,inds+q,cmp2);
  I j=0;
  for(I i=0;i<n;i++){
    auto[h,r]=dols[i];
    for(;j<q;j++){
      I k=inds[j];
      auto[b,a]=qrys[k];
      if(b>=h)break;
      ress[k]=upper_bound(dp.begin(),dp.end(),-a)-dp.begin();
    }
    auto it=upper_bound(dp.begin(),dp.end(),-r);
    if(it==dp.end())dp.push_back(-r);
    else*it=-r;
  }
  for(;j<q;j++){
    I k=inds[j];
    auto[b,a]=qrys[k];
    ress[k]=upper_bound(dp.begin(),dp.end(),-a)-dp.begin();
  }
  for(I i=0;i<q;i++)printf("%i\n",ress[i]);
}