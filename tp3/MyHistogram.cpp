#include "MyHistogram.hpp"
#include <time.h>
#include <iostream>


MyHistogram::MyHistogram(MyImage * image) 
: m_image(image){
    unsigned char * data = m_image->GetData(); 
    for (int i = 0 ; i < 256 ; i++){
        m_tableau[i] = 0 ; 
    }
    
    for (int i = 0 ; i < m_image->GetHeight() * m_image->GetWidth() ; i++){
        m_tableau[data[i]] +=1 ; 
    }
    
    for (int i = 0 ; i < 256 ; i ++){
        std::cout << m_tableau[i] << std::endl ; 
    }

}

void MyHistogram::GetDynamic (int * minValue, int * maxValue) {
    unsigned char * data = m_image->GetData() ;
    int i = 0 ;  
    while (data[i] == 0 && i < 256){
        i++ ; 
    }
    * minValue = i-1 ; 
    
    i = 255;
    while (data[i] == 0 && i >=0){
        i-- ; 
    } 
    *maxValue = i+1 ; 
    
}
