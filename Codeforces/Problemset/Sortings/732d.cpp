#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I M=1e5;
const Lli MIN=-1e18;
const Lli MAX=1e18;
I d_arr[N];
I a_arr[M];
Lli segs[2*M];
I m;
void upd(I i,Lli val){
  for(segs[i+=m]=val;i>>=1;)segs[i]=min(segs[i<<1],segs[i<<1|1]);
}
Lli qry(I l,I r){
  Lli res=MAX;
  for(l+=m,r+=m;l<r;l>>=1,r>>=1){
    if(l&1)res=min(res,segs[l++]);
    if(r&1)res=min(res,segs[--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>d_arr[i];
  for(I i=0;i<m;i++)cin>>a_arr[i];
  fill_n(segs,2*m,MIN);
  Lli low=accumulate(a_arr,a_arr+m,0ll)+m,res=MAX;
  for(I i=0;i<n;i++){
    I d=d_arr[i];
    if(d==0)continue;
    upd(d-1,i-a_arr[d-1]);
    Lli j=min(qry(0,m),i+1-low);
    if(j>=0)res=min(res,(Lli)i+1);
  }
  printf("%lli\n",res==MAX?-1:res);
}