#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
Lli nums[N];
vector<Lli>cpss;
I pres[N*6+1];
I n;Lli m;I k;
I cnt(Lli x){
  return lower_bound(nums,nums+n,x)-nums;
}
I cnt(Lli l,Lli r){
  return upper_bound(nums,nums+n,r)-lower_bound(nums,nums+n,l);
}
Lli lft(Lli x){
  Lli l=0,r=x+1;
  while(l<r){
    Lli t=l+(r-l)/2;
    cnt(t,x)<=k-1?r=t:l=t+1;
  }
  return l;
}
Lli rgt(Lli x){
  Lli l=x-1,r=m;
  while(l<r){
    Lli t=l+(r-l+1)/2;
    cnt(x,t)<=k-1?l=t:r=t-1;
  }
  return l;
}
Lli val(Lli x){
  Lli l=lft(x),r=rgt(x);
  if(l>x||r<x)return 0;
  Lli low=(x-l)/2,upp=(r-x)/2;
  if(cnt(0,x)<=k-1)low=x;
  if(cnt(x,m)<=k-1)upp=m-x;
  return low+upp+1;
}
Lli opt(Lli cnt,Lli x){
  x=max(x,0ll);
  Lli l=0,r=x/2;
  while(l<r){
    Lli t=l+(r-l+1)/2;
    val(x-2*t)>=cnt?l=t:r=t-1;
  }
  return val(x-2*l)>=cnt?x-2*l:m;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m>>k;
  for(I i=0;i<n;i++)cin>>nums[i];
  sort(nums,nums+n);
  cpss.push_back(0),cpss.push_back(m);
  for(I i=0;i<n;i++){
    Lli x=nums[i],y=x-1,z=x+1;
    cpss.push_back(x),cpss.push_back(x^1);
    cpss.push_back(y),cpss.push_back(y^1);
    cpss.push_back(z),cpss.push_back(z^1);
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<cpss.size();i++)pres[i]=cnt(cpss[i]);
  pres[cpss.size()]=n;
  pair<Lli,Lli>res={0,0};
  for(I i=0,l=0,r=0;i<cpss.size();i++){
    if(cpss[i]<0||cpss[i]>m)continue;
    for(;l<cpss.size()-1;l++)if(pres[i+1]-pres[l]<=k-1)break;
    for(;r<cpss.size()-1;r++)if(pres[r+1]-pres[i]>k-1){r--;break;}
    if(l>i||pres[i+1]-pres[l]>k-1)continue;
    if(i>r||pres[r+1]-pres[i]>k-1)continue;
    Lli upp=(cpss[r]-cpss[i])/2,low=(cpss[i]-cpss[l])/2;
    if(pres[i+1]<=k-1)low=cpss[i];
    if(n-pres[i]<=k-1)upp=m-cpss[i];
    res=max(res,{low+upp+1,-cpss[i]});
  }
  auto[cnt,pck]=res;pck=-pck;
  pck=min(pck,min(opt(cnt,pck),opt(cnt,pck-1)));
  printf("%lli %lli\n",cnt,pck);
}