#ifndef  __TARGETVALUES_H
#define  __TARGETVALUES_H

class targetvalues{
    public:
        int targettime;
        int targetvalue;
        double status;
    targetvalues();    
    ~targetvalues();
    void setT(int);
    int  getT();
};
#endif
