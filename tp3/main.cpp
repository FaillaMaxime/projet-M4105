
// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include <iostream>
#include "/users/info/etu-s4/faillam/M4105_C++/tp3/MyThresholdDialog.hpp"
#include "/users/info/etu-s4/faillam/M4105_C++/tp3/MyRotateDialog.hpp"
#ifndef WX_PRECOMP
#include <wx/wx.h>
//#include "MyImage.hpp"
#include "MyHistogram.hpp"
#endif

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};

class MyPanel: public wxPanel
{
public:
    MyPanel( wxWindow *parent ) ;
    ~MyPanel() ;
    void OpenImage(wxString fileName) ; 
    void OnPaint(wxPaintEvent &WXUNUSED(event)) ;
    void saveImage(wxString save) ; 
    void MirrorImage(bool dir) ; 
    void BlurImage() ;
    void Rotate(int rotate);
    void Negatif() ; 
    void Desaturate() ; 
    void Threshold(int seuil);
    void MirrorImageArtisanal(bool horizontal) ;
    void RotationImage() ; 
    void Posterize() ;
    void ComptageCouleurs();
    void ComptagePixel() ; 
    void Histogramme() ; 
    void EnhenceContrast() ; 
private:
    MyImage *m_image ;		// used to load and process the image
    wxBitmap m_bitmap ;	// used to display the image
    int m_width ;
    int m_height ;
    MyHistogram * m_histo ; 
};

class MyFrame: public wxFrame

{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnResize(wxCommandEvent& event) ;
    void OnOpenImage(wxCommandEvent& event) ; 
    void OnSaveImage(wxCommandEvent& event) ; 
    void OnPocessImage(wxCommandEvent& event);
    MyPanel *m_panel; // the panel inside the main frame
    
    const int SEUIL = 100; 
};

enum	// énumération. Elle gère la numérotation automatiquement 
{
	ID_Hello = 1,
    ID_About,
    ID_En_Cour,
    ID_LargUP,
    ID_LargDown,
    ID_Open,
    ID_Save,
    ID_MirrorHorizon,
    ID_MirrorVertical,
    ID_Blur,
    ID_Rotation90,
    ID_Rotation180,
    ID_Rotation270,
    ID_Negatif,
    ID_Desaturate,
    ID_Threshold,
    ID_MirrorHorizonArtisanal,
    ID_MirrorVerticalArtisanal,
    ID_RotationArtisanal,
    ID_Posterize,
    ID_Comptage_Couleurs,
    ID_Histogramme,
    ID_EnhenceContrast,

};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame( wxT("Hello World"), wxPoint(50, 50), wxSize(450, 340) );
    frame->Center(); 
	frame->Show(true);
    wxInitAllImageHandlers() ; 
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size){
    
	wxMenu *menuFile = new wxMenu ;
	menuFile->Append(ID_Hello, wxT("Hello...\tCtrl-H") , wxT("Chalut !")) ;
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello) ;

	menuFile->Append(wxID_EXIT) ;
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT) ;
    
    menuFile->Append(ID_About,wxT("About")) ;
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, ID_About) ;
    
    menuFile->AppendSeparator() ;
    
    menuFile->Append(ID_LargUP , wxT("plus large\tCtrl-+")) ;
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_LargUP) ;
    
    menuFile->Append(ID_LargDown , wxT("moins large\tCtrl--")) ;
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_LargDown) ;
    
    menuFile->Append(ID_Open , wxT("open")) ;
	Bind(wxEVT_MENU, &MyFrame::OnOpenImage, this, ID_Open) ;
    
    menuFile->Append(ID_Save , wxT("Save")) ;
	Bind(wxEVT_MENU, &MyFrame::OnSaveImage, this, ID_Save) ;
    
    wxMenu *menuHelp = new wxMenu ;
    menuHelp->Append(ID_En_Cour, wxT("en construction")) ;
    
    wxMenu *menuProcess = new wxMenu ;
    menuProcess->Append(ID_MirrorHorizon, wxT("Mirror Horizontal")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_MirrorHorizon) ;
    
    menuProcess->Append(ID_MirrorVertical, wxT("Mirror Vertical")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_MirrorVertical) ;
    
    menuProcess->AppendSeparator() ;
    
    menuProcess->Append(ID_Blur, wxT("Blur")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_Blur) ;
    
    menuProcess->AppendSeparator() ;
    
    menuProcess->Append(ID_Rotation90, wxT("Rotate 90")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_Rotation90) ;
    
    menuProcess->Append(ID_Rotation180, wxT("Rotate 180")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_Rotation180) ;
    
    menuProcess->Append(ID_Rotation270, wxT("Rotate -90")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_Rotation270) ;
    
    menuProcess->AppendSeparator() ;

    menuProcess->Append(ID_Negatif, wxT("Negatif")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_Negatif) ;
    
    menuProcess->AppendSeparator() ;
    
    menuProcess->Append(ID_Desaturate, wxT("Desaturate")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_Desaturate) ;
    
    menuProcess->AppendSeparator() ;
    
    menuProcess->Append(ID_Threshold, wxT("Threshold")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_Threshold) ;
    
    menuProcess->AppendSeparator() ;
    
    menuProcess->Append(ID_MirrorHorizonArtisanal, wxT("Mirroir Arti horizon")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_MirrorHorizonArtisanal) ;
    
    menuProcess->Append(ID_MirrorVerticalArtisanal, wxT("Mirroir Arti vert")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_MirrorVerticalArtisanal) ;
    
    menuProcess->AppendSeparator() ;
    
    menuProcess->Append(ID_RotationArtisanal, wxT("rotation arti")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_RotationArtisanal) ;
    
    menuProcess->AppendSeparator() ;
    
    menuProcess->Append(ID_Posterize, wxT("Posterize")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_Posterize) ;
    
    menuProcess->AppendSeparator() ;
    
    menuProcess->Append(ID_Comptage_Couleurs, wxT("nbCouleurs")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_Comptage_Couleurs) ;
    
    menuProcess->AppendSeparator() ;
    
    menuProcess->Append(ID_Histogramme, wxT("Histo")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_Histogramme) ;
    
    menuProcess->AppendSeparator() ;
    
    menuProcess->Append(ID_EnhenceContrast, wxT("Enhence Contrast")) ;
	Bind(wxEVT_MENU, &MyFrame::OnPocessImage, this, ID_EnhenceContrast) ;
    

    this->CreateStatusBar(1 , wxTB_DEFAULT_STYLE , wxID_ANY ,wxT("name")) ;
    this->SetStatusText("ho dear, we are in trubles");

	wxMenuBar *menuBar = new wxMenuBar ;
	menuBar->Append( menuFile, wxT("File" )) ;
    menuBar->Append( menuHelp, wxT("Help" )) ;
    menuBar->Append( menuProcess , wxT("Process")) ; 
	SetMenuBar(menuBar) ;
    
    m_panel = new MyPanel(this);
    
}

MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent){
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this) ;
    m_image = nullptr ; 
}


MyPanel::~MyPanel(){
}


void MyPanel::OpenImage(wxString fileName){
    delete m_image ;  
    m_image = new MyImage(fileName);
    m_height = m_image->GetHeight() ; 
    m_width = m_image->GetWidth() ; 
    this->SetSize(m_width , m_height) ; 
    this->GetParent()->SetSize(m_width , m_height) ; 
}


void MyFrame::OnOpenImage(wxCommandEvent& event) {
    wxString fileName = wxFileSelector("onegaï, open a file Onii-chan~") ; 
    if (!fileName.empty()){
        m_panel->OpenImage(fileName);
        this->Refresh(true) ;
    }
}


void MyPanel::OnPaint(wxPaintEvent &WXUNUSED(event)){
    if (m_image != nullptr ){
        m_bitmap = wxBitmap(*m_image) ;
        wxPaintDC dc(this);
        dc.DrawBitmap(m_bitmap,wxPoint(0,0));        
    } 
}



void MyFrame::OnHello(wxCommandEvent& event){
	wxLogMessage(wxT("Hello world from wxWidgets!"));
}


void MyFrame::OnExit(wxCommandEvent& event){
	Close(true);
}


void MyFrame::OnAbout(wxCommandEvent& event){
	wxLogMessage(wxT("Auteur: Pascal Bertolino - 2014-2019"));
}


void MyFrame::OnResize(wxCommandEvent& event){
    wxSize size= this->GetSize() ;
	if (event.GetId() == ID_LargUP){
        if(size.GetWidth() + 100 < 1500){
            size.SetWidth(size.GetWidth()+100) ; 
            this->SetSize(size) ; 
        }
    }else if (event.GetId() == ID_LargDown){
        if(size.GetWidth() - 100 > 200){
            size.SetWidth(size.GetWidth()-100) ; 
            this->SetSize(size) ; 
        }
    }
}


void MyFrame::OnSaveImage(wxCommandEvent& event) {
    wxString save = wxSaveFileSelector(wxT("Image") , wxT("png")) ;
    this->m_panel->saveImage(save) ; 
}

void MyPanel::saveImage(wxString save){
    this->m_image->SaveFile(save) ; 
}



void MyFrame::OnPocessImage(wxCommandEvent& event){
    switch(event.GetId()){
        case ID_MirrorHorizon:
            this->m_panel->MirrorImage(true) ;
            break;
        case ID_MirrorVertical:
            this->m_panel->MirrorImage(true) ;
            break;
        case ID_Blur:
            this->m_panel->BlurImage() ; 
            break;
        case ID_Rotation90:
            this->m_panel->Rotate(90);
            break;
        case ID_Rotation180:
            this->m_panel->Rotate(180);
            break;
        case ID_Rotation270:
            this->m_panel->Rotate(270);
            break;
        case ID_Negatif:
            {
                clock_t begin = clock() ; 
                this->m_panel->Negatif() ; 
                clock_t end = clock() ;
                unsigned long timer = (end - begin) ; 
                wxString str;
                str.Printf(wxT("time :  %ld") , timer); 
                wxLogMessage(str);   
            }
            break;
        case ID_Desaturate:
            this->m_panel->Desaturate() ;
            break;
        case ID_Threshold:
            this->m_panel->Threshold(this->SEUIL) ; 
            break;
        case ID_MirrorHorizonArtisanal:
            this->m_panel->MirrorImageArtisanal(true) ; 
            break;
        case ID_MirrorVerticalArtisanal:
            this->m_panel->MirrorImageArtisanal(false) ; 
            break;
        case ID_RotationArtisanal:
            this->m_panel->RotationImage() ; 
            break ; 
        case ID_Posterize:
            this->m_panel->Posterize() ;
            break;
        case ID_Comptage_Couleurs:
            this->m_panel->ComptageCouleurs();
            break;
        case ID_Histogramme :
            this->m_panel->Histogramme() ; 
            break;
        case ID_EnhenceContrast:
            this->m_panel->EnhenceContrast() ;
            break ; 
    }
    this->Refresh(true) ;
    
}

 
 
void MyPanel::MirrorImage(bool dir){
    if (this->m_image != nullptr){
        * this->m_image = this->m_image->Mirror(dir) ;
    }
}
    

void MyPanel::BlurImage(){
    if (this->m_image != nullptr){
        * this->m_image = this->m_image->Blur(2) ;
    }
}


void MyPanel::Rotate(int rotate){
    if (this->m_image != nullptr){
        /*if(rotate == 90){
            this->m_image = this->m_image->Rotate90() ;
        }else if (rotate==180){
            * this->m_image = this->m_image->Rotate180() ;
        }else if (rotate==270){
            * this->m_image = this->m_image->Rotate180() ;
            this->m_image = this->m_image->Rotate90() ;
        }*/
        m_height = m_image->GetHeight() ; 
        m_width = m_image->GetWidth() ; 
        this->SetSize(m_width , m_height) ; 
        this->GetParent()->SetSize(m_width , m_height) ;
    }
}

void MyPanel::Negatif(){
    if (this->m_image != nullptr){
        this->m_image->Negative() ; 
    }
}

void MyPanel::Desaturate() {
    if (this->m_image != nullptr){
        this->m_image->Desaturate() ; 
    }
}

void MyPanel::Threshold(int seuil) {
    /*if (this->m_image != nullptr){
        MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
        dlg->ShowModal() ;
        this->m_image->Threshold(dlg->m_threshold->GetValue()) ; 
    }*/
    MyImage * save = this->m_image ; 
    MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
    if (dlg->ShowModal() ==  wxID_OK){
         this->m_image->Threshold(dlg->m_threshold->GetValue()) ; 
    }else if (dlg->ShowModal() == wxID_CANCEL){
        this->m_image = save ; 
    }
}

void MyPanel::MirrorImageArtisanal(bool horizontal) {
    if (this->m_image != nullptr){
        this->m_image->MirrorArti(horizontal) ; 
    }
}

void MyPanel::RotationImage() {
    if (this->m_image != nullptr){
        
        MyRotateDialog *dlg = new MyRotateDialog(this, -1, wxDefaultPosition, wxSize(250,140)) ;
        if (dlg->ShowModal() == wxID_OK){
            wxImage * temp ; 
            for (int i = 0 ; i <= dlg->RadioBox1->GetSelection() ; i++){
                temp = this->m_image->Rotate90() ;
                this->m_image->SetData(temp->GetData() , temp->GetWidth() , temp->GetHeight()) ; 
            }
            m_height = m_image->GetHeight() ; 
            m_width = m_image->GetWidth() ; 
            this->SetSize(m_width , m_height) ; 
            this->GetParent()->SetSize(m_width , m_height) ;
        }
    }

}

void MyPanel::Posterize(){
    if (this->m_image != nullptr){
        this->m_image->Posterize() ; 
    }
}

void MyPanel::ComptageCouleurs(){
    int nbCouleurs = m_image->ComptageCouleurs() ;
    wxLogMessage(wxT("nb de Couleurs : "+ std::to_string(nbCouleurs) ));
}

void MyPanel::Histogramme(){
    if (this->m_histo){
        delete this->m_histo ;
    }
    this->m_histo = new MyHistogram(m_image) ; 
}

void MyPanel::EnhenceContrast() {
    int min ;
    int max ; 
    this->Histogramme() ;
    this->m_histo->GetDynamic(& min , & max) ; 
    this->m_image->EnhenceContrast(min , max) ; 
    
}