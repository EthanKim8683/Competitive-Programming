#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
using Lli=long long int;
const I N=1e5;
S t_arr[N];
I inds[N];
pair<I,I>rats[N];
B cmp(I a,I b){
  auto[x1,y1]=rats[a];auto[x2,y2]=rats[b];
  return(Lli)x1*y2>(Lli)x2*y1;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    cin>>t_arr[i];
    for(auto c:t_arr[i]){
      if(c=='s')rats[i].first++;
      if(c=='h')rats[i].second++;
    }
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  S s="";
  for(I i=0;i<n;i++)s+=t_arr[inds[i]];
  Lli res=0,pre=0;
  for(auto c:s){
    if(c=='s')pre++;
    if(c=='h')res+=pre;
  }
  printf("%lli\n",res);
}