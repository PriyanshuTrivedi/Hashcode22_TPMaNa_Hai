#include <bits/stdc++.h>
using namespace std;
using ll=long long;
map<string,map<string,ll>> candidates;
map<string,vector<pair<string,ll>>> projects;
vector<pair<ll,pair<string,pair<ll,ll>>>> prj;
vector<pair<string,vector<string>>> final_ans;

// function that returns the vector of candidate who can make the project
vector<string> fulfilz(string project)
{
    vector<string> ans;
    bool check;

    // to keep check that a candidate is not taken more than once
    map<string,bool> vis;
    for(auto x:projects[project])
    {

        // x is pair of required skill and its required level
        check=false;

        // ***I noticed that traversing the candidates in reverse order gave us more points so u can try that also***
        for(auto y:candidates)
        {

            // y.second is the map of skill and level possed by the candidate
            // so if the the candidate has that skill and his level is greater or equal than the required level and that person is not already participating in that project, then push it in the ans vector
            if(y.second[x.first]>=x.second && vis.find(y.first)==vis.end() && y.second.find(x.first)!=y.second.end())
            {
                ans.push_back(y.first);
                vis[y.first]=true;
                check=true;
                break;
            }
        }

        // if there exists some required skill of some level of the project that is not fulfilled by any of the candidate then return empty vector
        if(!check)
        return {};
    }
    return ans;
}
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // input and output file
    // freopen("a_an_example.in.txt", "r", stdin);
    freopen("b_better_start_small.in.txt", "r", stdin);
    // freopen("c_collaboration.in.txt", "r", stdin);
    // freopen("d_dense_schedule.in.txt", "r", stdin);
    // freopen("e_exceptional_skills.in.txt", "r", stdin);
    // freopen("f_find_great_mentors.in.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ll c,p,n;
    ll i;
    string candidate_name,candidate_skill,project_name,required_skill;
    ll no_skills,roles,candidate_skill_lvl,skill_lvl_required,days_to_complete,score,due_date;
    cin>>c>>p;

    // inputing candidates information
    while(c--)
    {
        cin>>candidate_name>>no_skills;
        for(i=0;i<no_skills;i++)
        {
            cin>>candidate_skill>>candidate_skill_lvl;
            candidates[candidate_name][candidate_skill]=candidate_skill_lvl;
        }
    }

    // inputing  projects information
    while(p--)
    {
        cin>>project_name>>days_to_complete>>score>>due_date>>roles;

        // storing projects according to their score as first values so they can be sorted according to score in descending order
        // it can also be sorted according to due_date in descending order by just changing score to due_date and vice vers
        prj.push_back(make_pair(score,make_pair(project_name,make_pair(days_to_complete,due_date))));

        // projects is a map of vector so an empty vector has to be inserted
        projects.insert({project_name,vector<pair<string,ll>>(roles,{"?",0})});
        for(i=0;i<roles;i++)
        {
            cin>>required_skill>>skill_lvl_required;
            projects[project_name][i]={required_skill,skill_lvl_required};
        }
    }

    // sorting according to score and then checking if that project can be be made i.e. there are people with the required skills
    sort(prj.begin(),prj.end());
    reverse(prj.begin(),prj.end());
    for(auto x:prj)
    {

        // x.second.first is the name of the project so checking if can be made
        auto y=fulfilz(x.second.first);
        if(y.size()!=0)
        {

            // pushing a pair of project name and an empty vector of string
            final_ans.push_back(make_pair(x.second.first,vector<string>()));
            n=final_ans.size()-1;

            // pushing the candidate names
            for(auto z:y)
            final_ans[n].second.push_back(z);
        }
    }

    // printing the total number of projects and the candidates
    cout<<final_ans.size()<<"\n";
    for(auto x:final_ans)
    {
        cout<<x.first<<"\n";
        for(auto y:x.second)
        cout<<y<<" ";
        cout<<"\n";
    }
    return 0;
}