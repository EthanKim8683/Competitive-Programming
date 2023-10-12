#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
const I A=1e6;
I a_arr[N];
I lows[2][N],upps[2][N];
I segs[2*A];
void upd(I i,I val){
  for(segs[i+=A]=val;i>>=1;)segs[i]=max(segs[i<<1],segs[i<<1|1]);
}
I qry(I l,I r){
  I res=0;
  for(l+=A,r+=A;l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs[l++]);
    if(r&1)res=max(res,segs[--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill_n(segs,2*A,0);
  for(I i=0;i<n;i++){
    I a=a_arr[i]-1;
    lows[0][i]=qry(0,a+1)-1;
    lows[1][i]=qry(a,A)-1;
    upd(a,i+1);
  }
  fill_n(segs,2*A,0);
  for(I i=n-1;i>=0;i--){
    I a=a_arr[i]-1;
    upps[0][i]=n-qry(0,a);
    upps[1][i]=n-qry(a+1,A);
    upd(a,n-i);
  }
  Lli res=0;
  for(I i=0;i<n;i++){
    Lli a=a_arr[i];
    res-=a*(i-lows[0][i])*(upps[0][i]-i);
    res+=a*(i-lows[1][i])*(upps[1][i]-i);
  }
  printf("%lli\n",res);
}