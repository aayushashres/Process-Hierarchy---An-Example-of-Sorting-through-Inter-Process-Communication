#ifndef NODE
#define NODE


class node
{
    private:
        int rid;
        char fname[100];
        char lname[100];
        int num_dependants;
        float income;
        int postalcode;
    public:
        node(int r, char* fn, char* ln, int nd, float i, int p);
        char* node_to_string(int index, float timetaken);
        char* node_in_string_format();
        void display();
        int getrid();
        int getnum_dependants();
        float getincome();
        int getpostalcode();
};

#endif