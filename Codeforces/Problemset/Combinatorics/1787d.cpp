#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2e5;
I a_arr[N];
B ancs[N];
vector<I>adjs[N];
B fins[N];
I sizs[N];
void dfs(I a){
  fins[a]=1;
  sizs[a]=1;
  for(auto b:adjs[a])dfs(b),sizs[a]+=sizs[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n;i++){
      I j=i+a_arr[i];
      if(j>=0&&j<n)adjs[j].push_back(i);
    }
    fill_n(fins,n,0);
    for(I i=0;i<n;i++){
      I j=i+a_arr[i];
      if(j<0||j>=n)dfs(i);
    }
    I fin=0;
    for(I i=0;i<n;i++)fin+=fins[i];
    fill_n(ancs,n,0);
    I t=0;
    for(;t>=0&&t<n&&!ancs[t];t+=a_arr[t])ancs[t]=1;
    Lli res=0;
    for(I i=0;i<n;i++){
      if(ancs[i]){
        res+=fin+n+1;
        if(t<0||t>=n)res-=sizs[i];
      }else{
        if(t<0||t>=n)res+=2*n+1;
      }
    }
    printf("%lli\n",res);
  }
}
/*
we can think of steps as edges on a functional graph

to ensure the game finishes after a finite number of steps, we can re-edge each
node in the component containing 1 such that the new edge leads to a component
that ends out of bounds

if no change is needed, nodes in components not containing 1 can lead anywhere
*/