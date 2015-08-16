#ifndef  __TARGETVALUES_H
#define  __TARGETVALUES_H

class targetvalues{
    public:
        int targettime;
        int targetvalue;
        int div;
        double status;
    targetvalues();    
    ~targetvalues();
    void setT(int);
    int  getT();
    void setDiv(int);
    int  getDiv();
};
#endif
