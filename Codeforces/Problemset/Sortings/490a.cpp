#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5000;
I t_arr[N];
vector<I>inds[3];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>t_arr[i];
  for(I i=0;i<n;i++)inds[t_arr[i]-1].push_back(i);
  I cnt=min(min(inds[0].size(),inds[1].size()),inds[2].size());
  printf("%i\n",cnt);
  for(I i=0;i<cnt;i++)printf("%i %i %i\n",inds[0][i]+1,inds[1][i]+1,inds[2][i]+1);
}