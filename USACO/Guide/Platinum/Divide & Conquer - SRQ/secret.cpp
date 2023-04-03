#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1000;
#ifdef ETHANKIM8683
void Init(I,I[]);
I Query(I,I);
I Secret(I x,I y){
  return x+y;
}
I main(){
  I n,q;cin>>n>>q;
  I a_arr[n];
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Init(n,a_arr);
  while(q--){
    I l,r;cin>>l>>r;
    printf("%i\n",Query(l-1,r-1));
  }
}
#else
#include"secret.h"
#endif
I*a_arr;
vector<I>vals[2*N];
I n;
void slv(I i=1,I l=0,I r=n-1){
  if(l>r)return;
  I m=l+(r-l)/2;
  vals[i].resize(r-l+1);
  if(m>=l)vals[i][m-l]=a_arr[m];
  if(m+1<=r)vals[i][m+1-l]=a_arr[m+1];
  for(I j=m;j-1>=l;j--)vals[i][j-1-l]=Secret(a_arr[j-1],vals[i][j-l]);
  for(I j=m+1;j+1<=r;j++)vals[i][j+1-l]=Secret(vals[i][j-l],a_arr[j+1]);
  slv(i<<1,l,m-1),slv(i<<1|1,m+1,r);
}
I qry(I l1,I r1,I i=1,I l2=0,I r2=n-1){
  I m=l2+(r2-l2)/2;
  if(r1<m)return qry(l1,r1,i<<1,l2,m-1);
  if(l1>m)return qry(l1,r1,i<<1|1,m+1,r2);
  return r1==m?vals[i][l1-l2]:Secret(vals[i][l1-l2],vals[i][r1-l2]);
}
void Init(I _n,I _a_arr[]){
  n=_n,a_arr=_a_arr,slv();
}
I Query(I l,I r){
  return qry(l,r);
}