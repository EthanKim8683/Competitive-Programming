#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e3;

I a_arr[N];
I pars[N];
I adjs[N];
I deps[N];
vector<I>sizs;
B dp[N+1][N+1];
vector<I>ress;
I x;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  a=fnd(a),b=fnd(b);
  pars[a]+=pars[b],pars[b]=a;
}

B dfs(I a,I d=1){
  B res=a==x;
  deps[a]=d;
  if(adjs[a]<0)return res;
  return res|dfs(adjs[a],d+1);
}

I siz(I i){
  return -pars[fnd(i)];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>x,x--;
  fill_n(adjs,n,-1);
  fill_n(pars,n,-1);
  for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a<0)continue;
    uni(a,i);
    adjs[a]=i;
  }
  for(I i=0;i<n;i++)if(i==fnd(i))
    if(!dfs(i))sizs.push_back(siz(i));
  I m=sizs.size();
  dp[0][0]=1;
  for(I i=0;i<m;i++){
    I siz=sizs[i];
    for(I j=0;j<=n;j++){
      if(j+siz<=n)dp[i+1][j+siz]|=dp[i][j];
      dp[i+1][j]|=dp[i][j];
    }
  }
  for(I i=0;i<=n;i++)if(dp[m][i])
    ress.push_back(i+deps[x]);
  for(auto i:ress)printf("%i\n",i);
}