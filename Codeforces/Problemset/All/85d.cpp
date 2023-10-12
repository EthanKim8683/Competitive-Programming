#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=1e5;
const I LOGN=17;
const I FIXN=1<<LOGN;
pair<I,I>qrys[N];
Lli vals[2*FIXN][5],dels[2*FIXN];
I fens[N+1];
Lli tmps[5];
vector<I>cpss;
I n;
void cmb(Lli*lhss,Lli*rhss,Lli*ress){
  for(I i=0;i<5;i++)ress[i]=lhss[i]+rhss[i];
}
void prm(Lli*vals,I prm){
  if((((prm%=5)+=5)%=5)==0)return;
  copy_n(vals,5,tmps);
  for(I i=0;i<5;i++)vals[(i+prm)%5]=tmps[i];
}
void app(I i,I val){
  prm(vals[i],val);
  if(i<FIXN)dels[i]+=val;
}
void psh(I i){
  for(I j=LOGN;j>=0;j--){
    I k=(i+FIXN)>>j;
    app(k<<1,dels[k]),app(k<<1|1,dels[k]),dels[k]=0;
  }
}
void pll(I i){
  for(i+=FIXN;i>>=1;)cmb(vals[i<<1],vals[i<<1|1],vals[i]),prm(vals[i],dels[i]);
}
void upd1(I i,I j,Lli val){
  psh(i),vals[i+FIXN][j]=val,pll(i);
}
void upd2(I l,I r,I val){
  psh(l),psh(r-1);
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)app(i++,val);
    if(j&1)app(--j,val);
  }
  pll(l),pll(r-1);
}
Lli qry1(I l,I r){
  psh(l),psh(r-1);
  Lli res=0;
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)res+=vals[i++][2];
    if(j&1)res+=vals[--j][2];
  }
  return res;
}
void upd3(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry2(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
void add(I x){
  upd1(x,qry2(x)%5,cpss[x]),upd2(x+1,n,1),upd3(x+1,1);
}
void del(I x){
  upd1(x,qry2(x)%5,0),upd2(x+1,n,-1),upd3(x+1,-1);
}
Lli sum(){
  return qry1(0,n);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++){
    S t;cin>>t;
    if(t=="add"){
      I x;cin>>x;
      qrys[i]={0,x};
      cpss.push_back(x);
    }
    if(t=="del"){
      I x;cin>>x;
      qrys[i]={1,x};
      cpss.push_back(x);
    }
    if(t=="sum"){
      qrys[i]={2,-1};
    }
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++){
    auto[t,x]=qrys[i];
    if(t==2)continue;
    x=lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
    qrys[i]={t,x};
  }
  for(I i=0;i<n;i++){
    auto[t,x]=qrys[i];
    if(t==0)add(x);
    if(t==1)del(x);
    if(t==2)printf("%lli\n",sum());
  }
}