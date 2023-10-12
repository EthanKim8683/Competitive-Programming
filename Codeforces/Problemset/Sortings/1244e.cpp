#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MAX=1e18;
I a_arr[N];
Lli pres1[N],sufs1[N];
Lli pres2[N],sufs2[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  copy_n(a_arr,n,pres1);
  copy_n(a_arr,n,sufs1);
  for(I i=0;i+1<n;i++)pres1[i+1]+=pres1[i];
  for(I i=n-1;i>0;i--)sufs1[i-1]+=sufs1[i];
  for(I i=0;i<n;i++){
    pres2[i]=(Lli)(i+1)*a_arr[i]-pres1[i];
    sufs2[i]=sufs1[i]-(Lli)(n-i)*a_arr[i];
  }
  Lli res=MAX;
  for(I i=0;i<n;i++){
    if(k-pres2[i]<0)break;
    I j=lower_bound(sufs2+i,sufs2+n,k-pres2[i],greater<Lli>())-sufs2;
    Lli rem=k-pres2[i]-sufs2[j],cur=a_arr[j]-a_arr[i];
    Lli cst1=i+1,lim1=i+1>=n?MAX:a_arr[i+1]-a_arr[i];
    Lli cst2=n-j,lim2=j-1<0?MAX:a_arr[j]-a_arr[j-1];
    if(cst2<cst1)swap(cst1,cst2),swap(lim1,lim2);
    Lli dif1=min(rem/cst1,lim1);rem-=dif1*cst1,cur-=dif1;
    Lli dif2=min(rem/cst2,lim2);rem-=dif2*cst2,cur-=dif2;
    res=min(res,cur);
  }
  for(I i=n-1;i>=0;i--){
    if(k-sufs2[i]<0)break;
    I j=upper_bound(pres2,pres2+i+1,k-sufs2[i])-pres2-1;
    Lli rem=k-sufs2[i]-pres2[j],cur=a_arr[i]-a_arr[j];
    Lli cst1=n-i,lim1=i-1<0?MAX:a_arr[i]-a_arr[i-1];
    Lli cst2=j+1,lim2=j+1>=n?MAX:a_arr[j+1]-a_arr[j];
    if(cst2<cst1)swap(cst1,cst2),swap(lim1,lim2);
    Lli dif1=min(rem/cst1,lim1);rem-=dif1*cst1,cur-=dif1;
    Lli dif2=min(rem/cst2,lim2);rem-=dif2*cst2,cur-=dif2;
    res=min(res,cur);
  }
  printf("%lli\n",max(res,0ll));
}