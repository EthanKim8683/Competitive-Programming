#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1000;

I p_arr[N];
B viss[N];

I dfs(I a){
  if(viss[a])return a;
  viss[a]=true;
  return dfs(p_arr[a]);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){I p;cin>>p,p_arr[i]=p-1;};
  for(I i=0;i<n;i++){
    fill_n(viss,n,false);
    printf("%i ",dfs(i)+1);
  }
  return 0;
}