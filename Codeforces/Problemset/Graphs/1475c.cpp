#include<iostream>
#include<cstdio>
#include<set>

using namespace std;

using I=int;
using Lli=long long int;

const I A=2e5;
const I B=2e5;
const I K=2e5;

I a_arr[K],b_arr[K];
multiset<pair<I,I>>sabs;
I smas[A+1],smbs[B+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I a,b,k;cin>>a>>b>>k;
    for(I i=0;i<k;i++)cin>>a_arr[i];
    for(I i=0;i<k;i++)cin>>b_arr[i];
    for(I i=0;i<k;i++){
      I a=a_arr[i],b=b_arr[i];
      sabs.insert({a,b});
      smas[a]++,smbs[b]++;
    }
    Lli res=0;
    for(I i=0;i<k;i++){
      I a=a_arr[i],b=b_arr[i];
      sabs.erase(sabs.find({a,b}));
      smas[a]--,smbs[b]--;
      res+=(k-i-1)-smas[a]-smbs[b]+sabs.count({a,b});
    }
    printf("%lli\n",res);
  }
  return 0;
}