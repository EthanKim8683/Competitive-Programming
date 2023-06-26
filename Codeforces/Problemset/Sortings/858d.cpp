#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=70000;
const I L=9;
I nums[N];
vector<I>cpss[L+1];
set<I>subs[N][L+1];
vector<I>viss[L+1][N*(L-1)/2];
I pows[L+1];
pair<I,I>ress[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=L;i++)pows[i]=pows[i-1]*10;
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>nums[i];
  for(I i=0;i<n;i++)for(I j=0;j<L;j++)for(I k=1;j+k<=L;k++)cpss[k].push_back(nums[i]/pows[j]%pows[k]);
  for(I i=1;i<=L;i++){
    sort(cpss[i].begin(),cpss[i].end());
    cpss[i].erase(unique(cpss[i].begin(),cpss[i].end()),cpss[i].end());
  }
  for(I i=0;i<n;i++)for(I j=0;j<L;j++)for(I k=1;j+k<=L;k++)subs[i][k].insert(lower_bound(cpss[k].begin(),cpss[k].end(),nums[i]/pows[j]%pows[k])-cpss[k].begin());
  for(I i=0;i<n;i++)for(I j=1;j<=L;j++)for(auto k:subs[i][j])viss[j][k].push_back(i);
  for(I i=L;i>=1;i--)for(I j=0;j<cpss[i].size();j++)if(viss[i][j].size()==1)ress[viss[i][j][0]]={i,cpss[i][j]};
  for(I i=0;i<n;i++){
    auto[len,sub]=ress[i];
    I rem=len;
    for(I j=sub;j;j/=10)rem--;
    for(I j=0;j<rem;j++)printf("0");
    if(sub!=0)printf("%i",sub);
    printf("\n");
  }
}