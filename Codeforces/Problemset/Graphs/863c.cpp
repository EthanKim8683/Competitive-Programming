#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

I a_arr[3][3];
I b_arr[3][3];
I deps[3][3];
vector<pair<I,I>>stks;
Lli ress[2];
Lli k;

B win(I a,I b){
  return b==(a+1)%3;
}

void dfs(I a,I b,I d){
  if(deps[a][b]!=-1){
    I c=deps[a][b];
    Lli len=d-c,tot=k-c;
    for(I i=0;i<min((Lli)c,k);i++){
      auto[x,y]=stks[i];
      if(x!=y)ress[win(x,y)]+=1;
    }
    for(I i=c;i<min((Lli)d,k);i++){
      auto[x,y]=stks[i];
      if(x!=y)ress[win(x,y)]+=tot/len+(i-c<tot%len);
    }
    printf("%lli %lli\n",ress[0],ress[1]);
    return;
  }
  deps[a][b]=d;
  stks.push_back({a,b});
  dfs(a_arr[a][b],b_arr[a][b],d+1);
  stks.pop_back();
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I a,b;cin>>k>>a>>b,a--,b--;
  fill(&deps[0][0],&deps[0][0]+sizeof(deps)/sizeof(I),-1);
  for(I i=0;i<3;i++)for(I j=0;j<3;j++){I a;cin>>a,a_arr[i][j]=a-1;}
  for(I i=0;i<3;i++)for(I j=0;j<3;j++){I b;cin>>b,b_arr[i][j]=b-1;}
  dfs(a,b,0);
  return 0;
}