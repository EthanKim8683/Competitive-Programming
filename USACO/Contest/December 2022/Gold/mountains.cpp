#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2000;
I h_arr[N];
vector<tuple<I,I,I>>lows,upps,alls;
Lli cons[N];
I n;
B cmp1(tuple<I,I,I>a,tuple<I,I,I>b){
  return get<0>(a)*get<1>(b)>get<0>(b)*get<1>(a);
}
B cmp2(tuple<I,I,I>a,tuple<I,I,I>b){
  return get<0>(a)*get<1>(b)<get<0>(b)*get<1>(a);
}
void cnt(I i,I a){
  lows.clear();
  for(I j=0;j<i;j++){
    I b=h_arr[j];
    tuple<I,I,I>lin={a-b,i-j,j};
    if(get<1>(lin)<0)get<0>(lin)*=-1,get<1>(lin)*=-1;
    while(lows.size()&&cmp1(lows.back(),lin))lows.pop_back();
    lows.push_back(lin);
  }
  cons[i]=lows.size();
}
void cnt(I i,I a,I s){
  lows.clear();
  for(I j=0;j<i;j++){
    I b=h_arr[j];
    tuple<I,I,I>lin={a-b,i-j,j};
    if(get<1>(lin)<0)get<0>(lin)*=-1,get<1>(lin)*=-1;
    while(lows.size()&&cmp1(lows.back(),lin))lows.pop_back();
    lows.push_back(lin);
  }
  upps.clear();
  for(I j=n-1;j>i;j--){
    I b=h_arr[j];
    tuple<I,I,I>lin={a-b,i-j,j};
    if(get<1>(lin)<0)get<0>(lin)*=-1,get<1>(lin)*=-1;
    while(upps.size()&&cmp2(upps.back(),lin))upps.pop_back();
    upps.push_back(lin);
  }
  
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>h_arr[i];
  for(I i=0;i<n;i++)cnt(i,h_arr[i]);
  for(I i=0;i<n;i++)printf("%lli ",cons[i]);
  printf("\n");
  printf("%lli\n",accumulate(cons,cons+n,0ll));
  I q;cin>>q;
  while(q--){
    I x,y;cin>>x>>y,x--;
    cnt(x,h_arr[x],-1);
    h_arr[x]+=y;
    cnt(x,h_arr[x],+1);
    printf("%lli\n",accumulate(cons,cons+n,0ll));
  }
}