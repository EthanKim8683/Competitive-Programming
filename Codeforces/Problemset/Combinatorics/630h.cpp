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
Lli prm(I n){
  Lli res=1;
  for(I i=1;i<=n;i++)res*=i;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  printf("%lli\n",bin(n,5)*bin(n,5)*prm(5));
}
/*
we can choose 5 rows and 5 columns and permute along the columns
*/