#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
vector<I>muls;
multiset<I>ones;
I one=0;
void add(I x){
  if(x==0)return;
  if(x==1){one++;return;}
  for(I i=1;i<=x;i*=10)if(x==i){ones.insert(x);return;}
  muls.push_back(x);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I s,n;cin>>s>>n;
    muls.clear(),ones.clear(),one=0;
    add(s);
    while(one+muls.size()+ones.size()<n){
      if(muls.size()){
        I x=muls.back();muls.pop_back();
        for(I i=1;i<=x;i*=10)if(x/i%10){add(i),add(x-i);break;}
        continue;
      }
      if(ones.size()){
        auto it=ones.begin();I x=*it;ones.erase(it);
        add(x/10),add(x-x/10);
        continue;
      }
    }
    for(auto i:ones)printf("%i ",i);
    for(auto i:muls)printf("%i ",i);
    for(I i=0;i<one;i++)printf("1 ");
    printf("\n");
  }
}