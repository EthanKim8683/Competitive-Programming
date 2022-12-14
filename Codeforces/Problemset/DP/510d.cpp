#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=300;
I l_arr[N];
I c_arr[N];
map<I,I>csts;
I gcd(I a,I b){
  return b?gcd(b,a%b):a;
}
void add(I i,I v){
  if(!csts.count(i)){csts[i]=v;return;}
  csts[i]=min(csts[i],v);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>l_arr[i];
  for(I i=0;i<n;i++)cin>>c_arr[i];
  for(I i=0;i<n;i++){
    I l=l_arr[i],c=c_arr[i];
    for(auto[j,v]:csts)add(gcd(j,l),v+c);
    add(l,c);
  }
  if(!csts.count(1))printf("-1\n"),exit(0);
  printf("%i\n",csts[1]);
}