#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=35000;
const I K=50;
const I LOGN=16;
const I FIXN=1<<LOGN;
const I MIN=-1e9;
I a_arr[N];
I vals[K+1][2*FIXN],dels[K+1][2*FIXN];
I lats[N+1];
void app(I t,I i,I val){
  vals[t][i]+=val;
  if(i<FIXN)dels[t][i]+=val;
}
void psh(I t,I i){
  for(I j=LOGN-1;j>0;j--){
    I k=(i+FIXN)>>j;
    app(t,k<<1,dels[t][k]),app(t,k<<1|1,dels[t][k]),dels[t][k]=0;
  }
}
void pll(I t,I i){
  for(i+=FIXN;i>>=1;)vals[t][i]=max(vals[t][i<<1],vals[t][i<<1|1])+dels[t][i];
}
void asn(I t,I i,I val){
  vals[t][i+FIXN]=val;
}
void bld(I t){
  for(I i=FIXN-1;i>0;i--)vals[t][i]=max(vals[t][i<<1],vals[t][i<<1|1]);
}
void upd(I t,I l,I r,I val){
  psh(t,l),psh(t,r-1);
  for(I i=l+FIXN,j=r+FIXN;i<j;i>>=1,j>>=1){
    if(i&1)app(t,i++,val);
    if(j&1)app(t,--j,val);
  }
  pll(t,l),pll(t,r-1);
}
I qry(I t,I l,I r){
  psh(t,l),psh(t,r-1);
  I res=MIN;
  for(l+=FIXN,r+=FIXN;l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,vals[t][l++]);
    if(r&1)res=max(res,vals[t][--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&vals[0][0],&vals[0][0]+(K+1)*(2*FIXN),MIN);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  asn(0,0,0),bld(0);
  fill_n(lats,n+1,-1);
  I cnt=0,res;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(lats[a]!=-1)for(I j=0;j<=k;j++)upd(j,lats[a]+1,i+1,1);
    else cnt++;
    lats[a]=i;
    for(I j=1;j<=k;j++){
      I cur=qry(j-1,0,i+1)+cnt;
      res=cur,upd(j,i+1,i+2,cur-cnt-MIN);
    }
  }
  printf("%i\n",res);
}