#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I K=17;
const I N=1<<(K+1);
Lli g_arr[N];
Lli ps[N+1];
map<Lli,I>pres;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I k;cin>>k;
    I n=1<<(k+1);
    for(I i=0;i<n;i++)cin>>g_arr[i];
    copy_n(g_arr,n,ps+1);
    for(I i=0;i<n;i++)ps[i+1]^=ps[i];
    pres.clear();
    I a=-1,b,c,d;
    pres.clear();
    for(I i=0;i<n;i++){
      if(a!=-1)break;
      if(i-1>=0)pres[g_arr[i-1]]=i-1;
      auto it=pres.find(g_arr[i]);
      if(it==pres.end())continue;
      I j=it->second;
      a=b=j,c=d=i;
    }
    pres.clear();
    for(I i=0;i<=n;i++){
      if(a!=-1)break;
      if(i-2>=0)pres[ps[i-2]]=i-2;
      auto it=pres.find(ps[i]);
      if(it==pres.end())continue;
      I j=it->second;
      a=b=j,c=j+1,d=i-1;
    }
    pres.clear();
    for(I i=1;i<=n;i++){
      if(a!=-1)break;
      if(i-1>=1)pres[ps[i-1]]=i-1;
      auto it=pres.find(g_arr[0]^ps[i]);
      if(it==pres.end())continue;
      I j=it->second;
      a=b=0,c=j,d=i-1;
    }
    printf("%i %i %i %i\n",a+1,b+1,c+1,d+1);
  }
}