#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=1e5;
const I MAX=1e9;

I ps1[N+1],ps2[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i<n;i++)ps1[i+1]=s[i]>='a'&&s[i]<='z';
  for(I i=0;i<n;i++)ps2[i+1]=s[i]>='A'&&s[i]<='Z';
  for(I i=0;i<n;i++)ps1[i+1]+=ps1[i];
  for(I i=0;i<n;i++)ps2[i+1]+=ps2[i];
  I res=MAX;
  for(I i=0;i<=n;i++)res=min(res,(ps1[i]-ps1[0])+(ps2[n]-ps2[i]));
  printf("%i\n",res);
}