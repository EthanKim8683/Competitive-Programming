#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli k;cin>>n>>k,k--;
  Lli tot=1;
  for(I i=1;i<n;i++)tot=tot*2+1;
  I res=n;
  Lli l=0,r=tot;
  while(l<r){
    Lli m=l+(r-l)/2;
    if(m==k)break;
    if(m>k)r=m-1;
    if(m<k)l=m+1;
    res--;
  }
  printf("%i\n",res);
}