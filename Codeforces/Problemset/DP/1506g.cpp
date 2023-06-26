#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=2e5;
I upps[26];
vector<I>stks;
B uses[26],imms[26];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    fill_n(upps,26,0);
    for(I i=0;i<n;i++){
      I a=s[i]-'a';
      upps[a]=max(upps[a],i);
    }
    fill_n(uses,26,0),fill_n(imms,26,0);
    stks.clear();
    for(I i=0;i<n;i++){
      I a=s[i]-'a';
      if(upps[a]==i)imms[a]=1;
      if(uses[a])continue;
      while(stks.size()){
        I b=stks.back();
        if(imms[b]||b>a)break;
        stks.pop_back(),uses[b]=0;
      }
      stks.push_back(a),uses[a]=1;
    }
    for(auto a:stks)printf("%c",a+'a');
    printf("\n");
  }
}