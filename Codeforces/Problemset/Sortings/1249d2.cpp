#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I X=2e5;
const I LOGX=18;
const I FIXX=1<<LOGX;
pair<I,I>segs[N];
I vals[2*FIXX],upds[2*FIXX];
I inds[N];
vector<I>ress;
B cmp(I a,I b){
  return segs[a]<segs[b];
}
void app(I i,I upd){
  vals[i]+=upd;
  if(i<FIXX)upds[i]+=upd;
}
void pll(I i){
  for(i+=FIXX;i>>=1;)vals[i]=max(vals[i<<1],vals[i<<1|1])+upds[i];
}
void psh(I i){
  for(I j=LOGX;j>=0;j--){
    I k=(i+FIXX)>>j;
    if(upds[k])app(k<<1,upds[k]),app(k<<1|1,upds[k]),upds[k]=0;
  }
}
void upd(I l,I r,I upd){
  psh(l),psh(r-1);
  for(I i=l+FIXX,j=r+FIXX;i<j;i>>=1,j>>=1){
    if(i&1)app(i++,upd);
    if(j&1)app(--j,upd);
  }
  pll(l),pll(r-1);
}
I qry(I l,I r){
  psh(l),psh(r);
  I res=0;
  for(l+=FIXX,r+=FIXX;l<r;l>>=1,r>>=1){
    if(l&1)res=max(vals[l++],res);
    if(r&1)res=max(res,vals[--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r,l--,r--;
    segs[i]={r,l};
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++){
    auto[r,l]=segs[inds[i]];
    qry(l,r+1)==k?ress.push_back(inds[i]):upd(l,r+1,1);
  }
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i ",i+1);
}