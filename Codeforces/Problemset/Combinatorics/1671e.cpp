#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=18;
const I PWN=1<<N;
const Lli MOD=998244353;
S strs[PWN];
Lli dp[PWN];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  I pwn=1<<n;
  for(I i=pwn-1;i>=1;i--){
    strs[i]=s[i-1],dp[i]=1;
    if(i>=pwn/2)continue;
    I j=i<<1,k=i<<1|1;
    if(strs[j]<strs[k])swap(j,k);
    strs[i]+=strs[j];
    strs[i]+=strs[k];
    (dp[i]*=dp[j])%=MOD;
    (dp[i]*=dp[k])%=MOD;
    if(strs[j]!=strs[k])(dp[i]*=2)%=MOD;
  }
  printf("%lli\n",dp[1]);
}
/*
for each subtree we can find the lexicographically smallest preorder string
possible after operations

if two adjacent subtrees' lexicographically smallest preorder strings are
equal, then an operation to swap them would not contribute to the number of
preorder strings of the entire tree

if they are different, they will each always produce different preorder strings
because, in the first level where they differ, the number of A's in one pair
of the first subtree will differ from the number of A's in its corresponding
pair in the second subtree, which will be reflected in the indices of that
pair in the final preorder string
*/