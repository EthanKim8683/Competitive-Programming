#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;
const I K=1000;

I mods[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    Lli res=0;
    for(I i=0;i<n;i++){
      I a;cin>>a;
      res+=a/k;
      mods[i]=a%k;
    }
    sort(mods,mods+n);
    for(I l=0,r=n-1;l<r;l++,r--){
      while(mods[l]+mods[r]<k&&l<r)l++;
      if(l==r)break;
      res++;
    }
    printf("%lli\n",res);
  }
}