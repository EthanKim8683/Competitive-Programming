#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=2e5;

vector<I>cnts[2];
I ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    cnts[0].clear();
    cnts[1].clear();
    for(I i=0;i<n;i++){
      I c=s[i]=='1';
      I j;
      if(cnts[!c].size())cnts[c].push_back(j=cnts[!c].back()),cnts[!c].pop_back();
      else cnts[c].push_back(j=cnts[0].size()+cnts[1].size());
      ress[i]=j;
    }
    printf("%i\n",cnts[0].size()+cnts[1].size());
    for(I i=0;i<n;i++)printf("%i ",ress[i]+1);
    printf("\n");
  }
}