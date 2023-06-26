#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I MAX=1e9;
I cnts[26];
I inds[26];
vector<I>reps;
vector<I>rems;
B cmp(I a,I b){
  return cnts[a]>cnts[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    fill_n(cnts,26,0);
    for(auto c:s)cnts[c-'a']++;
    iota(inds,inds+26,0);
    sort(inds,inds+26,cmp);
    pair<I,I>res={MAX,-1};
    for(I i=1;i<=26;i++)if(n%i==0){
      I cnt=0;
      for(I j=0;j<i;j++)cnt+=n/i-min(cnts[inds[j]],n/i);
      res=min(res,{cnt,i});
    }
    auto[cnt,unq]=res;
    fill_n(cnts,26,0);
    reps.clear(),rems.clear();
    for(I i=0;i<n;i++){
      I k=-1;
      for(I j=0;j<unq;j++)if(s[i]-'a'==inds[j])k=j;
      if(k!=-1&&cnts[k]<n/unq)cnts[k]++;
      else reps.push_back(i);
    }
    for(I i=0;i<unq;i++)for(I j=cnts[i];j<n/unq;j++)rems.push_back(inds[i]);
    for(auto i:reps)s[i]=rems.back()+'a',rems.pop_back();
    printf("%i\n",cnt);
    printf("%s\n",s.c_str());
  }
}