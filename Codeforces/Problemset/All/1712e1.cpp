#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I facs[2*N+1];
map<I,I>prms1;
vector<pair<I,I>>prms2;
vector<I>divs[2*N+1];
void add(I i,I j=0,I val=1){
  if(j==prms2.size()){divs[i].push_back(val);return;}
  auto[prm,cnt]=prms2[j];
  for(I k=0;k<=cnt;k++)add(i,j+1,val),val*=prm;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(facs,facs+2*N+1,0);
  for(I i=2;i*i<=2*N;i++)for(I j=i*i;j<=2*N;j+=i)facs[j]=min(facs[j],i);
  for(I i=1;i<=2*N;i++){
    prms1.clear();
    for(I j=i;j>1;j/=facs[j])prms1[facs[j]]++;
    prms2.assign(prms1.begin(),prms1.end()),add(i);
    sort(divs[i].begin(),divs[i].end());
  }
  I t;cin>>t;
  while(t--){
    I l,r;cin>>l>>r;
    Lli res=0;
    for(I i=l+2;i<=r;i++){
      auto upp=lower_bound(divs[i].begin(),divs[i].end(),i);
      auto low=lower_bound(divs[i].begin(),divs[i].end(),l);
      Lli cnt1=upp-low;
      res+=(Lli)(i-l)*(i-l-1)/2;
      res-=cnt1*(cnt1-1)/2;
      if(i%3==0&&i/3*2>=l){
        auto upp=lower_bound(divs[2*i].begin(),divs[2*i].end(),i);
        auto low=lower_bound(divs[2*i].begin(),divs[2*i].end(),max(i/3+1,l));
        Lli cnt2=upp-low;
        res-=max(cnt2-1,0ll);
      }
    }
    printf("%lli\n",res);
  }
}