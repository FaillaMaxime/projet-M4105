#include <string>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include "MyImage.hpp"
#include <map> 
#endif

class MyHistogram
{
public:
    MyHistogram(MyImage * image) ;
    void GetDynamic (int * minValue, int * maxValue) ; 
private:
    MyImage * m_image;
    unsigned int m_tableau[256] ; 
};

