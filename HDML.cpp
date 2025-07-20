#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <queue>
using namespace std;

class tag{
    public:
    string name;
    tag* next = nullptr;
    tag* prev = nullptr;
    vector<pair<string,string>> data;
};

tag* pnt = nullptr;

void solve(vector<char> &data);

int main() {   
    int n; cin >> n;
    int q; cin >> q;
    vector<char> stack;
    cin.ignore();
    while(n>0){
        n--;
        string data;
        getline(cin,data);
        for (int x=0; x < (int)data.size(); x++){
            char s = data[x];
            if(data[1] == '/' && pnt->prev != nullptr){
                tag* temp = pnt;
                pnt = pnt->prev;
                if(temp != nullptr){
                    pnt->next = temp;
                }
                stack.clear();
            }else if(s == '<' && data[1] != '/'){
                tag* temp = pnt;
                pnt = new tag();
                if(temp != nullptr){
                    pnt->prev = temp;
                }
            }else if(s == '>' && data[1] != '/') {
                solve(stack);
                stack.clear();
            }else{
                stack.push_back(s);
            }
        }
    }
    tag* root = pnt;
    while(q>0){
        q--;
        queue<string> tag;
        string data;
        string value;
        getline(cin,data);
        for(char s: data){
            if(s == '.'){
                tag.push(value);
                value.clear();
            }else if(s == '~'){
                tag.push(value);
                value.clear();
            }else{
                value.push_back(s);
            }
        }
        while(tag.size()){
            if(pnt->name == tag.front()){
                tag.pop();
            }else if(pnt->next != nullptr){
                pnt = pnt->next;
                tag.pop();
            }else{
                break;
            }
        }
        bool found = false;
        for(int x=0; x < (int)pnt->data.size(); x++){
            if(pnt->data[x].first == value){
                string out = pnt->data[x].second;
                if (!out.empty() && out.front() == '"' && out.back() == '"'){
                out = out.substr(1, out.size() - 2);
                }
                printf("%s\n",out.c_str());
                found = true; 
            }
        }
        if(!found){
            cout << "Not Found!" << endl;
        }
        pnt = root; // Reset to root after each query
    }
    return 0;
}

void solve(vector<char> &data){
    string temp;
    vector<string> substack;
    for(char s : data){
        if(s == ' '){
            substack.push_back(temp);
            temp.clear();
        }else{
            temp += s;
        }
    }
    substack.push_back(temp); // Add the last part
    pnt->name = substack[0];
    if(substack.size() >= 4){
        for(int x=1; x < (int)substack.size(); x += 3){
            pnt->data.push_back(std::make_pair(substack[x],substack[x+2]));
        }
    }
}