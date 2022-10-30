#include<bits/stdc++.h>

using namespace std;

using I=int;

vector<vector<I>>cels;
vector<vector<I>>invs;
vector<I>upps;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  cels.resize(n);
  for(I i=0;i<n;i++){
    cels[i].resize(m);
    for(I j=0;j<m;j++)cin>>cels[i][j];
  }
  invs.resize(m);
  for(I i=0;i<m;i++)for(I j=0;j+1<n;j++)
    if(cels[j+1][i]<cels[j][i])invs[i].push_back(j);
  for(I i=0;i<m;i++)invs[i].push_back(n-1);
  upps.resize(n);
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    upps[i]=max(upps[i],*lower_bound(invs[j].begin(),invs[j].end(),i));
  I k;cin>>k;
  for(I i=0;i<k;i++){
    I l,r;cin>>l>>r;
    printf("%s\n",upps[l-1]>=r-1?"Yes":"No");
  }
}