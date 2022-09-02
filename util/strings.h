//
// Created by sjhuang on 2022/8/28.
//

#ifndef WEB_SERVER_STRINGS_H
#define WEB_SERVER_STRINGS_H
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &str,const char &sign){
    int n = str.size();
    vector<string> ans;
    int prev = -1;
    for(int i  = 0; i < n; i++){
        char c = str[i];
        if(c == sign){
            ans.push_back(str.substr(prev, i - prev));
            prev = i;
        }else if(i == n - 1){
            ans.push_back(str.substr(prev, i - prev + 1));
        }
    }
    return ans;
}



#endif //WEB_SERVER_STRINGS_H
