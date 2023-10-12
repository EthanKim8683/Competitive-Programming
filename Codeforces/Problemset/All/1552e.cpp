#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100;
const I K=100;
I c_arr[N*K];
B viss[N+1];
I pres[N+1];
pair<I,I>ress[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n*k;i++)cin>>c_arr[i];
  I cnt=0;
  while(cnt<n){
    fill_n(pres,n+1,-1);
    for(I i=0;i<n*k;i++){
      I c=c_arr[i];
      if(viss[c])continue;
      if(pres[c]!=-1){
        ress[c]={pres[c],i};
        viss[c]=1,cnt++;
        fill_n(pres,n+1,-1);
        continue;
      }
      pres[c]=i;
    }
  }
  for(I i=1;i<=n;i++){
    auto[l,r]=ress[i];
    printf("%i %i\n",l+1,r+1);
  }
}
/*
if we greedily create intervals as soon a color is seen twice, at most n - 1
intervals are not disjoint with the created interval

this means that each round we can create around k - 1 disjoint intervals as
there are n * (k - 1) intervals total

therefore, at most n / (k - 1) rounds are needed to create intervals for
all colors
*/