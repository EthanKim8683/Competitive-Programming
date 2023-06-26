#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=132674;
tuple<I,I,I,I>rcts[N];
vector<I>cpss1,cpss2;
I ps1[2*N+1],ps2[2*N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
    rcts[i]={x1,y1,x2,y2};
    cpss1.push_back(x1),cpss1.push_back(x2);
    cpss2.push_back(y1),cpss2.push_back(y2);
  }
  sort(cpss1.begin(),cpss1.end());
  sort(cpss2.begin(),cpss2.end());
  cpss1.erase(unique(cpss1.begin(),cpss1.end()),cpss1.end());
  cpss2.erase(unique(cpss2.begin(),cpss2.end()),cpss2.end());
  for(I i=0;i<n;i++){
    auto[x1,y1,x2,y2]=rcts[i];
    x1=lower_bound(cpss1.begin(),cpss1.end(),x1)-cpss1.begin();
    x2=lower_bound(cpss1.begin(),cpss1.end(),x2)-cpss1.begin();
    y1=lower_bound(cpss2.begin(),cpss2.end(),y1)-cpss2.begin();
    y2=lower_bound(cpss2.begin(),cpss2.end(),y2)-cpss2.begin();
    rcts[i]={x1,y1,x2,y2};
    ps1[x1]++,ps1[x2+1]--;
  }
  for(I i=0;i+1<cpss1.size();i++)ps1[i+1]+=ps1[i];
  for(I i=0;i<cpss1.size();i++)if(ps1[i]>=n-1){
    fill_n(ps2,cpss2.size()+1,0);
    for(I j=0;j<n;j++){
      auto[x1,y1,x2,y2]=rcts[j];
      if(x1<=i&&i<=x2)ps2[y1]++,ps2[y2+1]--;
    }
    for(I j=0;j+1<cpss2.size();j++)ps2[j+1]+=ps2[j];
    for(I j=0;j<cpss2.size();j++)if(ps2[j]>=n-1)printf("%i %i\n",cpss1[i],cpss2[j]),exit(0);
  }
}