#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=3e5;
const I LOGN=19;
I a_arr[N];
I spas[N][LOGN];
I upps[N];
vector<I>ress;
I n;
void bld(){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<i)<=n;j++)spas[j][i]=gcd(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
}
I qry(I l,I r){
  I log=31-__builtin_clz(r-l);
  return gcd(spas[l][log],spas[r-(1<<log)][log]);
}
I lft(I i){
  I l=0,r=i;
  while(l<r){
    I m=l+(r-l)/2;
    qry(m,i+1)==a_arr[i]?r=m:l=m+1;
  }
  return l;
}
I rgt(I i){
  I l=i+1,r=n;
  while(l<r){
    I m=l+(r-l+1)/2;
    qry(i,m)==a_arr[i]?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)spas[i][0]=a_arr[i];
  bld();
  iota(upps,upps+n,0);
  I res=0;
  for(I i=0;i<n;i++){
    I l=lft(i),r=rgt(i);
    res=max(res,r-l),upps[l]=max(upps[l],r);
  }
  for(I i=0;i<n;i++)if(upps[i]-i==res)ress.push_back(i);
  printf("%i %i\n",ress.size(),res-1);
  for(auto i:ress)printf("%i ",i+1);
}