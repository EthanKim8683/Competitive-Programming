#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MAX=1e18;
I a_arr[N];
vector<I>cpss;
I cnts[3*N];
pair<Lli,I>pres[3*N],sufs[3*N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cpss.push_back(a_arr[i]),cpss.push_back(a_arr[i]-1),cpss.push_back(a_arr[i]+1);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++)cnts[lower_bound(cpss.begin(),cpss.end(),a_arr[i])-cpss.begin()]++;
  for(I i=0;i<cpss.size();i++)if(cnts[i]>=k)printf("0"),exit(0);
  for(Lli i=0,cnt=0,acc=0;i<cpss.size();i++)acc+=(Lli)cnts[i]*cpss[i],cnt+=cnts[i],pres[i]={(Lli)cnt*cpss[i]-acc,cnt};
  for(Lli i=cpss.size()-1,cnt=0,acc=0;i>=0;i--)acc+=(Lli)cnts[i]*cpss[i],cnt+=cnts[i],sufs[i]={acc-(Lli)cnt*cpss[i],cnt};
  Lli res=MAX;
  for(I i=1;i+1<cpss.size();i++){
    auto[cst1,cnt1]=pres[i-1];auto[cst2,cnt2]=sufs[i+1];I cnt3=cnts[i];
    if(cnt3==0)continue;
    res=min(res,cst1+cst2+k-cnt3);
    if(cnt1>=k-cnt3)res=min(res,cst1+k-cnt3);
    if(cnt2>=k-cnt3)res=min(res,cst2+k-cnt3);
  }
  printf("%lli\n",res);
}