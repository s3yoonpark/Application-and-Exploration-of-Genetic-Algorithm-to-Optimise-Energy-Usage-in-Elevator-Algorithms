#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
using namespace std;

const int populationSize = 25000;
const int evolutionCycle = 25;
const int elevatorWeight = 2000;

const int humanWeight = 60;
const int distanceBetweenFloors = 3; 
const int accelerationGravity = 10; 

const int mutationRate = 50;
const int survivalRate = 20;

struct Query
{
    int from;
    int to;
};

int N, curLevel;
vector<vector<pair<int, int>>> population;
vector<Query> requests;

int rng(int a, int b)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distr(a, b);
    return distr(gen);
}

int cost(vector<pair<int, int>>& arr)
{
    int ans = 0;
    int num = 0;
    int last = curLevel;
    for (int i = 0; i < (int)arr.size(); ++i)
    {
        int rqNum = arr[i].first;
        if (arr[i].second == 0)
        {
            ans += (num * humanWeight + elevatorWeight) * accelerationGravity * abs(last - requests[rqNum - 1].to) * distanceBetweenFloors;
            last = requests[rqNum - 1].to;
            --num;
        }
        else
        {
            ans += (num * humanWeight + elevatorWeight) * accelerationGravity * abs(last - requests[rqNum - 1].from) * distanceBetweenFloors;
            last = requests[rqNum - 1].from;
            ++num;
        }
    }
    return ans;
}

bool cmp(vector<pair<int, int>> &A, vector<pair<int, int>> &B)
{
    return cost(A) < cost(B);
}

vector<pair<int, int>> generate()
{
    vector<pair<int, int>> ans;
    vector<int> waitingList = vector<int>(N);
    for (int i = 0; i < N; ++i)
        waitingList[i] = i + 1;
    vector<int> taken;
    while (!waitingList.empty() || !taken.empty())
    {
        bool decision = rng(0, 1);
        if (waitingList.empty())
            decision = 0;
        if (decision == 0 && !taken.empty())
        {
            // dropping someone off
            int randomInd = rng(0, (int)taken.size() - 1);
            int passenger = taken[randomInd];
            taken.erase(taken.begin() + randomInd);
            ans.push_back(make_pair(passenger, 0));
        }
        if (decision == 1)
        {
            int randomInd = rng(0, (int)waitingList.size() - 1);
            int passenger = waitingList[randomInd];
            waitingList.erase(waitingList.begin() + randomInd);
            taken.push_back(passenger);
            ans.push_back(make_pair(passenger, 1));
        }
    }
    return ans;
}

vector<pair<int, int>> crossover(vector<pair<int, int>> &monoParent)
{
    int die = rng(1, 100);
    if (die <= mutationRate)
    {
        return generate();
    }
    else
    {
        vector<pair<int, int>> ans;
        while (1)
        {
            ans = monoParent;
            int ind1 = rng(0, (int)monoParent.size() - 1);
            int ind2 = rng(0, (int)monoParent.size() - 1);
            swap(ans[ind1], ans[ind2]);
            vector<bool> chk(N + 1, 0);
            bool invalid = 0;
            for (int i = 0; i < (int)ans.size() && !invalid; ++i)
            {
                if (ans[i].second == 0 && !chk[ans[i].first])
                {
                    invalid = 1;
                }
                if (ans[i].second == 1)
                {
                    chk[ans[i].first] = 1;
                }
            }
            if (invalid)
                continue;
            break;
        }
        return ans;
    }
}

int main()
{
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout); 
    cin >> N >> curLevel;
    for (int i = 0; i < N; ++i)
    {
        int a, b;
        cin >> a >> b;
        requests.push_back({a, b});
    }

    auto timeStart = chrono::high_resolution_clock::now();

    for (int i = 0; i < populationSize; ++i)
    {
        population.push_back(generate());
    }
    for (int i = 0; i < evolutionCycle; ++i)
    {
        sort(population.begin(), population.end(), cmp);
        // cout << i + 1 << "th evolution: " << cost(population[0]) << '\n';
        int fittest = (populationSize)*survivalRate / 100;
        int remaining = populationSize - fittest;
        vector<vector<pair<int, int>>> newPopulation;
        for (int j = 0; j < fittest; ++j)
        {
            newPopulation.push_back(population[j]);
        }
        for (int j = 0; j < remaining; ++j)
        {
            // new cross over function
            vector<pair<int, int>> monoParent = population[rng(0, fittest - 1)];
            newPopulation.push_back(crossover(monoParent));
        }
        swap(population, newPopulation);
    }
    sort(population.begin(), population.end(), cmp);
    cout << cost(population[0]) << '\n'; 
    // cout << "BEST ONE: " << cost(population[0]) << '\n';
    // for (auto& x : population[0]) {
    //     cout<<x.first<<' '<<x.second<<"  "; 
    // }
    // cout<<'\n'; 
    auto timeEnd = chrono::high_resolution_clock::now();
    // cout << chrono::duration_cast<chrono::milliseconds>(timeEnd - timeStart).count() << "ms" << '\n';
    return 0;
}
