#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct Ip {
    vector<int> Parts;

    Ip (
        const string& source
    ) 
    {
        istringstream tokenize_stream(source);
        string s;
        while(getline(tokenize_stream, s, '.')) {
            Parts.push_back(stoi(s));
        }
    }
    Ip (){};
};

ostream& operator <<(ostream &Str, const Ip &ip) { 
    // print something from v to str, e.g: Str << v.getX();
    for(const int& part : ip.Parts) {
        Str << part;
        if(&part != &ip.Parts.back())
            Str << ".";
    }
    return Str;
}

vector<Ip> Ips;

int main() {
    string in;
    while(getline(cin, in)) {
        istringstream line_stream(in);
        string ip_string;
        if(getline(line_stream, ip_string, '\t')) 
            Ips.push_back(Ip(ip_string));
    }
    //sorting
    sort(Ips.begin(), Ips.end(), 
        [](const Ip& first, const Ip& second) -> bool {
            return (first.Parts[0] > second.Parts[0])
            || (first.Parts[0] == second.Parts[0] && first.Parts[1] > second.Parts[1])
            || (first.Parts[1] == second.Parts[1] && first.Parts[2] > second.Parts[2])
            || (first.Parts[2] == second.Parts[2] && first.Parts[3] > second.Parts[3]);
        });
    for(const Ip& ip : Ips) {
        cout << ip << endl;
    }
    //first byte is 1
    vector<Ip> filtered(Ips.size());
    auto it =  copy_if(Ips.begin(), Ips.end(), filtered.begin(), [](Ip i){ return i.Parts[0] == 1;});
    filtered.resize(distance(filtered.begin(), it));
    for(const auto& ip: filtered) {
        cout << ip << endl;
    }
    //first is 46, second is 70
    filtered.clear();
    filtered.resize(Ips.size());
    it =  copy_if(Ips.begin(), Ips.end(), filtered.begin(), [](Ip i){ return i.Parts[0] == 46 && i.Parts[1] == 70;});
    filtered.resize(distance(filtered.begin(), it));
    for(const auto& ip: filtered) {
        cout << ip << endl;
    }
    //any is 46
    filtered.clear();
    filtered.resize(Ips.size());
    it =  copy_if(Ips.begin(), Ips.end(), filtered.begin(), [](Ip i){ return find(i.Parts.begin(), i.Parts.end(), 46) != i.Parts.end();});
    filtered.resize(distance(filtered.begin(), it));
    for(const auto& ip: filtered) {
        cout << ip << endl;
    }
}