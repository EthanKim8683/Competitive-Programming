#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I Y=15;
const I MAX=1e9;

Lli facs[Y];
vector<pair<Lli,I>>sums;

I pop(Lli x){
  if(!x)return 0;
  return __builtin_popcountll(x);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<Y;i++)facs[i]=facs[i-1]*i;
  for(I i=0;i<(1<<Y);i++){
    Lli sum=0;
    for(I j=0;j<Y;j++)sum+=(i>>j&1)*facs[j];
    sums.push_back({sum,pop(i)});
  }
  I t;cin>>t;
  while(t--){
    Lli n;cin>>n;
    I res=pop(n);
    for(auto[sum,cnt]:sums)res=min(res,pop(n-sum)+cnt);
    printf("%i\n",res);
  }
}