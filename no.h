
#ifndef NO_H
#define NO_H
#include <iostream>
#include <string>

using namespace std;

class No
{
private:
    int iD;

public:
    No(){};
    ~No(){};
    char review_id[90];
    char review_text[3000];
    int upvote;
    char version[10];
    char posted_data[20];
    int getId() { return iD; };
    void setId(int i) { iD = i; };
};

#endif // NO_H