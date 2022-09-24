#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const I A=1e5;
const Lli MAX=1e18;

I a_arr[N];
Lli diss[A+1];
Lli tots[A+1];
I cnts[A+1];
I viss[A+1];
queue<I>que;

void add(I d,I i,I j){
  if(i>A||viss[i]==j)return;
  que.push(i),diss[i]=d,viss[i]=j;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(viss,A+1,-1);
  for(I i=0;i<n;i++){
    I a;cin>>a;
    add(0,a,i);
    while(que.size()){
      I a=que.front();que.pop();
      I d=diss[a];
      tots[a]+=d;
      cnts[a]++;
      add(d+1,a*2,i);
      add(d+1,a/2,i);
    }
  }
  Lli res=MAX;
  for(I i=0;i<=A;i++)if(cnts[i]==n)
    res=min(res,tots[i]);
  printf("%lli\n",res);
  return 0;
}