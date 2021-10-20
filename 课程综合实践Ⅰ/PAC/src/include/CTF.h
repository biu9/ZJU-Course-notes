/*******************************************************************
 *       Filename:  CTFBase.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/07/2020 05:29:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruan Huabin
 *          Email:  ruanhuabin@tsinghua.edu.cn
 *        Company:  Dep. of CS, Tsinghua Unversity
 *
 *******************************************************************/


#ifndef  CTFBASE_H
#define  CTFBASE_H
#include <map>
#include <string>
using namespace std;
class CTFBase
{
    public:
        virtual void doCTF(map<string, string> &inputPara, map<string, string> &outputPara) = 0; 
        virtual ~CTFBase();

};


#endif
[PAC20219131@manager include]$ ls
AlignmentBase.h  CTFBase.h  CTF_old.h     mrc.h      ReconstructionAlgo_WBP_RAM.h  track.h
CTFAlgo.h        CTF.h      fftw3_prep.h  mrc_old.h  ReconstructionBase.h          util.h        
[PAC20219131@manager include]$ cat CTF.h
class CTF
{
public:
    CTF();
    CTF(int n_now);
    ~CTF();

public:
    void setAllCTFPara(float defocus1_now,float defocus2_now,float astig_now,float phase_shift_now,float w_now);
    void setAllImagePara(float pix_now,float volt_now,float Cs_now);
    void setN(int n_now);

    float getDefocus1();
    float getDefocus2();
    float getAstigmatism();
    float getPhaseShift();
    float getW();
    float getPixelSize();
    float getVoltage();
    float getCs();
    float getLambda();
    int getN();

    float computeCTF2D(float x,float y,int Nx,int Ny,bool phaseflip,bool flip_contrast,float z_offset);

private:
    float defocus1,defocus2;    // in m
    float astig;    // in radius
    float phase_shift;  // in radius
    float w_cos,w_sin;

    float pix;  // in m
    float volt; // in V
    float Cs;   // in m
    float lambda;   // in m

    int n;

};