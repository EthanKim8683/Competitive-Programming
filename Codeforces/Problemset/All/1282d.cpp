#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=300;
I ask(S s){
  printf("%s\n",s.c_str()),fflush(stdout);
  I res;cin>>res;
  if(res==-1||res==0)exit(0);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m=ask("a")+1,n=min(m,N);
  S s=S(n,'a');
  I pre=ask(s);
  if(pre==n)ask(S(m-1,'b'));
  for(I i=0;i<n;i++){
    s[i]='b';
    I cur=ask(s);
    if(cur>pre)s[i]='a';
    else pre=cur;
  }
}
/*
we can find the length of s in two queries:

first query "a", which will return |s| - 1, the amount of characters to
insert to get s (assuming there is an a in s)

second, query S(n, 'a'), where n is the length approximation from earlier,
which will equal n if and only if a is not in s, since all n - 1 insertions
will be replaced with n - 1 replacements

then, we can set all remaining characters to a and one by one replace them with
b if doing so results in a lesser edit distance
*/