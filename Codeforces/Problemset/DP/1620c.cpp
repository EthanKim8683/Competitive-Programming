#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

vector<I>sizs;
vector<I>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;Lli x;cin>>n>>k>>x,x--;
    S s;cin>>s;
    sizs.clear(),ress.clear();
    for(I i=0;i<n;i++){
      I len=0;
      while(i<n&&s[i]=='*')i++,len++;
      if(len)sizs.push_back(k*len+1);
    }
    reverse(sizs.begin(),sizs.end());
    for(auto siz:sizs)ress.push_back(x%siz),x/=siz;
    reverse(ress.begin(),ress.end());
    S res="";
    for(I i=0,j=0;i<n;){
      if(s[i]=='a'){res+='a',i++;continue;}
      while(i<n&&s[i]=='*')i++;
      for(I k=0;k<ress[j];k++)res+='b';
      j++;
    }
    printf("%s\n",res.c_str());
  }
}