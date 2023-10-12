#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
I s_arr[N];
I t_arr[N];
I inds[N];
vector<pair<I,I>>rems;
vector<tuple<I,I,I>>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>s_arr[i];
  for(I i=0;i<n;i++)cin>>t_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,[&](I a,I b){
    return s_arr[a]<s_arr[b];
  });
  sort(t_arr,t_arr+n);
  for(I i=0;i<n;i++){
    I j=inds[i],dif=t_arr[i]-s_arr[j];
    while(rems.size()&&dif<0){
      auto[rem,k]=rems.back();
      I com=min(rem,-dif);
      rem-=com,dif+=com;
      rems.back().first=rem;
      if(rem==0)rems.pop_back();
      ress.push_back({k,j,com});
    }
    if(dif<0)printf("NO\n"),exit(0);
    if(dif>0)rems.push_back({dif,j});
  }
  if(rems.size()!=0)printf("NO\n"),exit(0);
  printf("YES\n");
  printf("%i\n",ress.size());
  for(auto[i,j,d]:ress)printf("%i %i %i\n",i+1,j+1,d);
}
/*
for any tuple (i, j, k), drawing stones (i, j) closer by d units, then stones
(j, k) by d units as well is equivalent to drawing stones (i, k) by d units

this means that any stone in the direction of movement can be used to move a
stone d units as long as the former has at least d units to move in the
opposite direction

if all stones are in the proper position in the end, there is a solution
*/