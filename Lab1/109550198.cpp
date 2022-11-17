#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

int getWeight(vector<int> group){
    int sum = 0;
    for(int i = 0; i <  group.size();i++){
        sum += group[i];
    }
    return sum;
}

int findFakeCoin(vector<int> group, int idx){
    if(group.size() == 0) return -1; 
    if(group.size() == 1) return idx;

    int l = group.size() / 3;
    vector<int> group1, group2, group3, group4;
    
    for(int i = 0; i <  group.size();i++){
        
        if(i / l == 0){
            group1.push_back(group[i]);
        }
        else if(i / l == 1){
            group2.push_back(group[i]);
        }
        else if(i / l == 2){
            group3.push_back(group[i]);
        }
        else{
            group4.push_back(group[i]);
        }
    }
    // cout<<"idx=" << idx <<endl;
    int idx1=idx;
    int idx2=idx+l ;
    int idx3=idx+2*l;
    int idx4=idx+3*l;

    int w1 = getWeight(group1);
    int w2 = getWeight(group2);
    int w3 = getWeight(group3);
    int w4 = getWeight(group4);


    if(w1 == w2){
        if(w4 == 0){
            if(group3.size()==2){
                group3.push_back(group1[0]);

            }
            return findFakeCoin(group3,idx3);
        }
        else{
            if(w3==w1){
                if(group4.size()==2){
                    group4.push_back(group2[0]);
                }

                return findFakeCoin(group4, idx4);
            }
            else{
                if(group3.size()==2){
                    group3.push_back(group1[0]);

                }
                return findFakeCoin(group3, idx3); 
            }
        }
    }
    else if(w1!=w2){

        if(w3==w1){
            if(group2.size()==2){
                group2.push_back(group3[0]);

            }
            return findFakeCoin(group2, idx2);
        }
        else{
            if(group1.size()==2){
                group1.push_back(group3[0]);
            }
            return  findFakeCoin(group1, idx);
        }
    }
    // never goes here
    return -1;
}

int main() {
    int n= 0;
   
    int temp;
    while(cin>>n ){
        vector<int> a;
    
        while(n--){

            cin>>temp;
            a.push_back(temp);
        }
    
    // cout << "print:" << endl;
    // for(int i=0; i<a.size(); i++){
            
    //         cout<<a[i]<<endl;
    //  }
        int result = findFakeCoin(a,0);

        cout<<result<<endl;    

    }
    
    return 0;
}