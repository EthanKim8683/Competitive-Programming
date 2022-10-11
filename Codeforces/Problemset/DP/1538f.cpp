#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

Lli pows[10],reps[10];

Lli cnt(Lli x,I i){
  Lli pow=pows[i],rep=reps[i];
  return x/pow+(x%pow>=rep);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<10;i++)pows[i]=pows[i-1]*10;
  for(I i=0;i<10;i++)reps[i]=pows[i]-1;
  I t;cin>>t;
  while(t--){
    Lli l,r;cin>>l>>r,l--,r--;
    Lli res=0;
    for(I i=0;i<10;i++)res+=cnt(r,i)-cnt(l,i);
    printf("%lli\n",res);
  }
}