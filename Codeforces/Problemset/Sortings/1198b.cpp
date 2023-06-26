#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I Q=2e5;
I a_arr[N];
tuple<I,I,I>qrys[Q];
I ress[N];
B viss[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I q;cin>>q;
  for(I i=0;i<q;i++){
    I t;cin>>t;
    if(t==1){
      I p,x;cin>>p>>x,p--;
      qrys[i]={t,p,x};
    }
    if(t==2){
      I x;cin>>x;
      qrys[i]={t,-1,x};
    }
  }
  I upp=0;
  for(I i=q-1;i>=0;i--){
    auto[t,p,x]=qrys[i];
    if(t==1){
      if(!viss[p])ress[p]=max(upp,x);
      viss[p]=1;
    }
    if(t==2){
      upp=max(upp,x);
    }
  }
  for(I i=0;i<n;i++)if(!viss[i])ress[i]=max(upp,a_arr[i]);
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
}