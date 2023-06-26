#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
I cnts[26];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    S t;cin>>t;
    fill_n(cnts,26,0);
    for(auto c:s)cnts[c-'a']++;
    if(!(cnts[0]&&cnts[1]&&cnts[2])||t!="abc"){
      for(I i=0;i<26;i++)for(I j=0;j<cnts[i];j++)printf("%c",i+'a');
    }else{
      for(I i=0;i<cnts[0];i++)printf("a");
      for(I i=0;i<cnts[2];i++)printf("c");
      for(I i=0;i<cnts[1];i++)printf("b");
      for(I i=3;i<26;i++)for(I j=0;j<cnts[i];j++)printf("%c",i+'a');
    }
    printf("\n");
  }
}