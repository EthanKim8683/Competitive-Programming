#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I x_arr[N];
Lli blks[N];
I siz;
void upd(I i,I x){
  I j=i/siz;
  blks[j]-=x_arr[i],x_arr[i]=x,blks[j]+=x_arr[i];
}
Lli qry(I i){
  Lli res=0;
  for(I j=0;j<i/siz;j++)res+=blks[j];
  for(I j=i/siz*siz;j<i;j++)res+=x_arr[j];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  siz=sqrt(n);
  for(I i=0;i<n;i++)blks[i/siz]+=x_arr[i];
  while(q--){
    I t;cin>>t;
    if(t==1){
      I k,u;cin>>k>>u,k--;
      upd(k,u);
    }
    if(t==2){
      I a,b;cin>>a>>b,a--,b--;
      printf("%lli\n",qry(b+1)-qry(a));
    }
  }
}