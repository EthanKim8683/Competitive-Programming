#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
using C=char;
using B=bool;
const I N=5000;
const I K=5e6;
const Lli MOD=1e9+7;
Lli dp[N+1][N];
I vals[N][N+1];
I inds[N];
I t=0;
I ind=0;
I n;
S s;
C get(I i){
  if(i+t>=n)return 0;
  return s[i+t];
}
B cmp(I a,I b){
  return get(a)<get(b);
}
void dfs(I l,I r){
  sort(inds+l,inds+r,cmp);
  C pre=get(inds[l]);
  vals[inds[l]][inds[l]+t+1]=ind;
  for(I i=l+1;i<r;i++){
    C cur=get(inds[i]);
    if(cur!=pre){
      ind++;
      if(pre)t++,dfs(l,i),t--;
      l=i;
    }
    vals[inds[i]][inds[i]+t+1]=ind;
    pre=cur;
  }
  ind++;
  if(pre)t++,dfs(l,r),t--;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  cin>>s;
  iota(inds,inds+n,0);
  dfs(0,n);
  for(I i=1;i<=n;i++)dp[i][0]=1;
  for(I i=1;i<n;i++){
    Lli cur=0;
    for(I j=1;i+j<=n;j++)if(j==1||s[i]!='0'){
      (dp[i+j][i]+=cur)%=MOD;
      if(i-j>=0&&(j==1||s[i-j]!='0')){
        if(vals[i][i+j]>vals[i-j][i])(dp[i+j][i]+=dp[i][i-j])%=MOD;
        (cur+=dp[i][i-j])%=MOD;
      }
    }
  }
  Lli res=0;
  for(I i=0;i<n;i++)(res+=dp[n][i])%=MOD;
  printf("%lli\n",res);
}