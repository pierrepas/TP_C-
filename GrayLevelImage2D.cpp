#include "GrayLevelImage2D.hpp"

//using namespace GrayLevelImage2D;A


GrayLevelImage2D::Iterator::Iterator
(GrayLevelImage2D& Image,int x,int y):
    std::vector<GrayLevel>::iterator
    (Image.m_data.begin() + Image.index(x,y))
{}

GrayLevelImage2D::Iterator GrayLevelImage2D::start(int x, int y){
    return Iterator(*this,x,y);
}

GrayLevelImage2D::Iterator GrayLevelImage2D::begin(){
    return start(0,0);
}

GrayLevelImage2D::Iterator GrayLevelImage2D::end(){
    return start(0,h());
}

GrayLevelImage2D::GrayLevelImage2D(){
    m_width = 0;
    m_height = 0;
}

GrayLevelImage2D::GrayLevelImage2D(int w, int h, GrayLevel g){
    m_width = w;
    m_height = h;
    m_data.resize(w*h);
    fill(g);
}

int GrayLevelImage2D::w() const{
    return m_width;
}

int GrayLevelImage2D::h() const{
    return m_height;
}

int GrayLevelImage2D::index(int x, int y) const{
    return x + w() * y;
}

void GrayLevelImage2D::fill(GrayLevel g){
    for(int i = 0; i < w(); i++){
        for(int j = 0; j< h(); j++){
            at( i, j) = g;
        }
    }
}

GrayLevelImage2D::GrayLevel GrayLevelImage2D::at(int i, int j) const{
    return m_data[index(i,j)];
}

GrayLevelImage2D::GrayLevel & GrayLevelImage2D::at(int i, int j) {
    return m_data[index(i,j)];
}

// Convertir l'image en PGM, en mettant à jour width et height
bool GrayLevelImage2D::importPGM( std::istream & input ){
    std::string s;
    std::string commentary;
    std::getline(input, s);
    std::getline(input, commentary);
    int cmax;
    input >> m_width >> m_height >> cmax;
    *this = GrayLevelImage2D(m_width, m_height);
    if(s[1] == '5'){
        char lect;
        input >> std::noskipws;
        for (int i=0; i < m_width; i++){
            for (int j=0; j < m_width; j++){
                input >> lect;
                at(i,j) = lect;
            }
        }
    }else{
        int lect;
        for (int i=0; i < m_width; i++){
            for (int j=0; j < m_width; j++){
                input >> lect;
                at(i,j) = lect;
            }
        }
    }

    /*
       for ( Iterator it = begin(), itE = end(); it != itE; ++it  ){
       input >> *it;
       }
       */
    return true;
}

bool GrayLevelImage2D::exportPGM( std::ostream & output, bool ascii ){
    if(ascii){
        output << "P2";
    }else {
        output << "P5";
    }
    output << std::endl << h() << " " << w() << std::endl;
    output << 255 << std::endl;
/*
    for (Iterator it = begin(), itE = end(); it != itE; ++it ){
        if(ascii){
            output << (int) *it;
        }else{
            output << (char) *it;
        }
        output << *it;
    }
*/

    for(int i=0; i<w();i ++){
        for(int j=0; j<h();j ++){
            if(ascii){
                output << (int) at(i,j );
            }else{
                output << (char ) at(i,j);
            }
        }
    }
    return true;
}

