#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I a_arr[N];
map<I,I>cnts;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cnts[a_arr[i]]++;
  I res=0;
  for(auto[a,cnt]:cnts)res=max(res,cnt);
  printf("%i\n",n-res);
}
/*
note that it is always possible to represent the maximal permutation using
directed cycles such that all but one directed edge goes from larger to
smaller

therefore, if we flatten the cycles, we can arrange each cycle from largest
to smallest

and since each cycle has only one greater element after permutation, the
minimum number of cycles yields the maximal permutation

the minimum number of cycles is the maximum number of occurrences of a value
since each of a value must belong to a different cycle
*/