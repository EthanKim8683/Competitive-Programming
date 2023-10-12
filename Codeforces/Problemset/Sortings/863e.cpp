#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I MIN=-1e9;
pair<I,I>sets[N];
vector<I>cpss;
I ps[4*N+1];
vector<I>ncks;
I inds[N];
B reqs[N];
B cmp(I a,I b){
  return sets[a]<sets[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    sets[i]={l,r};
    cpss.push_back(l),cpss.push_back(l-1);
    cpss.push_back(r),cpss.push_back(r+1);
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++){
    auto[l,r]=sets[i];
    l=lower_bound(cpss.begin(),cpss.end(),l)-cpss.begin();
    r=lower_bound(cpss.begin(),cpss.end(),r)-cpss.begin();
    ps[l]++,ps[r+1]--,sets[i]={l,r};
  }
  for(I i=0;i<cpss.size();i++)ps[i+1]+=ps[i];
  for(I i=0;i<cpss.size();i++)if(ps[i]==1)ncks.push_back(i);
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0,j=0;i<n;i++)for(;j<ncks.size();j++){
    I x=ncks[j],k=inds[i];auto[l,r]=sets[k];
    if(x<l||x>r)break;
    reqs[k]=1;
  }
  for(I i=0;i<n;i++)if(!reqs[i])printf("%i\n",i+1),exit(0);
  printf("-1\n");
}