#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
I x_arr[N];
I inds[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    I x;cin>>x,x--;
    x_arr[i]=x,inds[x]=i;
  }
  I res=1;
  for(I i=0;i+1<n;i++)res+=inds[i+1]<inds[i];
  while(m--){
    I a,b;cin>>a>>b,a--,b--;
    if(a!=b){
      I x=x_arr[a],y=x_arr[b];
      if(x-1>=0)res-=inds[x]<inds[x-1];
      if(y-1>=0)res-=inds[y]<inds[y-1];
      if(x+1<n&&y-x!=1)res-=inds[x+1]<inds[x];
      if(y+1<n&&x-y!=1)res-=inds[y+1]<inds[y];
      swap(x_arr[a],x_arr[b]);
      swap(inds[x],inds[y]);
      if(x-1>=0)res+=inds[x]<inds[x-1];
      if(y-1>=0)res+=inds[y]<inds[y-1];
      if(x+1<n&&y-x!=1)res+=inds[x+1]<inds[x];
      if(y+1<n&&x-y!=1)res+=inds[y+1]<inds[y];
    }
    printf("%i\n",res);
  }
}