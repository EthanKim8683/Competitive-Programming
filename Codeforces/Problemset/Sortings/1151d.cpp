#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I stds[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  Lli res=0;
  for(I i=0;i<n;i++){
    I a,b;cin>>a>>b;
    stds[i]=b-a;
    res+=(Lli)b*(n-1);
  }
  sort(stds,stds+n);
  for(I i=0;i<n;i++)res-=(Lli)stds[i]*i;
  printf("%lli\n",res);
}