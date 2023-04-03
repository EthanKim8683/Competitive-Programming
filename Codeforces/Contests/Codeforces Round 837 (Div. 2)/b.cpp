#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=1e5;
I lows[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    fill_n(lows,n,-1);
    for(I i=0;i<m;i++){
      I x,y;cin>>x>>y,x--,y--;
      if(x<y)swap(x,y);
      lows[x]=max(lows[x],y);
    }
    for(I i=0;i+1<n;i++)lows[i+1]=max(lows[i+1],lows[i]);
    Lli res=0;
    for(I i=0;i<n;i++)res+=i-lows[i];
    printf("%lli\n",res);
  }
}