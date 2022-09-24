#include<iostream>
#include<cstdio>
#include<deque>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;

I a_arr[N];
I b_arr[N];
I adjs[N];
I ress[N];
I cols[N];
deque<I>que;

void dfs(I a,I c=0){
  if(ress[a]!=-1)return;
  cols[a]=c;
  I b=adjs[a];
  if(ress[b]!=-1&&cols[b]==c)return;
  if(c){ress[a]=que.back();que.pop_back();}
  else{ress[a]=que.front();que.pop_front();}
  dfs(b,!c);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(ress,n,-1);
    for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
    for(I i=0;i<n;i++){I b;cin>>b,b_arr[i]=b-1;}
    for(I i=0;i<n;i++)adjs[a_arr[i]]=b_arr[i];
    for(I i=0;i<n;i++)que.push_back(i);
    for(I i=0;i<n;i++)if(adjs[i]!=i)dfs(i);
    for(I i=0;i<n;i++)if(ress[i]==-1){ress[i]=que.back();que.pop_back();}
    Lli res=0;
    for(I i=0;i<n;i++)res+=abs(ress[a_arr[i]]-ress[b_arr[i]]);
    printf("%lli\n",res);
  }
  return 0;
}