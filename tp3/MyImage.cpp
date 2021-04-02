#include "MyImage.hpp"
#include <time.h>
#include <iostream>
MyImage::MyImage(const wxString& fileName)
: wxImage(fileName) 
{
}

MyImage::MyImage(wxImage image)
: wxImage(image) 
{
}
 
MyImage::MyImage(int largeur, int hauteur)
: wxImage(largeur, hauteur) 
{
}

MyImage::MyImage()
: wxImage() 
{
}

void MyImage::Negative(){
    unsigned char * data = this->GetData() ;
    for(int i = 0 ; i < (this->GetHeight() * this->GetWidth() * 3); i++){
        data[i] = ~data[i];
    } 
}

void MyImage::Desaturate(){
    unsigned char * data = this->GetData() ; 
    for (int i = 0 ; i < (this->GetHeight() * this->GetWidth()*3) ; i = i + 3){
        float tmp = (data[i] * 0.2126 + data[i+1] * 0.7152 + data[i+2] * 0.0722) ; 
        data[i] = (unsigned char) tmp ; 
        data[i+1] = (unsigned char) tmp;
        data[i+2] = (unsigned char) tmp;
    }
}

void MyImage::Threshold(int seuil){
    this->Desaturate(); 
    unsigned char * data = this->GetData() ; 
    for (int i = 0 ; i < (this->GetHeight() * this->GetWidth()*3) ; i = i + 3){
        if (data[i] > seuil){
            data[i] = 255 ; 
            data[i+1] = 255;
            data[i+2] = 255;
        }else{
            data[i] = 0 ; 
            data[i+1] = 0;
            data[i+2] = 0;
        }
    }
    
}

void MyImage::MirrorArti(bool horizontal){
    unsigned char * data = this->GetData() ;
    if (horizontal){
        for (int y =0 ; y < this->GetHeight() ; y++){
            for (int x = 0 ; x < (this->GetWidth()/ 2) ; x++){
                for (int h = 0 ; h < 3 ; h++){
                    int indice1 = y * this->GetWidth()*3 + x*3 + h ;
                    int indice2 = (y+1) * this->GetWidth()*3 - (x+1)*3 + h ;
                    
                    unsigned char temp = data [indice1] ; 
                    data[indice1] = data[indice2] ;
                    data[indice2] = temp ; 
                }
            }
        }
        
    }else{
        for (int x = 0 ; x < this->GetWidth() ; x++){
            for (int y = 0 ; y < this->GetHeight()/2 ; y++){
                int id1 = x + y*this->GetWidth();
                int id2 = x + (this->GetHeight()-y-1) * GetWidth();
                
                for (int h = 0 ; h <3 ; h++){
                    
                    unsigned char temp = data [id1*3 +h] ; 
                    data[id1*3+h] = data[id2*3+h] ;
                    data[id2*3+h] = temp ;
                    
                }
            }
        }
    }
}


wxImage* MyImage::Rotate90(){
    
    unsigned char * data = this->GetData() ;
    wxImage * nouvelle_image = new wxImage(this->GetHeight() , this->GetWidth()) ; 
    unsigned char * newdata =  nouvelle_image->GetData() ; 

    int index = 0 ; 
    for (int i = 0 ; i < this->GetWidth() ; i++ ){
        for (int j = 1 ; j <= this->GetHeight(); j++){
            for (int h = 0 ; h < 3 ; h ++){
                newdata[index] = data[(i + (this->GetHeight() - j)*this->GetWidth())*3 +h] ; 
                index ++ ; 
            }
        }
    }
    return nouvelle_image ; 
    
}

void MyImage::Posterize(){
    unsigned char * data = this->GetData() ; 
    for (int i = 0 ; i < this->GetHeight() * this->GetWidth() *3; i ++){
        if (data[i] > (255/2)){
            data[i] = 255 ; 
        }else{
            data[i] = 0 ; 
        }
    }
}    

int MyImage::ComptageCouleurs () {
    std::map<int,int> compteur ; 
    unsigned char * data = this->GetData() ; 
    int couleurCourante ; 
    for (int i = 0 ; i < this->GetHeight() * this->GetWidth() *3 ; i = i+3){
        couleurCourante = data[i] + data[i+1] * 1000 + data[i+2] * 1000000 ; 
        if (compteur.find(couleurCourante) == compteur.end() ){
            compteur.insert (std::pair<int, int> (couleurCourante , 1)) ; 
        }
    }
    
    return compteur.size() ; 
}


void MyImage::EnhenceContrast(int minValue , int maxValue){
    unsigned char * data = this->GetData() ; 
    int d;
    int f;
    for (int i = 0 ; i < this->GetHeight() * this->GetWidth()*3 ; i ++) {
        f = (255 * maxValue) / (maxValue - minValue ) ;  
        d = 255/(maxValue - minValue) ; 
        data[i]  = f * data[i] + d ;
    }
}
