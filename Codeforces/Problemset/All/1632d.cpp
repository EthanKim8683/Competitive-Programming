#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I LOGN=18;
I a_arr[N];
I spas[N][LOGN];
set<I>curs;
I n;
void bld(){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<i)<=n;j++)spas[j][i]=gcd(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
}
I qry(I l,I r){
  I d=31-__builtin_clz(r-l);
  return gcd(spas[l][d],spas[r-(1<<d)][d]);
}
I fnd(I i){
  I l=0,r=i;
  while(l<r){
    I m=l+(r-l+1)/2;
    qry(m,i+1)<=i-m+1?l=m:r=m-1;
  }
  return qry(l,i+1)==i-l+1?l:-1;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)spas[i][0]=a_arr[i];
  bld();
  for(I i=0;i<n;i++){
    I j=fnd(i);
    if(j!=-1&&curs.lower_bound(j)==curs.end())curs.insert(i);
    printf("%i ",curs.size());
  }
}