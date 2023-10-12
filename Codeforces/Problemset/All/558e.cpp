#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=1e5;
const I K=317;
const I L=(N+K-1)/K;
I typs[L];
I cols1[N];
I cols2[L],cnts[L][26];
I sizs[L];
I tots[26];
I n;
void slv(I i){
  fill_n(cnts[i],26,0);
  for(I j=i*K;j<min((i+1)*K,n);j++)cnts[i][cols1[j]]++;
}
I get(I i){
  if(typs[i/K]==0)return cols1[i];
  if(typs[i/K]==1)return cols2[i/K];
  return-1;
}
void cnv(I i){
  typs[i]=0;
  fill_n(cnts[i],26,0);
  for(I j=i*K;j<min((i+1)*K,n);j++)cnts[i][cols1[j]=cols2[i]]++;
}
void set1(I i,I col){
  if(typs[i/K]==1)cnv(i/K);
  cols1[i]=col;
}
void set2(I i,I col){
  typs[i]=1,cols2[i]=col;
}
void add1(I i){
  tots[get(i)]++;
}
void add2(I i){
  if(typs[i]==0)for(I j=0;j<26;j++)tots[j]+=cnts[i][j];
  if(typs[i]==1)tots[cols2[i]]+=sizs[i];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>n>>q;
  S s;cin>>s;
  for(I i=0;i<n;i++)cols1[i]=s[i]-'a';
  for(I i=0;i<n;i++){
    cnts[i/K][cols1[i]]++;
    sizs[i/K]++;
  }
  while(q--){
    I i,j,k;cin>>i>>j>>k,i--;
    fill_n(tots,26,0);
    for(I l=i;l<j;){
      if(l%K==0&&j>=l+sizs[l/K]){
        add2(l/K);
        l+=K;
      }else{
        add1(l);
        l++;
      }
    }
    if(k==0){
      I m=i+tots[26-1],o=26-1;
      for(I l=i;l<j;){
        while(m<=l)m+=tots[--o];
        if(l%K==0&&m>=l+sizs[l/K]){
          set2(l/K,o);
          l+=K;
        }else{
          set1(l,o);
          l++;
        }
      }
    }
    if(k==1){
      I m=i+tots[0],o=0;
      for(I l=i;l<j;){
        while(m<=l)m+=tots[++o];
        if(l%K==0&&m>=l+sizs[l/K]){
          set2(l/K,o);
          l+=K;
        }else{
          set1(l,o);
          l++;
        }
      }
    }
    for(I l=i/K;l<=(j-1)/K;l++)if(typs[l]==0)slv(l);
  }
  for(I i=0;i<n;i++)printf("%c",get(i)+'a');
}
/*
if we divide the array into blocks of size K, each update costs at most n / K
* 26 + K * 26 operations

this is because at most n / K blocks will be entirely one character and at most
26 blocks will contain multiple characters
*/