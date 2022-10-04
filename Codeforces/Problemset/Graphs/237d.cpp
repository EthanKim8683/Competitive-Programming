#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I M=N-1;

pair<I,I>edgs[M];
vector<I>nods[N];
vector<pair<I,I>>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I m=n-1;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    nods[a].push_back(i);
    nods[b].push_back(i);
    edgs[i]={a,b};
  }
  for(I i=0;i<n;i++){
    I a=nods[i].back();nods[i].pop_back();
    for(auto b:nods[i])ress.push_back({a,b});
  }
  printf("%i\n",m);
  for(I i=0;i<m;i++){
    auto[a,b]=edgs[i];
    printf("2 %i %i\n",a+1,b+1);
  }
  for(I i=0;i<m-1;i++){
    auto[a,b]=ress[i];
    printf("%i %i\n",a+1,b+1);
  }
}