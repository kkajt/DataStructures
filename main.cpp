#include <iostream>
#include <string>
#include <functional>
#include <sstream>
#include <vector>
#include <fstream>
#include <regex>
#include "header.h"

using namespace std;

// makes basic validation of arguments
bool checkArguments(int argc, char* argv[]) {
    if (argc < 3 || strcmp(argv[1],"--type")!=0 || (strcmp(argv[2],"rbt")!=0 && strcmp(argv[2],"bst")!=0 && strcmp(argv[2],"hmap")!=0)) return false;
    return true;
}

// cuts chars different to [a-zA-Z] from beginning and end of the string
string preparestring(string s) {
    size_t leftoffset = 0;
    size_t rightoffset = 0;
    regex left("[A-Za-z].*");
    regex right(".*[A-Za-z]");

    if (!regex_match(s, left))
    {
        leftoffset++;
        rightoffset++;
    }

    if (!regex_match(s, right))
    {
        rightoffset++;
    }
    s = s.substr(leftoffset, s.size() - rightoffset);
    return s;
}

// executes given line - recognizes command and invokes proper functions on DataStructure
void executeline(string line, DataStructure* p, struct counter *c) {

    clock_t start, end, startload =0 , endload =0;
    end = 0;
    double time_exec = 0.0, time_load = 0.0;
    istringstream iss(line);
    vector<string>* v = new vector<string>;
    string word;
    do {
        iss >> word;
        v->push_back(word);
    } while (iss);

    start = clock();
    if (v->at(0) == "insert") {
        p->insert(preparestring(v->at(1)));
        c->insert_num++;
        if (c->max_elem_num < p->getsize()) c->max_elem_num = p->getsize();
    }
    else if (v->at(0) == "load"){
        // if given command is load, programme should open specified file and insert all values from it
        startload = clock();
        string value;
        ifstream fin;
        fin.open(v->at(1), ifstream::in);
        while(fin>>value) {
            p->insert(preparestring(value));
            if (c->max_elem_num < p->getsize()) c->max_elem_num = p->getsize();
            //c->insert_num++;
        }
        fin.close();
        endload = clock();
        c->load_num++;
    }
    else if (v->at(0) == "delete") {
        p->deleteelement(v->at(1));
        c->delete_num++;
    }
    else if (v->at(0) == "find") {
        p->find(v->at(1));
        c->find_num++;
    }
    else if (v->at(0)== "min") {
        p->min();
        c->min_num++;
    }
    else if (v->at(0) == "max") {
        p->max();
        c->max_num++;
    }
    else if (v->at(0) == "successor") {
        p->successor(v->at(1));
        c->successor_num++;
    }
    else if (v->at(0) == "inorder") {
        p->inorder();
        c->inorder_num++;
    }
    else exit(EXIT_FAILURE);
    end = clock();

    // count time to 10^-4sec from processor clock
    time_exec = (double) ((end - start) * 1000) / CLOCKS_PER_SEC;
    time_load = (double) ((endload - startload) * 1000) / CLOCKS_PER_SEC;
    c->time_executing+=time_exec;
    c->time_load += time_load;

    delete v;
}

// prints collected statistics to standard error
void printstatistics(struct counter* c) {
    cerr<<"Statistics:"<<endl;
    cerr<<"Total execution time  (10^-4 s): "<<c->time_total<<endl;
    cerr<<"Time working on structures  (10^-4 s): "<<c->time_executing<<endl;
    cerr<<"Load time (10^-6 s): "<<c->time_load<<endl;
    cerr<<"Insert: "<<c->insert_num<<endl;
    cerr<<"Delete: "<<c->delete_num<<endl;
    cerr<<"Load: "<<c->load_num<<endl;
    cerr<<"Find: "<<c->find_num<<endl;
    cerr<<"Min: "<<c->min_num<<endl;
    cerr<<"Max: "<<c->max_num<<endl;
    cerr<<"Inorder: "<<c->inorder_num<<endl;
    cerr<<"Successor: "<<c->successor_num<<endl;
    cerr<<"Maximum elements in structure during execution: "<<c->max_elem_num<<endl;
    cerr<<"End element number in structure: "<<c->end_elem_num<<endl;
}

// performs test of HMap using speicfied file
// sets different breakpoints for HMap to change its array element from List to RBT and performs commands, printing
// its time of execution
void testHMap() {
    int repetitions = 1, breakpoint;
    int l=100, h=300;
    HMap* map;

    for (int i=0; i<repetitions; i++) {
        for (int j=l; j<=h; j++) {
            map = new HMap();
            map->setnt(j);
            ifstream myfile("./HMapTests/testHMap400.txt");
            clock_t start, end;
            start = clock();
            string line;
            getline(myfile, line);
            int n = stoi(line);
            if (n<0) exit(EXIT_FAILURE);
            struct counter* c = new counter();

            for (int i=0; i<n; i++) {
                getline(myfile, line);
                executeline(line, map, c);
            }
            end = clock();
            c->time_total = (double) ((end - start) * 1000) / CLOCKS_PER_SEC;
            c->end_elem_num = map->getsize();
            cerr<<c->time_executing<<endl;
            delete map;
            delete c;
        }
    }


}

// gets first line of standard input, and then executes next lines this amount of times
void readcommands(DataStructure *p) {
    clock_t start, end;
    start = clock();
    string line;
    getline(cin, line);
    int n = stoi(line);
    if (n<0) exit(EXIT_FAILURE);
    struct counter* c = new counter();

    for (int i=0; i<n; i++) {
        getline(cin, line);
        executeline(line, p, c);
    }
    end = clock();
    c->time_total = (double) ((end - start) * 1000) / CLOCKS_PER_SEC;
    c->end_elem_num = p->getsize();
    printstatistics(c);
    delete p;
    delete c;
}

int main(int argc, char* argv[]) {

    if (!checkArguments(argc, argv)) return 1;

    DataStructure* p;
    if (strcmp(argv[2], "bst")==0) p = new BST();
    else if (strcmp(argv[2], "rbt")==0) p = new RBT();
    else if (strcmp(argv[2],"hmap")==0) {
        p = new HMap();
    }
    readcommands(p);

    // if want to perform test on HMap, comment 'readcommands(p)' and uncomment below
    //testHMap();

    return 0;
}