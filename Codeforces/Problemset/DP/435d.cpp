#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=400;
const I M=400;
C cels[N][M+1];
I psh[N][M+1],psv[M][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)psh[i][j+1]=psv[j][i+1]=cels[i][j]-'0';
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)psh[i][j+1]+=psh[i][j];
  for(I i=0;i<m;i++)for(I j=0;j<n;j++)psv[i][j+1]+=psv[i][j];
  I res=0;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)if(cels[i][j]=='0'){
    for(I k=1;j+k<m&&i+k<n&&cels[i][j+k]=='0'&&cels[i+k][j+k]=='0';k++)res+=psv[j+k][i+k+1]-psv[j+k][i]==0;
    for(I k=1;j+k<m&&i-k>=0&&cels[i][j+k]=='0'&&cels[i-k][j+k]=='0';k++)res+=psv[j+k][i+1]-psv[j+k][i-k]==0;
    for(I k=1;i+k<n&&j+k<m&&cels[i+k][j]=='0'&&cels[i+k][j+k]=='0';k++)res+=psh[i+k][j+k+1]-psh[i+k][j]==0;
    for(I k=1;i-k>=0&&j+k<m&&cels[i-k][j]=='0'&&cels[i-k][j+k]=='0';k++)res+=psh[i-k][j+k+1]-psh[i-k][j]==0;
    for(I k=1;j+k<m&&i-k>=0&&i+k<n&&cels[i-k][j+k]=='0'&&cels[i+k][j+k]=='0';k++)res+=psv[j+k][i+k+1]-psv[j+k][i-k]==0;
    for(I k=1;j-k>=0&&i-k>=0&&i+k<n&&cels[i-k][j-k]=='0'&&cels[i+k][j-k]=='0';k++)res+=psv[j-k][i+k+1]-psv[j-k][i-k]==0;
    for(I k=1;i+k<n&&j-k>=0&&j+k<m&&cels[i+k][j-k]=='0'&&cels[i+k][j+k]=='0';k++)res+=psh[i+k][j+k+1]-psh[i+k][j-k]==0;
    for(I k=1;i-k>=0&&j-k>=0&&j+k<m&&cels[i-k][j-k]=='0'&&cels[i-k][j+k]=='0';k++)res+=psh[i-k][j+k+1]-psh[i-k][j-k]==0;
  }
  printf("%i\n",res);
}