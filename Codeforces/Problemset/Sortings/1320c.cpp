#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I M=2e5;
const I P=2e5;
const I K=448;
const Lli MIN=-1e18;
pair<I,I>weps[N];
pair<I,I>arms[M];
tuple<I,I,I>mons[P];
vector<I>cpss;
Lli vals[K*K];
Lli sums[K];
Lli upps[K];
Lli upp=MIN;
void asn(I i,Lli val){
  vals[i]=max(vals[i],val);
  upp=max(upp,val);
}
void bld(){
  for(I i=0;i<K*K;i++){
    upps[i/K]=max(upps[i/K],vals[i]);
    upp=max(upp,vals[i]);
  }
}
void upd(I i,Lli val){
  for(I j=i;j<(i/K+1)*K;j++){
    vals[j]+=val;
    upps[i/K]=max(upps[i/K],vals[j]);
  }
  for(I j=i/K+1;j<K;j++){
    sums[j]+=val;
    upp=max(upp,upps[j]+sums[j]);
  }
  upp=max(upp,upps[i/K]+sums[i/K]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,p;cin>>n>>m>>p;
  for(I i=0;i<n;i++){
    I a,cst;cin>>a>>cst;
    weps[i]={a,cst};
  }
  for(I i=0;i<m;i++){
    I b,cst;cin>>b>>cst;
    arms[i]={b,cst};
  }
  for(I i=0;i<p;i++){
    I x,y,z;cin>>x>>y>>z;
    mons[i]={x,y,z};
  }
  sort(weps,weps+n);
  sort(arms,arms+m);
  sort(mons,mons+p);
  for(I i=0;i<m;i++){
    auto[b,cst]=arms[i];
    cpss.push_back(b);
  }
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  fill_n(vals,K*K,MIN),fill_n(upps,K,MIN);
  for(I i=0;i<m;i++){
    auto[b,cst]=arms[i];
    asn(lower_bound(cpss.begin(),cpss.end(),b)-cpss.begin(),-cst);
  }
  bld();
  Lli res=MIN;
  for(I i=0,j=0;i<n;i++){
    auto[a,cst]=weps[i];
    for(;j<p;j++){
      auto[x,y,z]=mons[j];
      if(x>=a)break;
      upd(upper_bound(cpss.begin(),cpss.end(),y)-cpss.begin(),z);
    }
    res=max(res,upp-cst);
  }
  printf("%lli\n",res);
}