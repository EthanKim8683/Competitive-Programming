#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
struct Seg{Lli dp[3][3],l,r;};
const I N=200000;
const Lli MIN=-1e18;
Lli a_arr[N];
Seg segs[2*N];
I n;
void cmb(Lli&a,Lli b){
  a=max(a,b);
}
Seg cmb(Seg a,Seg b){
  Seg res;
  for(I i=0;i<3;i++)for(I j=0;j<3;j++){
    res.dp[i][j]=MIN;
    cmb(res.dp[i][j],a.dp[i][0]+b.dp[0][j]);
    cmb(res.dp[i][j],a.dp[i][0]+b.dp[1][j]);
    cmb(res.dp[i][j],a.dp[i][0]+b.dp[2][j]);
    cmb(res.dp[i][j],a.dp[i][1]+b.dp[0][j]);
    cmb(res.dp[i][j],a.dp[i][1]+b.dp[1][j]);
    cmb(res.dp[i][j],a.dp[i][1]+b.dp[2][j]+max(b.l-a.r,0ll));
    cmb(res.dp[i][j],a.dp[i][2]+b.dp[0][j]);
    cmb(res.dp[i][j],a.dp[i][2]+b.dp[1][j]+max(a.r-b.l,0ll));
    cmb(res.dp[i][j],a.dp[i][2]+b.dp[2][j]);
  }
  res.l=a.l,res.r=b.r;
  return res;
}
void asn(I i,Lli x){
  segs[i+n]={{{0,0,0},{0,MIN,0},{0,0,MIN}},x,x};
}
void bld(){
  for(I i=n-1;i>0;i--)segs[i]=cmb(segs[i<<1],segs[i<<1|1]);
}
void upd1(I i,Lli x){
  for(segs[i+=n].l+=x;i>1;i>>=1)segs[i>>1]=cmb(segs[i&~1],segs[i|1]);
}
void upd2(I i,Lli x){
  for(segs[i+=n].r+=x;i>1;i>>=1)segs[i>>1]=cmb(segs[i&~1],segs[i|1]);
}
Lli qry(I l,I r){
  Seg lrs={{{0,MIN,MIN},{MIN,MIN,MIN},{MIN,MIN,MIN}},0,0};
  Seg rrs={{{0,MIN,MIN},{MIN,MIN,MIN},{MIN,MIN,MIN}},0,0};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)lrs=cmb(lrs,segs[l++]);
    if(r&1)rrs=cmb(segs[--r],rrs);
  }
  Seg seg=cmb(lrs,rrs);
  Lli res=MIN;
  for(I i=0;i<3;i++)for(I j=0;j<3;j++)cmb(res,seg.dp[i][j]);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)asn(i,a_arr[i]);
  bld();
  while(q--){
    I l,r,x;cin>>l>>r>>x,l--,r--;
    upd1(l,x),upd2(r,x);
    printf("%lli\n",qry(0,n));
  }
}