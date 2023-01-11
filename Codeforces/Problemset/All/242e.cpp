#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I LOGN=17;
const I FIXN=1<<LOGN;
const I L=21;
I a_arr[N];
pair<Lli,Lli>vals[L][2*FIXN];
I dels[L][2*FIXN];
pair<Lli,Lli>apl(pair<Lli,Lli>val,I del){
  if(del%2)swap(val.first,val.second);
  return val;
}
pair<Lli,Lli>cmb(pair<Lli,Lli>a,pair<Lli,Lli>b){
  return{a.first+b.first,a.second+b.second};
}
void pll(I u,I v){
  for(I i=v+FIXN;i>1;i>>=1)vals[u][i>>1]=cmb(apl(vals[u][i],dels[u][i]),apl(vals[u][i^1],dels[u][i^1]));
}
void psh(I u,I v){
  for(I i=LOGN;i>0;i--){
    I j=(v+FIXN)>>i;
    vals[u][j]=apl(vals[u][j],dels[u][j]),dels[u][j<<1]+=dels[u][j],dels[u][j<<1|1]+=dels[u][j],dels[u][j]=0;
  }
}
void asn(I u,I v,pair<Lli,Lli>val){
  vals[u][v+FIXN]=val;
}
void bld(I u){
  for(I i=FIXN-1;i>0;i--)vals[u][i]=cmb(vals[u][i<<1],vals[u][i<<1|1]);
}
void upd(I u,I l,I r,I val){
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)dels[u][i]+=val,i++;
    if(j&1)j--,dels[u][j]+=val;
  }
  pll(u,l),pll(u,r-1);
}
Lli qry(I u,I l,I r){
  psh(u,l),psh(u,r-1);
  pair<Lli,Lli>res={0,0};
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)res=cmb(res,apl(vals[u][i],dels[u][i])),i++;
    if(j&1)j--,res=cmb(res,apl(vals[u][j],dels[u][j]));
  }
  return res.first;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    for(I j=0;j<L;j++){
      I bit=a>>j&1;
      if(bit==0)asn(j,i,{0,1});
      if(bit==1)asn(j,i,{1,0});
    }
  }
  for(I i=0;i<L;i++)bld(i);
  I m;cin>>m;
  while(m--){
    I t;cin>>t;
    if(t==1){
      I l,r;cin>>l>>r,l--;
      Lli res=0;
      for(I i=0;i<L;i++)res+=qry(i,l,r)<<i;
      printf("%lli\n",res);
    }
    if(t==2){
      I l,r,x;cin>>l>>r>>x,l--;
      for(I i=0;i<L;i++)upd(i,l,r,x>>i&1);
    }
  }
}