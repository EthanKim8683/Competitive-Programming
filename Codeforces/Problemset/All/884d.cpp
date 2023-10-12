#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
I a_arr[N];
multiset<Lli>rems;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)rems.insert(a_arr[i]);
  Lli res=0;
  while(rems.size()>1){
    I cnt=rems.size()%2==0?2:3;
    Lli sum=0;
    for(I i=0;i<cnt;i++){
      auto it=rems.begin();
      sum+=*it,rems.erase(it);
    }
    res+=sum,rems.insert(sum);
  }
  printf("%lli\n",res);
}
/*
the problem statement is unclear on the meaning of the input, but the balls are
all initially in the first box

the total cost is the total number of balls among all boxes operated on

if we look at the problem in reverse, we can think of combining boxes instead
of separating them

in doing so, we can combine to make the minimum box every time, yielding the
minimum total cost
*/