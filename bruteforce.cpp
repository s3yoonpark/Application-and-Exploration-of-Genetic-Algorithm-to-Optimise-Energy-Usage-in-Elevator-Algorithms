#include <bits/stdc++.h>
using namespace std; 

struct Query {
    int from, to; 
}; 

const int elevatorWeight = 2000; 
const int humanWeight = 60; 
const int distanceBetweenFloors = 3; 
const int accelerationGravity = 10; 

int n, curLevel; 
int ans = INT_MAX; 
bool completed[50][2]; 
vector<Query> rq; 

vector<pair<int,int>> temp; 
int s = 0; 
int num = 0; 

void dfs() {
    if (s > INT_MAX) return; 
    if ((int)temp.size() == n*2) {
        ans = min(ans, s); 
        return; 
    }
    int last; 
    if (temp.empty()) {
        last = curLevel; 
    } else {
        if (temp.back().second == 1) {
            last = rq[temp.back().first].from; 
        } else {
            last = rq[temp.back().first].to; 
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!completed[i][0]) {
            // picking someone up 
            temp.push_back(make_pair(i, 1)); 
            completed[i][0] = 1; 
            s += (num*humanWeight+elevatorWeight)*accelerationGravity*abs(last-rq[i].from)*distanceBetweenFloors; 
            ++num; 
            dfs(); 
            temp.pop_back(); 
            --num; 
            s -= (num*humanWeight+elevatorWeight)*accelerationGravity*abs(last-rq[i].from)*distanceBetweenFloors; 
            completed[i][0] = 0; 
        } 
        if (completed[i][0] && !completed[i][1]) {
            temp.push_back(make_pair(i, 0)); 
            completed[i][1] = 1; 
            s += (num*humanWeight+elevatorWeight)*accelerationGravity*abs(last-rq[i].to)*distanceBetweenFloors; 
            --num; 
            dfs(); 
            temp.pop_back(); 
            completed[i][1] = 0; 
            ++num; 
            s -= (num*humanWeight+elevatorWeight)*accelerationGravity*abs(last-rq[i].to)*distanceBetweenFloors; 
        }
    }
    return; 
}

int main() {
    freopen("input.txt", "r", stdin); 
    memset(completed, 0, sizeof(completed)); 
    cin >> n >> curLevel; 
    rq = vector<Query>(n); 
    for (int i = 0; i < n; ++i) {
        cin >> rq[i].from >> rq[i].to; 
    }
    vector<pair<int,int>> temp; 
    int s = 0; 
    dfs(); 
    cout << ans << '\n'; 

    return 0; 
}
