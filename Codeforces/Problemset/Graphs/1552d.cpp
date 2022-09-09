#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I N=10;

I a_arr[N];
I sum=0,cnt=0;
B res=0;
I n;

void dfs(I d){
  if(d==n){
    if(!sum&&cnt)res=1;
    return;
  }
  for(I i=-1;i<=1;i++){
    sum+=i*a_arr[d];
    cnt+=!!i;
    dfs(d+1);
    sum-=i*a_arr[d];
    cnt-=!!i;
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    res=0;
    dfs(0);
    if(res)printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}