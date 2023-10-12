#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I LOGN=17;
I a_arr[N];
I spas[N][LOGN];
I ress[N+1];
I n;
void bld(){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<i)<=n;j++)spas[j][i]=gcd(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
}
I qry(I l,I r){
  I d=31-__builtin_clz(r-l);
  return gcd(spas[l][d],spas[r-(1<<d)][d]);
}
I fnd(I i,I j,I x){
  I l=0,r=i;
  while(l<r){
    I m=l+(r-l)/2;
    qry(m,j+1)==x?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)spas[i][0]=a_arr[i];
    bld();
    fill_n(ress,n+1,1);
    for(I i=0;i<n;i++)for(I j=i;j>=0;j--){
      I x=qry(j,i+1);
      j=fnd(j,i,x);
      ress[i+1-j]=max(ress[i+1-j],x);
    }
    for(I i=n;i-1>=1;i--)ress[i-1]=max(ress[i-1],ress[i]);
    for(I i=1;i<=n;i++)printf("%i ",ress[i]);
    printf("\n");
  }
}