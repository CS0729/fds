#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;
class Student{
public:
    string student_id;
    string name;
    map<string, double> course;
    double average;
    void setAverage(){
    double sum = 0.0;
        for (auto it = this->course.begin(); it != this->course.end(); ++it) {
            sum += it->second;
        }
        this->average = sum / this->course.size();
    }
};
int main(){
    string input;
    map<string, Student> studentMap;
    vector<string> course1;
    while(getline(cin,input)){
        size_t pos;
        string token;
        vector<string>data;
        while ((pos = input.find(", ")) != string::npos) {
            token = input.substr(0, pos);
            data.push_back(token);
            input.erase(0, pos + 2);
        }
        data.push_back(input);
        if(data.size()==2){
            studentMap[data[0]].student_id=data[0];
            studentMap[data[0]].name=data[1];
        }
        if(data.size()==3){
            if (find(course1.begin(), course1.end(), data[1]) == course1.end()) {
                course1.push_back(data[1]);
            }
            map<string,Student>::iterator it;
            it=studentMap.find(data[0]);
            double score=stod(data[2]);  //字符串转化为double
            it->second.course[data[1]]=score;
        }
    }
 
    for (auto &it: studentMap) {
        it.second.setAverage();
    }
 

    cout<<"student id, name, ";
    for (auto &course_name : course1) {
        cout<<course_name<<", ";
    }
    cout<<"average"<<endl;

    for (auto &it : studentMap) {
        cout << it.second.student_id << ", " << it.second.name << ", ";
        for (auto &course_name : course1) {
            if (it.second.course.find(course_name) != it.second.course.end()) {
                cout << it.second.course[course_name] << ", ";
            } else {
                cout << ", ";
            }
        }
        cout << fixed << setprecision(1) << it.second.average << endl;
    }
}