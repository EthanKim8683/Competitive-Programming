#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=2e5;

C movs[N+1];
tuple<I,I,I>dp1[N+1],dp2[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    cin>>movs;
    dp1[0]={0,0,0};
    for(I i=0;i<n;i++){
      auto[cur,low,upp]=dp1[i];
      cur+=movs[i]=='+';
      cur-=movs[i]=='-';
      low=min(low,cur);
      upp=max(upp,cur);
      dp1[i+1]={cur,low,upp};
    }
    dp2[n]={0,0,0};
    for(I i=n;i>0;i--){
      auto[cur,low,upp]=dp2[i];
      cur-=movs[i-1]=='+';
      cur+=movs[i-1]=='-';
      low=min(low,cur);
      upp=max(upp,cur);
      dp2[i-1]={cur,low,upp};
    }
    while(m--){
      I l,r;cin>>l>>r,l--;
      auto[cur1,low1,upp1]=dp1[l];
      auto[cur2,low2,upp2]=dp2[r];
      low1-=cur1;
      upp1-=cur1;
      low2-=cur2;
      upp2-=cur2;
      I low=min(low1,low2);
      I upp=max(upp1,upp2);
      printf("%i\n",upp-low+1);
    }
  }
}