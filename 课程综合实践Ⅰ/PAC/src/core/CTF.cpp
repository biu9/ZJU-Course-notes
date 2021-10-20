#include "CTF.h"
#include "math.h"

const double h=6.62606957e-34;
const double c=299792458;
const double q0=1.602e-19;
const double m0=9.109383e-31;

CTF::CTF()
{

}

CTF::CTF(int n_now)
{
    n=n_now;
}

CTF::~CTF()
{

}

void CTF::setAllCTFPara(float defocus1_now,float defocus2_now,float astig_now,float phase_shift_now,float w_now)
{
    defocus1=defocus1_now*1e-10;    // input in A, store in m
    defocus2=defocus2_now*1e-10;    // input in A, store in m
    astig=astig_now/180.0*M_PI;    // input in degree, store in radius
    phase_shift=phase_shift_now;    // in radius
    w_cos=w_now;
    w_sin=sqrt(1-w_now*w_now);
}

void CTF::setAllImagePara(float pix_now,float volt_now,float Cs_now)
{
    pix=pix_now*1e-10;  // input in A, store in m
    volt=volt_now*1e3;  // input in kV, store in V
    Cs=Cs_now*1e-3; // input in mm, store in m
//    lambda=12.26/sqrt(volt+0.9785*volt*volt/1e6)*1e-10; // in m
    lambda=h/sqrt(2*m0*q0*volt*(1+(q0*volt)/(2*m0*c*c)));   // in m
}

void CTF::setN(int n_now)
{
    n=n_now;
}

float CTF::getDefocus1()
{
    return defocus1;
}

float CTF::getDefocus2()
{
    return defocus2;
}

float CTF::getAstigmatism()
{
    return astig;
}

float CTF::getPhaseShift()
{
    return phase_shift;
}

float CTF::getW()
{
    return w_cos;
}

float CTF::getPixelSize()
{
    return pix;
}

float CTF::getVoltage()
{
    return volt;
}

float CTF::getCs()
{
    return Cs;
}

float CTF::getLambda()
{
    return lambda;
}

int CTF::getN()
{
    return n;
}

float CTF::computeCTF2D(float x,float y,int Nx,int Ny,bool phaseflip,bool flip_contrast,float z_offset) // z_offset in pixels, x和y给的都是格点坐标值，非真实值
{
    float x_norm=(x>=int(ceil(float(Nx+1)/2)))?(x-Nx):(x),y_norm=(y>=int(ceil(float(Ny+1)/2)))?(y-Ny):(y);
    float x_real=float(x_norm)/float(Nx)*(1/pix),y_real=float(y_norm)/float(Ny)*(1/pix);
    float alpha;
    if(x_norm==0)
    {
        if(y_norm>0)
        {
            alpha=M_PI_2;
        }
        else if(y_norm<0)
        {
            alpha=-M_PI_2;
        }
        else
        {
            alpha=0.0;
        }
    }
    else
    {
        alpha=atan(y_real/x_real);
    }
    float freq2=x_real*x_real+y_real*y_real;
    float df_now=((defocus1+defocus2-2*z_offset*pix)+(defocus1-defocus2)*cos(2*(alpha-astig)))/2.0;
    float chi=M_PI*lambda*df_now*freq2-M_PI_2*Cs*lambda*lambda*lambda*freq2*freq2+phase_shift;   
    float ctf_now=w_sin*sin(chi)+w_cos*cos(chi);
    if(flip_contrast)
    {
        ctf_now=-ctf_now;
    }
    if(phaseflip)
    {
        if(ctf_now>=0)
        {
            return 1.0;
        }
        else
        {
            return -1.0;
        }
    }
    else
    {
        return ctf_now;
    }
}