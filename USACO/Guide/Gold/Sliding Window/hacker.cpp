#include<iostream>
#include<cstdio>
#include<deque>

using namespace std;

using I=int;

const I N=500000;

I v_arr[N];
I rngs[N];
deque<pair<I,I>>que;
I cnt1=0,cnt2=0;

void add(I val){
  while(que.size()&&que.back().first>val)que.pop_back();
  que.push_back({val,cnt1++});
}

void rem(){
  if(que.size()&&que.front().second==cnt2)que.pop_front();
  cnt2++;
}

I qry(){
  return que.front().first;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>v_arr[i];
  I tot=0;
  for(I i=0;i<n;i++)tot+=v_arr[i];
  I low=n/2,upp=n-low;
  I sum=0;
  for(I i=0;i<upp;i++)sum+=v_arr[i];
  for(I i=0;i<n;i++){
    rngs[i]=sum;
    sum+=v_arr[(i+upp)%n]-v_arr[i];
  }
  for(I i=0;i<upp;i++)add(rngs[i]);
  I res=0;
  for(I i=0;i<n;i++){
    res=max(res,qry());
    add(rngs[(i+upp)%n]),rem();
  }
  printf("%i\n",res);
  return 0;
}