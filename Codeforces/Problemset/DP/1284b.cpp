#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=100000;
const I S=1e6;
const I MIN=-1e9;
const I MAX=1e9;

I lows[N];
I upps[N];
I ps[S+4];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I low=MAX,upp=MIN;
    I l;cin>>l;
    for(I j=0;j<l;j++){
      I s;cin>>s,s++;
      if(low<s)low=0,upp=S+2;
      low=min(low,s);
      upp=max(upp,s);
    }
    lows[i]=low;
    upps[i]=upp;
  }
  for(I i=0;i<n;i++)ps[lows[i]+1]++;
  for(I i=0;i<=S+2;i++)ps[i+1]+=ps[i];
  Lli res=0;
  for(I i=0;i<n;i++)res+=ps[upps[i]];
  printf("%lli\n",res);
}