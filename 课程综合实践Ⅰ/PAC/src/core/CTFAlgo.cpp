/*******************************************************************
 *       Filename:  CTFAlgo.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/07/2020 05:37:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruan Huabin
 *          Email:  ruanhuabin@tsinghua.edu.cn
 *        Company:  Dep. of CS, Tsinghua Unversity
 *
 *******************************************************************/
#include "CTFAlgo.h"
#include "mrc.h"
#include "math.h"
#include "CTF.h"
#include "fftw3.h"
#include "util.h"

static void buf2fft(float *buf, float *fft, int nx, int ny)
{
    int nxb=nx+2-nx%2;
    int i;
    for(i=0;i<(nx+2-nx%2)*ny;i++)
    {
        fft[i]=0.0;
    }
    for(i=0;i<ny;i++)
    {
        memcpy(fft+i*nxb,buf+i*nx,sizeof(float)*nx);
    }
}

static void fft2buf(float *buf, float *fft, int nx, int ny)
{
    int nxb=nx+2-nx%2;
    int i;
    for(i=0;i<nx*ny;i++)
    {
        buf[i]=0.0;
    }
    for(i=0;i<ny;i++)
    {
        memcpy(buf+i*nx,fft+i*nxb,sizeof(float)*nx);
    }
}

static void buf2fft_padding(float *buf, float *fft, int nx, int ny,int nx_pad,int ny_pad)     
{
    int nxb=nx_pad+2-nx_pad%2;
    int i;
    for(i=0;i<(nx_pad+2-nx_pad%2)*ny_pad;i++)
    {
        fft[i]=0.0;
    }
    for(i=0;i<ny;i++)
    {
        memcpy(fft+i*nxb,buf+i*nx,sizeof(float)*nx);
    }
}

static void calc_psd_2D(float *image,float *psd,int Nx,int Ny)
{
    fftwf_plan plan_fft;
    float *bufc=new float[(Nx+2-Nx%2)*Ny];
    plan_fft=fftwf_plan_dft_r2c_2d(Ny,Nx,(float*)bufc,reinterpret_cast<fftwf_complex*>(bufc),FFTW_ESTIMATE);
    buf2fft(image,bufc,Nx,Ny);
    fftwf_execute(plan_fft);

    int fft_x[Nx],fft_y[Ny];
    int fft_x_offset=int(ceil(float(Nx+1)/2))-1,fft_y_offset=int(ceil(float(Ny+1)/2))-1;      
    for(int i=0;i<Nx;i++)
    {
        fft_x[i]=i;
        if(i>fft_x_offset)
        {
            fft_x[i]-=(Nx);
        }
    }
    for(int j=0;j<Ny;j++)
    {
        fft_y[j]=j;
        if(j>fft_y_offset)
        {
            fft_y[j]-=Ny;
        }
    }

    // fftshift
    for(int i=0;i<Nx+2-Nx%2;i+=2)
    {
        for(int j=0;j<Ny;j++)
        {
            int i_psd=fft_x[i/2]+fft_x_offset,j_psd=fft_y[j]+fft_y_offset;
/*            if(abs(fft_x[i/2])>=0 && abs(fft_x[i/2])<=1 && abs(fft_y[j])>=0 && abs(fft_x[j])<=1)    // 直流附近可能太大了，干扰判断
            {
                psd[i_psd+j_psd*(Nx+2-Nx%2)]=0.0;
            }
            else*/
            {
                if(i_psd>=0 && i_psd<Nx && j_psd>=0 && j_psd<Ny)
                {
                    psd[i_psd+j_psd*(Nx)]=bufc[i+j*(Nx+2-Nx%2)]*bufc[i+j*(Nx+2-Nx%2)]+bufc[i+1+j*(Nx+2-Nx%2)]*bufc[i+1+j*(Nx+2-Nx%2)];
                    psd[(Nx-i_psd-1)+(Ny-j_psd-1)*(Nx)]=bufc[i+j*(Nx+2-Nx%2)]*bufc[i+j*(Nx+2-Nx%2)]+bufc[i+1+j*(Nx+2-Nx%2)]*bufc[i+1+j*(Nx+2-Nx%2)];  // 中心对称
                }
            }
        }
    }

    fftwf_destroy_plan(plan_fft);
    delete [] bufc;
}

static void calc_psd_2D_padding(float *image,float *psd,int Nx,int Ny)
{
    fftwf_plan plan_fft;
    int Nx_pad=Nx*2,Ny_pad=Ny*2;
    float *bufc=new float[(Nx_pad+2)*Ny_pad];
    plan_fft=fftwf_plan_dft_r2c_2d(Ny_pad,Nx_pad,(float*)bufc,reinterpret_cast<fftwf_complex*>(bufc),FFTW_ESTIMATE);
    buf2fft_padding(image,bufc,Nx,Ny,Nx_pad,Ny_pad);
    fftwf_execute(plan_fft);

    int fft_x[Nx_pad],fft_y[Ny_pad];
    int fft_x_offset=int(ceil(float(Nx_pad+1)/2))-1,fft_y_offset=int(ceil(float(Ny_pad+1)/2))-1;
    for(int i=0;i<Nx_pad;i++)
    {
        fft_x[i]=i;
        if(i>fft_x_offset)
        {
            fft_x[i]-=(Nx_pad);
        }
    }
    for(int j=0;j<Ny_pad;j++)
    {
        fft_y[j]=j;
        if(j>fft_y_offset)
        {
            fft_y[j]-=Ny_pad;
        }
    }

    // fftshift
    float *psd_padding=new float[(Nx_pad)*Ny_pad];
    for(int i=0;i<Nx_pad+2;i+=2)
    {
        for(int j=0;j<Ny_pad;j++)
        {
            int i_psd=fft_x[i/2]+fft_x_offset,j_psd=fft_y[j]+fft_y_offset;
            if(abs(fft_x[i/2])>=0 && abs(fft_x[i/2])<=1 && abs(fft_y[j])>=0 && abs(fft_x[j])<=1)    // 直流附近可能太大了，干扰判断
            {
                psd_padding[i_psd+j_psd*(Nx_pad)]=0.0;
            }
            else
            {
                if(i_psd>=0 && i_psd<Nx_pad && j_psd>=0 && j_psd<Ny_pad)
                {
                    psd_padding[i_psd+j_psd*(Nx_pad)]=bufc[i+j*(Nx_pad+2)]*bufc[i+j*(Nx_pad+2)]+bufc[i+1+j*(Nx_pad+2)]*bufc[i+1+j*(Nx_pad+2)];
                    psd_padding[(Nx_pad-i_psd)+(Ny_pad-j_psd)*(Nx_pad)]=bufc[i+j*(Nx_pad+2)]*bufc[i+j*(Nx_pad+2)]+bufc[i+1+j*(Nx_pad+2)]*bufc[i+1+j*(Nx_pad+2)];  // 中心对称
                }
            }
        }
    }

    MRC psd_padding_mrc("test.mrc","wb");
    psd_padding_mrc.createMRC_empty(Nx_pad,Ny_pad,1,2);
    psd_padding_mrc.write2DIm(psd_padding,0);
    psd_padding_mrc.close();

    // lowpass filter of the psd (crop in FD to perform downsampling)
    fftwf_plan plan_fft_2;
    float *bufc_2=new float[(Nx_pad+2)*Ny_pad];
    plan_fft_2=fftwf_plan_dft_r2c_2d(Ny_pad,Nx_pad,(float*)bufc_2,reinterpret_cast<fftwf_complex*>(bufc_2),FFTW_ESTIMATE);
    buf2fft(psd_padding,bufc_2,Nx_pad,Ny_pad);
    fftwf_execute(plan_fft_2);
    float *bufc_3=new float[(Nx+2)*Ny];
    for(int i=0;i<(Nx+2);i+=2)
    {
        int jj=0;
        for(int j=0;j<int(ceil(float(Ny+1)/2));j++)
        {
            bufc_3[i+jj*(Nx+2)]=bufc_2[i+j*(Nx_pad+2)];
            bufc_3[i+1+jj*(Nx+2)]=bufc_2[i+1+j*(Nx_pad+2)];
            jj++;
        }
        for(int j=Ny_pad-int(ceil(float(Ny+1)/2))+2;j<Ny_pad;j++)
        {
            bufc_3[i+jj*(Nx+2)]=bufc_2[i+j*(Nx_pad+2)];
            bufc_3[i+1+jj*(Nx+2)]=bufc_2[i+1+j*(Nx_pad+2)];
            jj++;
        }
    }
    fftwf_plan plan_fft_3;
    plan_fft_3=fftwf_plan_dft_c2r_2d(Ny,Nx,reinterpret_cast<fftwf_complex*>(bufc_3),(float*)bufc_3,FFTW_ESTIMATE);
    fftwf_execute(plan_fft_3);
    fft2buf(psd,bufc_3,Nx,Ny);

    fftwf_destroy_plan(plan_fft);
    fftwf_destroy_plan(plan_fft_2);
    fftwf_destroy_plan(plan_fft_3);
    delete [] bufc;
    delete [] bufc_2;
    delete [] bufc_3;
    delete [] psd_padding;
}

static void normalize_psd(float *psd,int Nx,int Ny)
{
    float power_max=0.0;
    for(int i=0;i<Nx;i++)
    {
        for(int j=0;j<Ny;j++)
        {
            if(power_max<psd[i+j*Nx])
            {
                power_max=psd[i+j*Nx];
            }
        }
    }
    for(int i=0;i<Nx;i++)
    {
        for(int j=0;j<Ny;j++)
        {
            psd[i+j*Nx]/=power_max;
        }
    }
}

static void spectrum_box_convolution(float *psd,float res_min,float pix,int Nx,int Ny)        
{
        float *psd_orig=new float[Nx*Ny];
    memcpy(psd_orig,psd,sizeof(float)*Nx*Ny);
    int box_size=int(Nx*pix/res_min/sqrt(2));
//    int box_size=1;
    if(box_size%2==0)   // 默认box_size为奇数
    {
        box_size++;
    }
    int box_size_half=(box_size-1)/2;
    int fft_x_offset=int(ceil(float(Nx+1)/2))-1,fft_y_offset=int(ceil(float(Ny+1)/2))-1;      
    float fft_x[Nx],fft_y[Ny];
    for(int i=0;i<Nx;i++)
    {
        fft_x[i]=(i-fft_x_offset)/(Nx*pix);
    }
    for(int j=0;j<Ny;j++)
    {
        fft_y[j]=(j-fft_y_offset)/(Ny*pix);
    }
    for(int i=0;i<Nx;i++)
    {
        for(int j=0;j<Ny;j++)
        {
        /*    if((fft_x[i]*fft_x[i])+(fft_y[j]*fft_y[j])<1/(res_min*res_min))    // 比res_min 
还小的区域不考虑
            {
                psd[i+j*Nx]=0.0;
                continue;
            }*/
            int box_pix_num=0;
            float box_sum=0.0;
            for(int ii=-box_size_half;ii<=box_size_half;ii++)
            {
                for(int jj=-box_size_half;jj<=box_size_half;jj++)
                {
                    if(!((i+ii+Nx)%Nx>=fft_x_offset-1 && (i+ii+Nx)%Nx<=fft_x_offset+1 && (j+jj+Ny)%Ny>=fft_y_offset-1 && (j+jj+Ny)%Ny<=fft_y_offset+1)) // 直流附近可能太大了，干扰判断     
                    {
                        box_pix_num++;
                        box_sum+=psd_orig[((i+ii+Nx)%Nx)+((j+jj+Ny)%Ny)*Nx];  // psd是周期函数
                    }
                }
            }
            if(box_pix_num==0)
            {
                psd[i+j*Nx]=0.0;
            }
            else
            {
                psd[i+j*Nx]=box_sum/float(box_pix_num);
//                psd[i+j*Nx]=psd_orig[i+j*Nx];
            }
        }
    }
    delete [] psd_orig;
}



CTFAlgo::~CTFAlgo()
{
}

void CTFAlgo::doCTF(map<string, string> &inputPara, map<string, string> &outputPara)
{
    cout<<"Run doCTF() in CTFAlgo"<<endl;

    // Input
    map<string,string>::iterator it=inputPara.find("input_mrc");
    string input_mrc;
    if(it!=inputPara.end())
    {
        input_mrc=it->second;
        cout << "Input file name: " << input_mrc << endl;
    }
    else
    {
        cerr << "No input file name!" << endl;
        abort();
    }
    MRC stack_orig(input_mrc.c_str(),"rb");
    if(!stack_orig.hasFile())
    {
        cerr << "Cannot open input mrc stack!" << endl;
        abort();
    }

    it=inputPara.find("defocus_file");
    string defocus_file;
    if(it!=inputPara.end())
    {
        defocus_file=it->second;
        cout << "Defocus file name: " << defocus_file << endl;
    }
    else
    {
        cout << "No defocus file name, set default: defocus_file.txt" << endl;
        defocus_file="defocus_file.txt";
    }

    it=inputPara.find("prfx");
    string prfx;
    if(it!=inputPara.end())
    {
        prfx=it->second;
        cout << "Prefix: " << prfx << endl;
    }
    else
    {
        cout << "No prfx, set default: tomo" << endl;
        prfx="tomo";
    }

/*    it=inputPara.find("input_tlt");
    string input_tlt;
    if(it!=inputPara.end())
    {
        input_tlt=it->second;
        cout << "Input tlt file name: " << input_tlt << endl;
    }
    else
    {
        cerr << "No input tlt file name!" << endl;
        abort();
    }
    FILE *ftlt=fopen(input_tlt.c_str(),"r");
    if(ftlt==NULL)
    {
        cerr << "Cannot open tlt file!" << endl;
        abort();
    }
    float theta[stack_orig.getNz()];
    float theta_max=0.0;
    for(int n=0;n<stack_orig.getNz();n++)
    {
        fscanf(ftlt,"%f",&theta[n]);
        if(fabs(theta[n])>theta_max)
        {
            theta_max=fabs(theta[n]);
        }
    }
    fflush(ftlt);
    fclose(ftlt);*/

    CTF ctf_para[stack_orig.getNz()];
    float Cs,pix,volt,w_cos;
    it=inputPara.find("Cs");
    if(it!=inputPara.end())
    {
        Cs=atof(it->second.c_str());
        cout << "Cs (mm): " << Cs << endl;
    }
    else
    {
        cerr << "No Cs!" << endl;
        abort();
    }
    it=inputPara.find("pixel_size");
    if(it!=inputPara.end())
    {
        pix=atof(it->second.c_str());
        cout << "Pixel size (A): " << pix << endl;
    }
    else
    {
        cerr << "No pixel size!" << endl;
        abort();
    }
    it=inputPara.find("voltage");
    if(it!=inputPara.end())
    {
        volt=atof(it->second.c_str());
        cout << "Accelerating voltage (kV): " << volt << endl;
    }
    else
    {
        cerr << "No accelerating voltage!" << endl;
        abort();
    }
    it=inputPara.find("w");
    if(it!=inputPara.end())
    {
        w_cos=atof(it->second.c_str());
        cout << "Amplitude contrast: " << w_cos << endl;
    }
    else
    {
        cerr << "No amplitude contrast!" << endl;
        abort();
    }
    for(int n=0;n<stack_orig.getNz();n++)
    {
        ctf_para[n].setAllImagePara(pix,volt,Cs);
        ctf_para[n].setAllCTFPara(0,0,0,0,w_cos);
    }

    FILE *fpsi=fopen("psi.txt","r");
    if(!fpsi)
    {
        cerr << "No psi found!" << endl;
        abort();
    }
    float psi_deg,psi_rad;
    fscanf(fpsi,"%f",&psi_deg);
    psi_rad=psi_deg*M_PI/180;
    fflush(fpsi);
    fclose(fpsi);
    cout << "psi: " << psi_deg << endl;

    cout << endl << "Parameters for searching: " << endl;
    int patch_size;
    float res_max,res_min;
    float df_max,df_min,df_step;
    it=inputPara.find("patch_size");
    if(it!=inputPara.end())
    {
        patch_size=atoi(it->second.c_str());
        if(patch_size%2==1)  // 默认patch_size为偶数
        {
            patch_size++;
        }
        cout << "Patch size: " << patch_size << endl;
    }
    else
    {
        cout << "No patch size found, set default: 512" << endl;
        patch_size=512;
    }
    it=inputPara.find("res_max");
    if(it!=inputPara.end())
    {
        res_max=atof(it->second.c_str());
        cout << "Maximum resolution (A): " << res_max << endl;
    }
    else
    {
        cout << "No maximum resolution found, set default: 50 (A)" << endl;
        res_max=50.0;
    }
    it=inputPara.find("res_min");
    if(it!=inputPara.end())
    {
        res_min=atof(it->second.c_str());
        cout << "Minimum resolution (A): " << res_min << endl;
    }
    else
    {
        cout << "No minimum resolution found, set default: 10 (A)" << endl;
        res_min=10.0;
    }
    it=inputPara.find("df_min");
    if(it!=inputPara.end())
    {
        df_min=atof(it->second.c_str());
        cout << "Minimum defocus (A): " << df_min << endl;
    }
    else
    {
        cout << "No minimum defocus found, set default: 10000 (A)" << endl;
        df_min=10000.0;
    }
    it=inputPara.find("df_max");
    if(it!=inputPara.end())
    {
        df_max=atof(it->second.c_str());
        cout << "Maximum defocus (A): " << df_max << endl;
    }
    else
    {
        cout << "No maximum defocus found, set default: 50000 (A)" << endl;
        df_max=50000.0;
    }
    it=inputPara.find("df_step");
    if(it!=inputPara.end())
    {
        df_step=atof(it->second.c_str());
        cout << "Defocus searching step (A): " << df_step << endl;
    }
    else
    {
        cout << "No defocus searching step found, set default: 100 (A)" << endl;
        df_step=100.0;
    }



    // CTF estimation
/*    cout << endl << "Start CTF estimation: " << endl;
    string psd_mrc=prfx+".psd";
    MRC stack_psd(psd_mrc.c_str(),"wb");
    stack_psd.createMRC_empty(patch_size,patch_size,stack_orig.getNz(),2);
    for(int n=0;n<stack_orig.getNz();n++)
    {
        cout << "Image " << n << ": ";

        // read in current image
        float *image_now=new float[stack_orig.getNx()*stack_orig.getNy()];
        stack_orig.read2DIm_32bit(image_now,n);

        // obtain power spectrum
        float *psd_sum=new float[patch_size*patch_size];
        for(int i=0;i<patch_size*patch_size;i++)
        {
            psd_sum[i]=0.0;
        }

        // 特别注意：先求功率谱再求和！！！（求功率谱有一个平方，因此不能交换顺序，先求和再求 
平方相位项将无法抵消）
        int x_center=int(stack_orig.getNx()/2),y_center=int(stack_orig.getNy()/2);
        int patch_x_center=x_center,patch_y_center=y_center;
        int patch_size_half=patch_size/2;
        int patch_x_step=int(8.0*cos((psi_deg+90)*M_PI/180.0)),patch_y_step=int(8.0*sin((psi_deg+90)*M_PI/180.0));
        int patch_num=0;
        while(patch_x_center+patch_size_half-1<stack_orig.getNx() && patch_x_center-patch_size_half+1+1>=0 && patch_y_center+patch_size_half<stack_orig.getNy() && patch_y_center-patch_size_half+1>=0) // 从中间正向搜 // 取x方向510，y方向512的块，经padding后变成512*512
        {
            // get current patch
            float *patch_now=new float[(patch_size-2)*patch_size];
            for(int i=-patch_size_half+1+1;i<=patch_size_half-1;i++)
            {
                for(int j=-patch_size_half+1;j<=patch_size_half;j++)
                {
                    patch_now[(i+patch_size_half-1-1)+(j+patch_size_half-1)*(patch_size-2)]=image_now[(patch_x_center+i)+(patch_y_center+j)*stack_orig.getNx()];
                }
            }

            // calculate current psd
            float *psd_now=new float[patch_size*patch_size];
            calc_psd_2D(patch_now,psd_now,patch_size-2,patch_size);

            // add up all psd
            for(int i=0;i<patch_size*patch_size;i++)
            {
                psd_sum[i]+=psd_now[i];
            }

            patch_x_center+=patch_x_step;
            patch_y_center+=patch_y_step;
            patch_num++;

            delete [] patch_now;
            delete [] psd_now;
        }
        patch_x_center=x_center-patch_x_step;
        patch_y_center=y_center-patch_y_step;
        while(patch_x_center+patch_size_half-1<stack_orig.getNx() && patch_x_center-patch_size_half+1+1>=0 && patch_y_center+patch_size_half<stack_orig.getNy() && patch_y_center-patch_size_half+1>=0) // 反向搜
        {
            // get current patch
            float *patch_now=new float[(patch_size-2)*patch_size];
            for(int i=-patch_size_half+1+1;i<=patch_size_half-1;i++)
            {
                for(int j=-patch_size_half+1;j<=patch_size_half;j++)
                {
                    patch_now[(i+patch_size_half-1-1)+(j+patch_size_half-1)*(patch_size-2)]=image_now[(patch_x_center+i)+(patch_y_center+j)*stack_orig.getNx()];
                }
            }

            // calculate current psd
            float *psd_now=new float[patch_size*patch_size];
            calc_psd_2D(patch_now,psd_now,patch_size-2,patch_size);

            // add up all psd
            for(int i=0;i<patch_size*patch_size;i++)
            {
                psd_sum[i]+=psd_now[i];
            }

            patch_x_center-=patch_x_step;
            patch_y_center-=patch_y_step;
            patch_num++;

            delete [] patch_now;
            delete [] psd_now;
        }
        for(int i=0;i<patch_size*patch_size;i++)    // averaging
        {
            psd_sum[i]/=patch_num;
        }

//        spectrum_box_convolution(psd_sum,res_min,pix,patch_size,patch_size);
        stack_psd.write2DIm(psd_sum,n);

        cout << "Done" << endl;

        delete [] image_now;
        delete [] psd_sum;
    }
    stack_psd.close();

    cout << endl << "Finish CTF estimation successfully!" << endl << endl;*/

    cout << endl << "Start CTF estimation: " << endl;
    string psd_mrc=prfx+".psd";
    MRC stack_psd(psd_mrc.c_str(),"wb");
    stack_psd.createMRC_empty(patch_size,patch_size,stack_orig.getNz(),2);
    for(int n=0;n<stack_orig.getNz();n++)
    {
        cout << "Image " << n << ": ";
        // read in current image
        float *image_now=new float[stack_orig.getNx()*stack_orig.getNy()];
        stack_orig.read2DIm_32bit(image_now,n);

        // obtain power spectrum
        float *psd_sum=new float[patch_size*patch_size];
        for(int i=0;i<patch_size*patch_size;i++)
        {
            psd_sum[i]=0.0;
        }

        // 特别注意：先求功率谱再求和！！！（求功率谱有一个平方，因此不能交换顺序，先求和再求 
平方相位项将无法抵消）
        int x_center=int(stack_orig.getNx()/2),y_center=int(stack_orig.getNy()/2);
        int patch_x_center=x_center,patch_y_center=y_center;
        int patch_size_half=patch_size/2;
        int patch_x_step=int(float(patch_size_half)/2.0*cos((psi_deg+90)*M_PI/180.0)),patch_y_step=int(float(patch_size_half)/2.0*sin((psi_deg+90)*M_PI/180.0));
        int patch_num=0;
        while(patch_x_center+patch_size_half<stack_orig.getNx() && patch_x_center-patch_size_half+1>=0 && patch_y_center+patch_size_half<stack_orig.getNy() && patch_y_center-patch_size_half+1>=0) // 从中间正向搜
        {
            // get current patch
            float *patch_now=new float[patch_size*patch_size];
//            float patch_now_min=1e10,patch_now_max=-1e10;
            for(int i=-patch_size_half+1;i<=patch_size_half;i++)
            {
                for(int j=-patch_size_half+1;j<=patch_size_half;j++)
                {
                    patch_now[(i+patch_size_half-1)+(j+patch_size_half-1)*patch_size]=image_now[(patch_x_center+i)+(patch_y_center+j)*stack_orig.getNx()];
/*                    if(patch_now[(i+patch_size_half-1)+(j+patch_size_half-1)*patch_size]>patch_now_max)
                    {
                        patch_now_max=patch_now[(i+patch_size_half-1)+(j+patch_size_half-1)*patch_size];
                    }
                    if(patch_now[(i+patch_size_half-1)+(j+patch_size_half-1)*patch_size]<patch_now_min)
                    {
                        patch_now_min=patch_now[(i+patch_size_half-1)+(j+patch_size_half-1)*patch_size];
                    }*/
                }
            }
            // normalization
/*            for(int i=-patch_size_half+1;i<=patch_size_half;i++)
            {
                for(int j=-patch_size_half+1;j<=patch_size_half;j++)
                {
                    patch_now[(i+patch_size_half-1)+(j+patch_size_half-1)*patch_size]=(patch_now[(i+patch_size_half-1)+(j+patch_size_half-1)*patch_size]-patch_now_min)/(patch_now_max-patch_now_min);
                }
            }*/

            // calculate current psd
            float *psd_now=new float[patch_size*patch_size];
            calc_psd_2D_padding(patch_now,psd_now,patch_size,patch_size);

            // add up all psd
            for(int i=0;i<patch_size*patch_size;i++)
            {
                psd_sum[i]+=psd_now[i];
            }

            patch_x_center+=patch_x_step;
            patch_y_center+=patch_y_step;
            patch_num++;

            delete [] patch_now;
            delete [] psd_now;

        }
        patch_x_center=x_center-patch_x_step;
        patch_y_center=y_center-patch_y_step;
        while(patch_x_center+patch_size_half<stack_orig.getNx() && patch_x_center-patch_size_half+1>=0 && patch_y_center+patch_size_half<stack_orig.getNy() && patch_y_center-patch_size_half+1>=0) // 反向搜
        {
            // get current patch
            float *patch_now=new float[patch_size*patch_size];
            for(int i=-patch_size_half+1;i<=patch_size_half;i++)
            {
                for(int j=-patch_size_half+1;j<=patch_size_half;j++)
                {
                    patch_now[(i+patch_size_half-1)+(j+patch_size_half-1)*patch_size]=image_now[(patch_x_center+i)+(patch_y_center+j)*stack_orig.getNx()];
                }
            }

            // calculate current psd
            float *psd_now=new float[patch_size*patch_size];
            calc_psd_2D_padding(patch_now,psd_now,patch_size,patch_size);

            // add up all psd
            for(int i=0;i<patch_size*patch_size;i++)
            {
                psd_sum[i]+=psd_now[i];
            }

            patch_x_center-=patch_x_step;
            patch_y_center-=patch_y_step;
            patch_num++;

            delete [] patch_now;
            delete [] psd_now;
        }
        for(int i=0;i<patch_size*patch_size;i++)    // averaging
        {
            psd_sum[i]/=patch_num;
        }

//        spectrum_box_convolution(psd_sum,res_min,pix,patch_size,patch_size);
        stack_psd.write2DIm(psd_sum,n);

        cout << "Done" << endl;

        delete [] image_now;
        delete [] psd_sum;
    }
    stack_psd.close();

    cout << endl << "Finish CTF estimation successfully!" << endl << endl;

}