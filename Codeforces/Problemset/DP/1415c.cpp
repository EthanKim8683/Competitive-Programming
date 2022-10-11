#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=1e5;
const Lli MAX=1e18;

I ps[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,p,k;cin>>n>>p>>k;
    S s;cin>>s;
    I x,y;cin>>x>>y;
    fill_n(ps,n+1,0);
    for(I i=0;i<n;i++)ps[i+1]=s[i]=='0';
    for(I i=n;i-k>=0;i--)ps[i-k]+=ps[i];
    Lli res=MAX;
    for(I i=0;i+p<=n;i++)res=min(res,(Lli)ps[i+p]*x+(Lli)i*y);
    printf("%lli\n",res);
  }
}