#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
Lli bin(I n,I k){
  Lli res=1;
  for(I i=n-k+1;i<=n;i++)res*=i;
  for(I i=1;i<=k;i++)res/=i;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,t;cin>>n>>m>>t;
  Lli res=0;
  for(I j=4;j<=t-1;j++)res+=bin(n,j)*bin(m,t-j);
  printf("%lli\n",res);
}
/*
brute force
*/