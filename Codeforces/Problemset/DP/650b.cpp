#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=5e5;
I ps1[N],ps2[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,a,b,t;cin>>n>>a>>b>>t;
  S s;cin>>s;
  for(I i=0;i+1<n;i++)ps1[i+1]=ps1[i]+a+1+(s[i+1]!='h')*b;
  for(I i=0;i+1<n;i++)ps2[i+1]=ps2[i]+a+1+(s[n-1-i]!='h')*b;
  I res=0;
  if(t-(s[0]!='h')*b-1>=0)res=max(res,1);
  for(I i=0;i<n;i++){
    I rem=t-(s[0]!='h')*b-1-ps1[i];
    if(rem>=0)res=max(res,i+1);
  }
  for(I i=0;i<n;i++){
    I rem=t-(s[0]!='h')*b-1-ps2[i];
    if(rem>=0)res=max(res,i+1);
  }
  for(I i=0;i<n;i++){
    I rem=t-(s[0]!='h')*b-1-ps1[i]-i*a;
    if(rem>=0)res=max(res,(I)(i+upper_bound(ps2,ps2+n,rem)-ps2));
  }
  for(I i=0;i<n;i++){
    I rem=t-(s[0]!='h')*b-1-ps2[i]-i*a;
    if(rem>=0)res=max(res,(I)(i+upper_bound(ps1,ps1+n,rem)-ps1));
  }
  printf("%i\n",min(res,n));
}