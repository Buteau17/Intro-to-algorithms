#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n , m;
    cin >> n >> m;

    vector<vector<int> > profit, dp;
    for(int i=0; i<=n ; i++){
        vector<int> tmp;
        tmp.resize(m+1);
        profit.push_back(tmp);
    }
    
    for(int i=0; i<=n ; i++){
        vector<int> tmp;
        tmp.resize(m+1);
        dp.push_back(tmp);
    }
    // Read the profit matrix
    
    for (int i = 1; i <= n; i++) {
        
        for (int j = 0; j <= m; j++) {
            
            cin >> profit[i][j];
            // cout<<i<<" "<<j<<" " << profit[i][j]<<endl;
            }
            
            }

    // Initialize the dp array with base cases
    for (int j = 0; j <= m; j++) {
        dp[0][j] = 0;
        
        }
        
        for (int i = 1; i <= n; i++) {
            
            dp[i][0] = 0;
    }
    // cout<<profit[1][1]<<endl;

    // Iterate over the projects and resources
    
    for (int i = 1; i <= n; i++) {
        
        for (int j = 0; j <= m; j++) {
            
            for (int k = 0; k <= j; k++) {
                
                dp[i][j] = max(dp[i][j], dp[i-1][j-k] + profit[i][k]);

                // if (i == 1 && j==1){

                //     cout<<dp[i][j]<<" "<<dp[i-1][j-k]<<" "<<profit[i][k]<<endl;

                // }

    }
    }
    }
    // cout<<"dp table"<<endl;
    // for(int i =0 ; i<n+1 ;i++){
    //     for (int j =0 ; j<m+1 ; j++){
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    // The maximum profit is dp[n][m]
    cout << dp[n][m] << endl;

    return 0;
}

