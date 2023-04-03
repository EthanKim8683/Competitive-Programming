#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I Q=2e5;
I x_arr[N];
vector<I>inds[2*N];
pair<I,I>qrys[Q];
Lli ress[Q];
Lli lows[N],upps[N];
I n;
void add(I i,I j=1,I l1=0,I r1=n-1){
  I m=l1+(r1-l1)/2;
  auto[l2,r2]=qrys[i];
  if(r2<m)return add(i,j<<1,l1,m-1);
  if(l2>m)return add(i,j<<1|1,m+1,r1);
  inds[j].push_back(i);
}
void slv(I i=1,I l1=0,I r1=n-1){
  if(l1>r1)return;
  I m=l1+(r1-l1)/2;
  for(I j=l1;j<=m;j++)lows[j]=x_arr[j];
  for(I j=m+1;j<=r1;j++)upps[j]=x_arr[j];
  for(I j=m;j-1>=l1;j--)lows[j-1]=min(lows[j-1],lows[j]);
  for(I j=m+1;j+1<=r1;j++)upps[j+1]=min(upps[j+1],upps[j]);
  for(auto j:inds[i]){
    auto[l2,r2]=qrys[j];
    ress[j]=r2==m?lows[l2]:min(lows[l2],upps[r2]);
  }
  slv(i<<1,l1,m-1),slv(i<<1|1,m+1,r1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  for(I i=0;i<q;i++){
    I l,r;cin>>l>>r,l--,r--;
    qrys[i]={l,r},add(i);
  }
  slv();
  for(I i=0;i<q;i++)printf("%lli\n",ress[i]);
}