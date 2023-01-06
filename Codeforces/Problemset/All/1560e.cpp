#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
using C=char;
map<I,I>tots;
I ords[26];
I lens[26];
I cnts[26];
C ress[26+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    tots.clear();
    for(I i=n-1,j=0;i>=0;i--){
      I c=s[i]-'a';
      if(!tots.count(c))ords[c]=j++;
      tots[c]++;
    }
    B res=1;
    for(auto[chr,tot]:tots){
      I ord=tots.size()-ords[chr];
      res&=tot%ord==0;
      lens[chr]=tot/ord;
    }
    fill_n(cnts,26,0);
    S str="";I acc=0;
    for(I i=0;i<n;i++){
      I c=s[i]-'a';
      cnts[c]++;
      acc+=cnts[c]==lens[c];
      res&=cnts[c]<=lens[c];
      str+=s[i];
      if(acc==tots.size())break;
    }
    S sim="";
    for(I i=tots.size()-1;i>=0;i--)for(auto chr:str)if(ords[chr-'a']<=i)sim+=chr;
    res&=sim==s;
    for(auto[chr,tot]:tots)ress[ords[chr]]=chr+'a';
    reverse(ress,ress+tots.size());
    ress[tots.size()]=0;
    if(!res){printf("-1\n");continue;}
    printf("%s %s\n",str.c_str(),ress);
  }
}