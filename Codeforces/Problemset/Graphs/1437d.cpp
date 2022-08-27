#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

using I=int;

const I N=2e5;

I a_arr[N];
queue<I>que;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    que.push(0);
    I r=1,res=0;
    while(r<n){
      I d=que.front();que.pop();
      res=max(res,d);
      while(r+1<n&&a_arr[r+1]>a_arr[r])
        que.push(d+1),r++;
      que.push(d+1),r++;
    }
    while(que.size())
      res=max(res,que.front()),que.pop();
    printf("%i\n",res);
  }
  return 0;
}