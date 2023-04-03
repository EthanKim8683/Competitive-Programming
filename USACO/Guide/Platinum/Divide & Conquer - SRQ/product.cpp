#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
const I Q=2e7;
I a_arr[N];
I b_arr[Q/64+2];
vector<Lli>pres[2*N];
I n;Lli p;
void bld(I i=1,I l=0,I r=n-1){
  if(r<l)return;
  I m=l+(r-l)/2;
  pres[i].resize(r-l+1);
  if(m>=l)pres[i][m-l]=a_arr[m];
  if(m+1<=r)pres[i][m+1-l]=a_arr[m+1];
  for(I j=m;j-1>=l;j--)pres[i][j-1-l]=pres[i][j-l]*a_arr[j-1]%p;
  for(I j=m+1;j+1<=r;j++)pres[i][j+1-l]=pres[i][j-l]*a_arr[j+1]%p;
  bld(i<<1,l,m-1),bld(i<<1|1,m+1,r);
}
Lli qry(I l1,I r1,I i=1,I l2=0,I r2=n-1){
  I m=l2+(r2-l2)/2;
  if(r1<m)return qry(l1,r1,i<<1,l2,m-1);
  if(l1>m)return qry(l1,r1,i<<1|1,m+1,r2);
  return r1==m?pres[i][l1-l2]:pres[i][l1-l2]*pres[i][r1-l2]%p;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I q;cin>>n>>p>>q;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<q/64+2;i++)cin>>b_arr[i];
    bld();
    Lli x=0;I l,r;
    for(I i=0;i<q;i++){
      if(i%64==0)l=b_arr[i/64],r=b_arr[i/64+1];
      l=(l+x)%n,r=(r+x)%n;
      if(l>r)swap(l,r);
      x=(qry(l,r)+1)%p;
    }
    printf("%i\n",x);
  }
}