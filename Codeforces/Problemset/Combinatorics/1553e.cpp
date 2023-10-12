#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
I p_arr[N];
I cnts[N];
vector<I>ress;
I pars[N];
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>p_arr[i];
    fill_n(cnts,n,0);
    for(I i=0;i<n;i++)cnts[(i-(p_arr[i]-1)+n)%n]++;
    ress.clear();
    for(I i=0;i<n;i++)if((n-cnts[i]+1)/2<=m){
      fill_n(pars,n,-1);
      for(I j=0;j<n;j++)uni(p_arr[(j+i)%n]-1,j);
      I cnt=n;
      for(I j=0;j<n;j++)if(fnd(j)==j)cnt--;
      if(cnt<=m)ress.push_back(i);
    }
    printf("%i ",ress.size());
    for(auto i:ress)printf("%i ",i);
    printf("\n");
  }
}
/*
you can count for each k the number of i such that i == p[(i + k) % n]

if the minimum number of swaps required to produce p is no larger than m,
ceil((n - cnts[k]) / 2) <= m (cnts[k] >= n / 3 and each cnts[k] represents
a disjoint set, meaning at most 3 such k), we can find the number of cycles
in p with respect to cyclic shift k

the number of swaps required to produce a permutation of size n with c cycles
is n - c

then, we can further verify that n - c <= m, which, if true, means the k is
valid
*/