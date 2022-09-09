#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

using I=int;
using B=bool;

const I N=1e6;
const I MAX=1e9;

I a_arr[N];
I adjs[N];
queue<I>que;
I deps[N];
I cnt;

void add(I i,I d){
  if(d>=deps[i])return;
  deps[i]=d;
  que.push(i),cnt--;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,d;cin>>n>>d;
    fill_n(deps,n,MAX);
    while(que.size())que.pop();
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)adjs[(i+n-d)%n]=i;
    cnt=n;
    for(I i=0;i<n;i++)if(a_arr[i]==0)add(i,1);
    I res=0;
    while(que.size()&&cnt){
      I a=que.front();que.pop();
      res=max(res,deps[a]);
      add(adjs[a],deps[a]+1);
    }
    if(cnt){printf("-1\n");continue;}
    printf("%i\n",res);
  }
  return 0;
}