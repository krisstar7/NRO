#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <omp.h>
#include <ctime>
#include <unistd.h>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <set>

using namespace std;

std::string trim( const std::string & s )
{
  auto first = s.find_first_not_of( " \f\n\r\t\v" );
  auto last  = s.find_last_not_of ( " \f\n\r\t\v" );
  return (first == s.npos) ? "" : s.substr( first, last+1 );
}

//Klase za tocke in mreze
struct Point{
    int ID;
    double x;
    double y;
    bool isInner=false;
    // int nAdj;
    // int* idAdj; 
};

int main() {

    //Matrix A in b
    vector<vector<double>> A;
    vector<double> b;
    vector<double> T;
    double dx = 1.25;
    double dy = 1.25;
    int h = 100;
    int k = 24;
    const int n = 5754;
    constexpr size_t SIZE = static_cast<size_t>(n);

    //Beremo file
    string filename = "./primer2mreza.txt";

    ifstream infile;
    infile.open(filename);

    string temp;
    getline(infile, temp);

    string temp2;
    //Preberi stevilo tock
    istringstream iss(temp);
    iss >> temp2;
    iss >> temp2;
    // const int n = stoi(temp2);
    
    // COSNTEXPR size_t SIZE = 5357;
    // replace(string_first_line.begin(), string_first_line.end(), '=', ' ');
    
    //Inicijaliziram A, b, T
    
    for (int i=0; i<n; i++){
        T.push_back(0);
        b.push_back(0);

        vector<double> row;

        for(int j=0; j<n; j++){
            row.push_back(0);
        }
        A.push_back(row);

    }
    
    //Preberi tocke
    vector<Point> points;
    array<unordered_set<int>, SIZE> adjM;

    for(int i = 0; i<n; i++){
        getline(infile, temp);
        replace(temp.begin(), temp.end(), ';', ' ');
        replace(temp.begin(), temp.end(), ',', ' ');  

        string idTemp;
        string xTemp;
        string yTemp;

        istringstream iss(temp);
        iss >> idTemp;
        iss >> xTemp;
        iss >> yTemp;
    
        Point tempP;
        tempP.ID = stoi(idTemp);
        tempP.x = stoi(xTemp);
        tempP.y = stoi(yTemp);

        points.push_back(tempP);
    }

    getline(infile, temp);
    getline(infile, temp);
    
    //Preberi stevilo mreze
    istringstream issM(temp);
    issM >> temp2;
    issM >> temp2;
    int nMreze = stoi(temp2);
    // cout<<temp;

    //Preberi mreza i popolni adjacency matrix
    while (getline(infile, temp)){
        if (trim(temp).empty()) break;
         
        replace(temp.begin(), temp.end(), ';', ' ');
        replace(temp.begin(), temp.end(), ',', ' ');  

        string idTemp;
        string id1Temp;
        string id2Temp;
        string id3Temp;
        string id4Temp;

        istringstream iss(temp);
        iss >> idTemp;
        iss >> id1Temp;
        iss >> id2Temp;
        iss >> id3Temp;
        iss >> id4Temp;

        int p1 = stoi(id1Temp);
        int p2 = stoi(id2Temp);
        int p3 = stoi(id3Temp);
        int p4 = stoi(id4Temp);
        
        adjM[p1].insert(p2);
        adjM[p1].insert(p4);

        adjM[p2].insert(p1);
        adjM[p2].insert(p3);

        adjM[p3].insert(p2);
        adjM[p3].insert(p4);

        adjM[p4].insert(p1);
        adjM[p4].insert(p3);
        
        // if(stoi(idTemp)<100){
        //     printf("%d - %d - %d - %d\n", p1, p2, p3, p4);
        // }
    }

    //Proveri dali e inner
    int index = 0;
    for(auto tocka : adjM){
        int counter = 0;
        for(auto elem : tocka){
            counter++;
        }

        if(counter==4){
            points[index].isInner = true;
        }

        index++;
    }

    
    getline(infile, temp);
    getline(infile, temp);
    getline(infile, temp);
    getline(infile, temp);
    
    vector<int> T1;
    vector<int> T2;
    vector<int> q3;
    vector<int> T4;
    vector<int> T5ex;

    //Preberi pogoje
    //Pogoj 1
    while (getline(infile, temp)){
        if (trim(temp).empty()) break;
        int id = stoi(temp);
        T1.push_back(id);
    }

    getline(infile, temp);
    getline(infile, temp);

    //Pogoj 2
    while (getline(infile, temp)){
        if (trim(temp).empty()) break;
        int id = stoi(temp);
        T2.push_back(id);
    }

    getline(infile, temp);
    getline(infile, temp);

    //Pogoj 3
    while (getline(infile, temp)){
        if (trim(temp).empty()) break;
        int id = stoi(temp);
        q3.push_back(id);
    }

    getline(infile, temp);
    getline(infile, temp);

    //Pogoj 4
    while (getline(infile, temp)){
        if (trim(temp).empty()) break;
        int id = stoi(temp);
        T4.push_back(id);
    }

    getline(infile, temp);
    getline(infile, temp);
    getline(infile, temp);

    //Pogoj 5
    while (getline(infile, temp)){
        if (trim(temp).empty()) break;
        int id = stoi(temp);
        T5ex.push_back(id);
    }

    cout<<"T1: "<<T1[0]<<" - "<<T1.back()<<": "<<T1.size()-1<<endl;
    cout<<"T2: "<<T2[0]<<" - "<<T2.back()<<": "<<T2.size()-1<<endl;
    cout<<"q3: "<<q3[0]<<" - "<<q3.back()<<": "<<q3.size()-1<<endl;
    cout<<"T4: "<<T4[0]<<" - "<<T4.back()<<": "<<T4.size()-1<<endl;
    cout<<"T5ex: "<<T5ex[0]<<" - "<<T5ex.back()<<": "<<T5ex.size()-1<<endl;


    //Sestavamo A in b

    int counter=0;
    unordered_set<int> done;

    //Pog 1
    for(auto id : T1){
        if(done.find(id) != done.end()) continue;
        done.insert(id);
        A[counter][id] = 1;
        b[counter] = 400;
        counter++;
    }

    //Pog 2
    for(auto id : T2){
        if(done.find(id) != done.end()) continue;
        done.insert(id);
        A[counter][id] = 1;
        b[counter] = 100;
        counter++;
    }

    //Pog 4
    for(auto id : T4){
        if(done.find(id) != done.end()) continue;
        done.insert(id);
        A[counter][id] = 1;
        b[counter] = 600;
        counter++;
    }

    //Pog 3
    for(auto id : q3){
        if(done.find(id) != done.end()) continue;
        done.insert(id);
        for(auto elem : adjM[id]){
            if(points[elem].isInner)
                A[counter][elem] = 2;
            else
                A[counter][elem] = 1;
        }

        b[counter] = 0;

        counter++;
    }

    //Pog 5
    for(auto id : T5ex){
        if(done.find(id) != done.end()) continue;
        done.insert(id);
        //preveri rob ali notranjem
        if(points[id].isInner){
            //notr
            for(auto elem : adjM[id]){
                if(points[elem].isInner)
                    A[counter][elem] = 2;
                else
                    A[counter][elem] = 1;
            }
            A[counter][id] = -2*(3+(h*dx)/k);

        }else{
            //rob
            for(auto elem : adjM[id]){
                A[counter][elem] = 2;
            }
            A[counter][id] = -2*(2+(h*dx)/k);
        }

        b[counter] = -2*(h*dx*200)/k;
        counter++;
    }

    vector<int> s;
    s.reserve(T1.size()+T2.size()+q3.size()+T4.size()+T5ex.size());
    s.insert(s.end(), T1.begin(), T1.end());
    s.insert(s.end(), T2.begin(), T2.end());
    s.insert(s.end(), q3.begin(), q3.end());
    s.insert(s.end(), T4.begin(), T4.end());
    s.insert(s.end(), T5ex.begin(), T5ex.end());

    // cout<<s.size()<<endl;
    set<int> ss(s.begin(), s.end());
    // cout<<ss.size()<<endl;

    //Notranjost
    for(auto p : points){
        if(p.isInner){
            if(ss.find(p.ID) == ss.end()){
                A[counter][p.ID] = -4;
                for(auto elem : adjM[p.ID]){
                    A[counter][elem] = 1;
                }
                b[counter] = 0;

                counter++;
            }
        }
    }

    // cout<<n-counter<<endl;

    // int counter2=0;
    // for(auto p : points)
    //     if(p.isInner)
    //         counter2++;

    // cout<<counter2<<endl;

    


    return 0;
}