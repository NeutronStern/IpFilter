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
    Ip () = default;

    bool operator>(const Ip another) const {
        return (Parts[0] > another.Parts[0])
            || (Parts[0] == another.Parts[0] && Parts[1] > another.Parts[1])
            || (Parts[1] == another.Parts[1] && Parts[2] > another.Parts[2])
            || (Parts[2] == another.Parts[2] && Parts[3] > another.Parts[3]);
    } 
    bool operator<(const Ip another) const {
        return (Parts[0] < another.Parts[0])
            || (Parts[0] == another.Parts[0] && Parts[1] < another.Parts[1])
            || (Parts[1] == another.Parts[1] && Parts[2] < another.Parts[2])
            || (Parts[2] == another.Parts[2] && Parts[3] < another.Parts[3]);
    } 
    bool operator==(const Ip another) const {
        return Parts[0] == another.Parts[0]
            && Parts[1] == another.Parts[1]
            && Parts[2] == another.Parts[2]
            && Parts[3] == another.Parts[3];
    } 
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
    sort(Ips.begin(), Ips.end(), greater<Ip>());
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