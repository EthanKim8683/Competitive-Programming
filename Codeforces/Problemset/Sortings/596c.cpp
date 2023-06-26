#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100000;
const I X=100000;
const I Y=100000;
const I W=100000;
pair<I,I>pnts[N];
I w_arr[N];
vector<I>rads1[X+Y+1],rads2[2*W+1];
I ress[N];
map<pair<I,I>,I>lows;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts[i]={x,y};
  }
  for(I i=0;i<n;i++)cin>>w_arr[i];
  for(I i=0;i<n;i++){
    auto[x,y]=pnts[i];
    rads1[x+y].push_back(i);
  }
  for(I i=0;i<n;i++)rads2[W+w_arr[i]].push_back(i);
  for(I i=-W;i<=W;i++)reverse(rads2[W+i].begin(),rads2[W+i].end());
  for(I i=0;i<=X+Y;i++)for(auto j:rads1[i]){
    auto[x,y]=pnts[j];
    if(abs(y-x)>W||rads2[W+y-x].empty())printf("NO\n"),exit(0);
    I k=rads2[W+y-x].back();rads2[W+y-x].pop_back();
    if(lows[{x,y}]>k)printf("NO\n"),exit(0);
    lows[{x+1,y}]=max(lows[{x+1,y}],k);
    lows[{x,y+1}]=max(lows[{x,y+1}],k);
    ress[k]=j;
  }
  printf("YES\n");
  for(I i=0;i<n;i++){
    auto[x,y]=pnts[ress[i]];
    printf("%i %i\n",x,y);
  }
}