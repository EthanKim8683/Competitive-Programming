#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=1e6;

Lli ps1[N],ps2[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i+1<n;i++)if(s[i]=='v'&&s[i+1]=='v')ps1[i+1]=1;
  for(I i=n-1;i>0;i--)if(s[i]=='v'&&s[i-1]=='v')ps2[i-1]=1;
  for(I i=0;i+1<n;i++)ps1[i+1]+=ps1[i];
  for(I i=n-1;i>0;i--)ps2[i-1]+=ps2[i];
  Lli res=0;
  for(I i=1;i+1<n;i++)if(s[i]=='o')res+=ps1[i-1]*ps2[i+1];
  printf("%lli\n",res);
}