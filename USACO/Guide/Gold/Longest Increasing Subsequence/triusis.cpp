#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;

/*
Firstly, each pole must be subtracted
by the jump height multiplied by their
index because:

let x=current pole height
let y=next pole height
let j=jump height

x+j>=y, therefore x>=y-j

Then, subtract the length of the LDS
from the total length, representing the
amount of poles needing adjustment to
conform to x>=y-j.

Though, note that the LDS must start
with 0, representing the unadjustable
starting point.
*/

const I N=200000;

I a_arr[N];
vector<I>dp;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)a_arr[i]-=(i+1)*m;
  reverse(a_arr,a_arr+n);
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a>0)continue;
    auto it=upper_bound(dp.begin(),dp.end(),a);
    if(it==dp.end())dp.push_back(a);
    else *it=a;
  }
  printf("%i\n",n-dp.size());
  return 0;
}