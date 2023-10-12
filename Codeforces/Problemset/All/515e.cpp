#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MAX=1e18;
const Lli MIN=-MAX;
I d_arr[N];
I h_arr[N];
Lli ps[N+1];
tuple<Lli,Lli,Lli>segs[2*N];
I n;
tuple<Lli,Lli,Lli>cmb(tuple<Lli,Lli,Lli>l,tuple<Lli,Lli,Lli>r){
  auto[sum1,low1,upp1]=l;
  auto[sum2,low2,upp2]=r;
  return{max(max(sum1,sum2),upp2-low1),min(low1,low2),max(upp1,upp2)};
}
void asn(I i){
  segs[i+n]={0,ps[i]-2*h_arr[i],ps[i]+2*h_arr[i]};
}
void bld(){
  for(I i=n-1;i>0;i--)segs[i]=cmb(segs[i<<1],segs[i<<1|1]);
}
tuple<Lli,Lli,Lli>qry(I l,I r){
  tuple<Lli,Lli,Lli>lrs={0,MAX,MIN},rrs={0,MAX,MIN};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)lrs=cmb(lrs,segs[l++]);
    if(r&1)rrs=cmb(segs[--r],rrs);
  }
  return cmb(lrs,rrs);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>d_arr[i];
  for(I i=0;i<n;i++)cin>>h_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=ps[i]+d_arr[i];
  fill_n(segs,2*N,tuple<Lli,Lli,Lli>{0,MAX,MIN});
  for(I i=0;i<n;i++)asn(i);
  bld();
  while(m--){
    I a,b;cin>>a>>b,a--,b--;
    if(a<=b){
      auto[sum1,low1,upp1]=qry(0,a);
      auto[sum2,low2,upp2]=qry(b+1,n);
      auto[sum3,low3,upp3]=cmb({sum2,low2,upp2},{sum1,low1+ps[n],upp1+ps[n]});
      printf("%lli\n",sum3);
    }
    if(a>b){
      auto[sum1,low1,upp1]=qry(b+1,a);
      printf("%lli\n",sum1);
    }
  }
}
/*
we can use segment trees to combine minimum and maximum prefix sums
*/