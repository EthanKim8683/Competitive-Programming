#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
I cnts[26];
vector<I>cpss;
vector<I>ress;
I inds[26];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    fill_n(cnts,26,0);
    cpss.clear();
    for(auto c:s)cnts[c-'a']++,cpss.push_back(c-'a');
    sort(cpss.begin(),cpss.end());
    cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
    I mid=cpss.size()/2;
    ress.clear();
    for(I i=0;i<cpss.size();i++){
      if(i%2==0)ress.push_back(cpss[mid+i/2]);
      if(i%2==1)ress.push_back(cpss[i/2]);
    }
    B vld=0;
    iota(inds,inds+ress.size(),0);
    do{
      vld=1;
      for(I i=0;i+1<ress.size();i++)vld&=abs(ress[inds[i]]-ress[inds[i+1]])!=1;
    }while(!vld&&next_permutation(inds,inds+ress.size()));
    if(!vld){printf("No answer\n");continue;}
    for(I i=0;i<ress.size();i++){
      I j=ress[inds[i]];
      for(I k=0;k<cnts[j];k++)printf("%c",j+'a');
    }
    printf("\n");
  }
}