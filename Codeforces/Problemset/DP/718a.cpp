#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,t;cin>>n>>t;
  S s;cin>>s;
  I j=0,k=-1;
  for(I i=0;i<n;i++)if(s[i]=='.')j=i+1;
  for(I i=n-1;i>=j;i--)if(s[i]>='5')k=i;
  if(k==-1)printf("%s\n",s.c_str()),exit(0);
  S res=s.substr(0,k);
  I cnt=1;
  for(k--;k>=j;k--){
    res[k]++;
    if(res[k]<'5'||cnt>=t)break;
    res.pop_back(),cnt++;
  }
  if(res[k]=='.'){
    res.pop_back();
    B car=1;
    for(k--;k>=0&&car;k--){
      res[k]++;
      car=res[k]>'9';
      if(car)res[k]='0';
    }
    if(car)res="1"+res;
  }
  printf("%s\n",res.c_str());
}