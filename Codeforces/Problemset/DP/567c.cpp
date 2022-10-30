#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

Lli a_arr[N];
map<Lli,Lli>cnts[2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=0;
  for(I i=0;i<n;i++){
    Lli a=a_arr[i];
    if(a%k==0){
      res+=cnts[1][a/k];
      cnts[1][a]+=cnts[0][a/k];
    }
    cnts[0][a]++;
  }
  printf("%lli\n",res);
}