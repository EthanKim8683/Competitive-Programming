#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I a_arr[N];
I ps[N];
I segs[2*(N+1)];
I n;
void upd(I i,I val){
  for(i+=n+1;i>0;i>>=1)segs[i]=max(segs[i],val);
}
I qry(I l,I r){
  I res=0;
  for(l+=n+1,r+=n+1;l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs[l++]);
    if(r&1)res=max(res,segs[--r]);
  }
  return res;
}
I qry(I i){
  return segs[i+n+1];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i+1<n;i++)ps[i+1]=ps[i]+(a_arr[i]!=a_arr[i+1]);
  upd(0,1);
  for(I i=1;i<n;i++){
    I a=a_arr[i],b=a_arr[i-1];
    upd(b,ps[i-1]-ps[i]+max(qry(0,a),qry(a+1,n+1))+1);
    upd(b,ps[i-1]-ps[i]+qry(a));
  }
  printf("%i\n",ps[n-1]+qry(0,n+1));
}