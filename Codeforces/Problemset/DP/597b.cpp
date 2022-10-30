#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=5e5;
const I MAX=1e9;

vector<I>cpss;
pair<I,I>ords[N];
I dp[N+1];

I cps(I i){
  return lower_bound(cpss.begin(),cpss.end(),i)-cpss.begin();
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    cpss.push_back(l);
    cpss.push_back(r);
    ords[i]={l,r};
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++){
    auto[l,r]=ords[i];
    ords[i]={cps(l),cps(r)};
  }
  sort(ords,ords+n);
  for(I i=0;i<n;i++){
    auto[l,r]=ords[i];
    I j=upper_bound(ords,ords+n,pair<I,I>{r,MAX})-ords;
    dp[j]=max(dp[j],dp[i]+1);
    dp[i+1]=max(dp[i+1],dp[i]);
  }
  printf("%i\n",dp[n]);
}