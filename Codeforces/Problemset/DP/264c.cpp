#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MIN=-1e18;
I v_arr[N];
I c_arr[N];
Lli upps[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>v_arr[i];
  for(I i=0;i<n;i++)cin>>c_arr[i];
  while(q--){
    I a,b;cin>>a>>b;
    fill_n(upps,n+1,MIN);
    pair<Lli,I>upp1={0,-1},upp2={0,-1};
    for(I i=0;i<n;i++){
      Lli v=v_arr[i],c=c_arr[i];
      upps[c]=max(upps[c],upps[c]+v*a);
      if(upp1.second!=c)upps[c]=max(upps[c],upp1.first+v*b);
      if(upp2.second!=c)upps[c]=max(upps[c],upp2.first+v*b);
      if(upp1.second==c){
        upp1=max(upp1,{upps[c],c});
      }else{
        upp2=max(upp2,{upps[c],c});
      }
      if(upp2>upp1)swap(upp2,upp1);
    }
    printf("%lli\n",upp1.first);
  }
}