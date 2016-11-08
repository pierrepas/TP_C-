// double-brightness.cpp
#include <iostream>
#include <fstream>
#include "GrayLevelImage2D.hpp"

using namespace std;

int main( int argc, char** argv )
{
    typedef GrayLevelImage2D::GrayLevel GrayLevel;
    typedef GrayLevelImage2D::Iterator Iterator;
    if ( argc < 3 )
    {
        std::cerr << "Usage: filtrage-median <input.pgm> <output.pgm> <nombre>" << std::endl;
        return 0;
    }
    GrayLevelImage2D imgIn, img;
    int tailleFiltrage = 3;
    ifstream input( argv[1] ); // récupère le 1er argument.
    bool ok = imgIn.importPGM( input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();
    for(int i=0; i<imgIn.w(); i++){
        for(int j=0; j<imgIn.h(); j++){
            vector<int> tabAdjacence;
            for(int k = i - tailleFiltrage; k < i + tailleFiltrage; k++){
                for(int l = j - tailleFiltrage; l < j + tailleFiltrage; l++){
                    if(i > 0 && i < imgIn.w() && j > 0 && j < imgIn.h())
                        tabAdjacence.push_back(imgIn.at(k,l));
                }
            }
            sort(tabAdjacence.front(), tabAdjacence.back());
            int med = tabAdjacence[tabAdjacence.size() / 2];
            img.at(i,j) = med;
        }
    }
    /*
       for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
       {
       }
    */
    ofstream output( argv[2] ); // récupère le 2ème argument.
    ok = img.exportPGM( output, false );
    if ( !ok )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}
