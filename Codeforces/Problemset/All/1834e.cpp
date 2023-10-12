#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=3e5;
const I LOGN=19;
const I P=4257733;
I a_arr[N];
I tmps[N];
B coms[P+1];
vector<I>prms;
Lli spas[N][LOGN];
vector<I>lcms;
I n;
void bld(){
  for(I i=0;i<n;i++)spas[i][0]=a_arr[i];
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<i)<=n;j++)spas[j][i]=min(lcm(spas[j][i-1],spas[j+(1<<(i-1))][i-1]),P+1ll);
}
Lli qry(I l,I r){
  I d=31-__builtin_clz(r-l);
  return min(lcm(spas[l][d],spas[r-(1<<d)][d]),P+1ll);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  coms[0]=coms[1]=1;
  for(I i=2;i*i<=P;i++)for(I j=i*i;j<=P;j+=i)coms[j]=1;
  for(I i=2;i<=P;i++)if(!coms[i])prms.push_back(i);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    copy_n(a_arr,n,tmps);
    sort(tmps,tmps+n);
    I p=0;
    for(I i=0;i<n;i++){
      I a=tmps[i];
      if(a>P)break;
      if(coms[a])continue;
      if(a==prms[p])p++;
    }
    p=prms[p];
    bld();
    lcms.clear();
    for(I i=0;i<n;i++){
      I j=i+1;
      while(j<=n){
        if(qry(i,j)>=p)break;
        lcms.push_back(qry(i,j));
        I l=j+1,r=n+1;
        while(l<r){
          I m=l+(r-l)/2;
          qry(i,m)!=qry(i,j)?r=m:l=m+1;
        }
        j=l;
      }
    }
    sort(lcms.begin(),lcms.end());
    I res=1;
    for(auto lcm:lcms)if(lcm==res)res++;
    printf("%i\n",res);
  }
}
/*
the maximum possible MEX is the smallest prime not in the provided array,
since no (a, b) exist such that lcm(a, b) = p, where a nor b equals p

since the smallest prime p scales roughly with n, we can estimate that
the maximum number of lcm-changing contributions to a subarray starting at
any index resulting in lcm less than p is roughly log(n)

this means we can find all possible lcm less than p in O(n * log(n))
*/