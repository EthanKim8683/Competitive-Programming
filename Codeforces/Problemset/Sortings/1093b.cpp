#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    sort(s.begin(),s.end());
    B pal=1;
    for(I i=0,j=s.size()-1;i<j;i++,j--)pal&=s[i]==s[j];
    if(pal){printf("-1\n");continue;}
    printf("%s\n",s.c_str());
  }
}