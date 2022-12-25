#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I A=5e6;
const I MAX=1e9;
I a_arr[N];
I dp[A+1];
B coms[A+1];
I mods[4];
map<I,I>tims;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=2;i*i<=A;i++)if(!coms[i])for(I j=i*i;j<=A;j+=i)coms[j]=1;
  for(I i=1;i<=A;i++){
    if(!coms[i])mods[i%4]=0;
    else mods[i%4]++;
    dp[i]=mods[i%4];
  }
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    tims.clear();
    for(I i=0;i<n;i++){
      I a=a_arr[i],cnt=dp[a];
      if(tims.count(cnt))continue;
      tims[cnt]=a%4;
    }
    if(tims.begin()->second)printf("Farmer John\n");
    else printf("Farmer Nhoj\n");
  }
}