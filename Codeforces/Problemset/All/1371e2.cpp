#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
I a_arr[N];
multimap<I,pair<I,B>>rems;
multiset<I>reqs;
vector<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,p;cin>>n>>p;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n,greater<I>());
  I low=0,upp=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i],v=((n-a-i)%p+p)%p,w=(p-v)%p;
    rems.insert({a,{w,(n-i)%p==0}});
    reqs.insert(w);
    low=max(low,1+i+a-n);
    upp=max(upp,a);
  }
  B flg=0;
  for(I i=low;i<=upp;i++){
    for(auto it=rems.begin();it!=rems.end();){
      auto[a,rem]=*it;
      if(a>i)break;
      auto[w,set]=rem;
      reqs.erase(reqs.find(w));
      flg|=set;
      it=rems.erase(it);
    }
    if(flg)break;
    if(reqs.find(i%p)!=reqs.end())continue;
    ress.push_back(i);
  }
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i ",i);
}
/*
a permutation p is good if, for all i, a[i] - inv(p)[i] is less than or equal
to x

therefore, the number of valid permutations of an integer x is equal to
the number of permutations (we can substitute inv(p) for p, inv(p) itself is a
permutation) whose max(a[i] - p[i]) is less than or equal to x

for an integer x, the earliest p[i] for an index i is a[i] - x, meaning, if
processed in non-decreasing order of a[i], the number of possible positions
is equal to n - max(a[i] - x, 0) - m, where m is the number of j before i

this is where the prime p comes in

if, for a given x, any i has a multiple of p number of possible positions, f(x)
is also a multiple of p, since the number of permutations is the product of
said quantity among all i

therefore, we can produce v[i] = (n - a[i] - m) % p for all i, and find
w[i] = (p - v[i]) % p, the modulo of the x required to make a multiple of
prime p
*/