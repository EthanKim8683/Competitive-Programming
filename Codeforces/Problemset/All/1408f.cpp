#include<bits/stdc++.h>
using namespace std;
using I=int;
vector<pair<I,I>>ress;
void slv(I l,I r){
  if(r-l==1)return;
  if(__builtin_popcount(r-l)==1){
    I m=l+(r-l)/2;
    slv(l,m),slv(m,r);
    for(I i=0;i<(r-l)/2;i++)ress.push_back({l+i,m+i});
  }else{
    I d=31-__builtin_clz(r-l);
    slv(l,l+(1<<d)),slv(r-(1<<d),r);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  slv(0,n);
  printf("%i\n",ress.size());
  for(auto[l,r]:ress)printf("%i %i\n",l+1,r+1);
}
/*
we can convert any power of two subarray into a single value

thus, we can produce two overlapping power-of-two subarrays such that the
entire array contains only two unique values (think sparse table)
*/