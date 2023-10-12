#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=2e5;
I inds[N],invs[N],poss[N],curs[N];
S u;
B cmp(I a,I b){
  return u[a]<u[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I n;cin>>n;
    S s;cin>>s;
    S t;cin>>t;
    u=s;
    iota(inds,inds+n,0),sort(inds,inds+n,cmp);
    iota(poss,poss+n,0),iota(curs,curs+n,0);
    for(I i=0;i<n;i++)invs[inds[i]]=i;
    I cnt1=0;
    for(I i=0;i<n;i++){
      I j=invs[i],k=curs[j],dis=abs(j-poss[i]);
      cnt1+=max(dis+dis-1,0);
      swap(curs[poss[i]],curs[j]);
      swap(poss[i],poss[k]);
    }
    u=t;
    iota(inds,inds+n,0),sort(inds,inds+n,cmp);
    iota(poss,poss+n,0),iota(curs,curs+n,0);
    for(I i=0;i<n;i++)invs[inds[i]]=i;
    I cnt2=0;
    for(I i=0;i<n;i++){
      I j=invs[i],k=curs[j],dis=abs(j-poss[i]);
      cnt2+=max(dis+dis-1,0);
      swap(curs[poss[i]],curs[j]);
      swap(poss[i],poss[k]);
    }
    sort(s.begin(),s.end());
    sort(t.begin(),t.end());
    if(s!=t){printf("NO\n");continue;}
    s.erase(unique(s.begin(),s.end()),s.end());
    if(s.size()!=t.size()){printf("YES\n");continue;}
    printf("%s\n",abs(cnt1-cnt2)%2?"NO":"YES");
  }
}