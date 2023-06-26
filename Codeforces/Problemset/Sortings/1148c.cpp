#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=3e5;
I p_arr[N];
I locs[N],occs[N];
vector<pair<I,I>>ress;
void swp(I a,I b){
  if(a==b)return;
  ress.push_back({a,b});
  swap(locs[occs[a]],locs[occs[b]]);
  swap(occs[a],occs[b]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  for(I i=0;i<n;i++)occs[i]=p_arr[i]-1;
  for(I i=0;i<n;i++)locs[p_arr[i]-1]=i;
  for(I i=0;i<n;i++){
    I j=locs[i];
    if(j==i)continue;
    I k=2*abs(j-0)>=n?0:n-1;
    I l=2*abs(i-0)>=n?0:n-1;
    swp(j,k),swp(k,l),swp(l,i);
  }
  printf("%i\n",ress.size());
  for(auto[a,b]:ress)printf("%i %i\n",a+1,b+1);
}