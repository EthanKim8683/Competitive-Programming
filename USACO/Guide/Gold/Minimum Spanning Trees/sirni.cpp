#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I P=1e7;
I p_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>p_arr[i];
}
/*
min(a%b,b%a):
- a<b: min(a,b%a)=b%a
- a>b: min(a%b,b)=a%b

max(res)=(min(a)-1)*(n-1)

min dist from multiple of `p` going up, lookup at `p`
min dist from `p` going down, lookup at multiple of `p`
*/