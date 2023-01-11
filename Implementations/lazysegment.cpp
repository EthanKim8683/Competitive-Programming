#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I LOGN=17;
const I FIXN=1<<LOGN;
const I MIN=-1e9;
I a_arr[N];
I vals[2*FIXN],dels[2*FIXN];
void pll(I x){
  for(I i=x+FIXN;i>1;i>>=1)vals[i>>1]=max(vals[i]+dels[i],vals[i^1]+dels[i^1]);
}
void psh(I x){
  for(I i=LOGN;i>0;i--){
    I j=(x+FIXN)>>i;
    vals[j]+=dels[j],dels[j<<1]+=dels[j],dels[j<<1|1]+=dels[j],dels[j]=0;
  }
}
void asn(I i,I val){
  vals[i+FIXN]=val;
}
void bld(){
  for(I i=FIXN-1;i>0;i--)vals[i]=max(vals[i<<1],vals[i<<1|1]);
}
void upd(I l,I r,I val){
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)dels[i]+=val,i++;
    if(j&1)j--,dels[j]+=val;
  }
  pll(l),pll(r-1);
}
I qry(I l,I r){
  psh(l),psh(r-1);
  I res=MIN;
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)res=max(res,vals[i]+dels[i]),i++;
    if(j&1)j--,res=max(res,vals[j]+dels[j]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill_n(vals,2*FIXN,MIN);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)asn(i,a_arr[i]);
  bld();
  I m;cin>>m;
  while(m--){
    I t;cin>>t;
    if(t==1){
      I l,r,x;cin>>l>>r>>x,l--,r--;
      upd(l,r+1,x);
    }
    if(t==2){
      I l,r;cin>>l>>r,l--,r--;
      printf("%i\n",qry(l,r+1));
    }
  }
}