#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lf=long double;

const I M=1000;

I s_arr[M];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,h;cin>>n>>m>>h,h--;
  for(I i=0;i<m;i++)cin>>s_arr[i];
  n--,s_arr[h]--;
  I t=accumulate(s_arr,s_arr+m,0);
  if(t<n)printf("-1\n"),exit(0);
  I s=s_arr[h];
  I r=t-s;
  Lf res=0;
  for(I i=1;i<=s;i++){
    if(s<0)continue;
    if(i<0)continue;
    if(s-i<0)continue;
    if(r<0)continue;
    if(n-i<0)continue;
    if(r-(n-i)<0)continue;
    if(t<0)continue;
    if(n<0)continue;
    if(t-n<0)continue;
    I upp=0;
    upp=max(upp,s);
    upp=max(upp,i);
    upp=max(upp,s-i);
    upp=max(upp,r);
    upp=max(upp,n-i);
    upp=max(upp,r-(n-i));
    upp=max(upp,t);
    upp=max(upp,n);
    upp=max(upp,t-n);
    Lf cur=1;
    for(I j=1;j<=upp;j++){
      if(j<=s)cur*=j;
      if(j<=i)cur/=j;
      if(j<=s-i)cur/=j;
      if(j<=r)cur*=j;
      if(j<=n-i)cur/=j;
      if(j<=r-(n-i))cur/=j;
      if(j<=t)cur/=j;
      if(j<=n)cur*=j;
      if(j<=t-n)cur*=j;
    }
    res+=cur;
  }
  printf("%Lf\n",res);
}