#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=2e5;
const I A=1e6;

I a_arr[N];
B coms[A+1];
I ps1[N],ps2[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  coms[0]=coms[1]=1;
  for(I i=2;i*i<=A;i++)if(!coms[i])
    for(I j=i*i;j<=A;j+=i)coms[j]=1;
  I t;cin>>t;
  while(t--){
    I n,e;cin>>n>>e;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)ps1[i]=ps2[i]=a_arr[i]==1;
    for(I i=n-1;i-e>=0;i--)if(a_arr[i-e]==1)ps1[i-e]+=ps1[i];
    for(I i=0;i+e<n;i++)if(a_arr[i+e]==1)ps2[i+e]+=ps2[i];
    Lli res=0;
    for(I i=0;i<n;i++)if(!coms[a_arr[i]]){
      Lli cur=1;
      if(i-e>=0)cur*=ps2[i-e]+1;
      if(i+e<n)cur*=ps1[i+e]+1;
      res+=cur-1;
    }
    printf("%lli\n",res);
  }
}