#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1000;

I m_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>m_arr[i];
  Lli res=0,x=-1;
  for(I i=0;i<n;i++){
    Lli tot=m_arr[i];
    I upp=m_arr[i];
    for(I j=i-1;j>=0;j--)tot+=(upp=min(upp,m_arr[j]));
    upp=m_arr[i];
    for(I j=i+1;j<n;j++)tot+=(upp=min(upp,m_arr[j]));
    if(tot<=res)continue;
    res=tot,x=i;
  }
  I upp=m_arr[x];
  for(I i=x-1;i>=0;i--)m_arr[i]=(upp=min(upp,m_arr[i]));
  upp=m_arr[x];
  for(I i=x+1;i<n;i++)m_arr[i]=(upp=min(upp,m_arr[i]));
  for(I i=0;i<n;i++)printf("%i ",m_arr[i]);
}