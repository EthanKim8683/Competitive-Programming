#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=0;
  for(I i=0;i+1<n;i++){
    Lli x=a_arr[i],y=a_arr[i+1];
    if(y<x)swap(x,y);
    res+=(x-1+1)*(y-x)+(n-y+1)*(y-x);
  }
  res+=(Lli)(a_arr[0]-1+1)*(n-a_arr[0]+1);
  res+=(Lli)(a_arr[n-1]-1+1)*(n-a_arr[n-1]+1);
  printf("%lli\n",res/2);
}
/*
for every pair of adjacent nodes (i, i + 1), where x = min(a[i], a[i + 1]),
y = max(a[i], a[i + 1]), a boundary is present when l <= x <= r < y or
x < l <= y <= r

this means there are (x - 1 + 1) * (y - x) + (n - y + 1) * (y - x) pairs (l, r)
such that there exists a boundary between (i, i + 1)

if a node i is missing an adjacent node, there exists a boundary when
l <= a[i] <= r

meaning there are (a[i] - 1 + 1) * (n - a[i] + 1) pairs (l, r) such that there
is a boundary adjacent to i

the number of components is equal to half the number of boundaries, as each
component has two boundaries
*/