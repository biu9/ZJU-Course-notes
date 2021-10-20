/*******************************************************************
 *       Filename:  ReconstructionAlgo.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/07/2020 05:40:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruan Huabin
 *          Email:  ruanhuabin@tsinghua.edu.cn
 *        Company:  Dep. of CS, Tsinghua Unversity
 *
 *******************************************************************/
#include "ReconstructionAlgo_WBP_RAM.h"
#include "mrc.h"
#include "CTF.h"
#include "math.h"
#include "fftw3.h"
#include "omp.h"
#include "util.h"

static void buf2fft(float *buf, float *fft, int nx, int ny)
{
    int nxb = nx + 2 - nx % 2;
    int i;
#pragma omp parallel for
    for (i = 0; i < (nx + 2 - nx % 2) * ny; i++)
    {
        fft[i] = 0.0;
    }
#pragma omp parallel for
    for (i = 0; i < ny; i++)
    {
        memcpy(fft + i * nxb, buf + i * nx, sizeof(float) * nx);
    }
}

static void fft2buf(float *buf, float *fft, int nx, int ny)
{
    int nxb = nx + 2 - nx % 2;
    int i;
#pragma omp parallel for
    for (i = 0; i < nx * ny; i++)
    {
        buf[i] = 0.0;
    }
#pragma omp parallel for
    for (i = 0; i < ny; i++)
    {
        memcpy(buf + i * nx, fft + i * nxb, sizeof(float) * nx);
    }
}

static void buf2fft_padding_1D(float *buf, float *fft, int nx_orig, int nx_final, int ny_orig, int ny_final)
{
    int nxb = nx_final + 2 - nx_final % 2;
    int nxp = nx_final - nx_orig + 1;
    int i, j;
#pragma omp parallel for
    for (i = 0; i < (nx_final + 2 - nx_final % 2) * ny_final; i++)
    {
        fft[i] = 0.0;
    }
    //#pragma omp parallel for
    for (i = 0; i < ny_orig; i++)
    {
        memcpy(fft + i * nxb, buf + i * nx_orig, sizeof(float) * nx_orig);
        for (j = nx_orig; j < nx_final; j++) // padding for continuity (FFT本质是周期延拓后做DFT，将首尾连接以保证连续性)
        {
            fft[i * nxb + j] = (float(j - nx_orig + 1) / float(nxp)) * buf[i * nx_orig] + (float(nx_final - j) / float(nxp)) * buf[(i + 1) * nx_orig - 1];
        }
    }
}

static void fft2buf_padding_1D(float *buf, float *fft, int nx_orig, int nx_final, int ny_orig, int ny_final)
{
    int nxb = nx_final + 2 - nx_final % 2;
    int i;
#pragma omp parallel for
    for (i = 0; i < nx_orig * ny_orig; i++)
    {
        buf[i] = 0.0;
    }
#pragma omp parallel for
    for (i = 0; i < ny_orig; i++)
    {
        memcpy(buf + i * nx_orig, fft + i * nxb, sizeof(float) * nx_orig);
    }
}

static void filter_weighting(float *data, int Nx, float radial, float sigma)
{
    int Nx_padding = int(Nx / 10);
    int Nx_final = Nx + Nx_padding;
    fftwf_plan plan_fft, plan_ifft;
    float *bufc = new float[Nx_final + 2 - Nx_final % 2];
    plan_fft = fftwf_plan_dft_r2c_1d(Nx_final, (float *)bufc, reinterpret_cast<fftwf_complex *>(bufc), FFTW_ESTIMATE);
    plan_ifft = fftwf_plan_dft_c2r_1d(Nx_final, reinterpret_cast<fftwf_complex *>(bufc), (float *)bufc, FFTW_ESTIMATE);
    buf2fft_padding_1D(data, bufc, Nx, Nx_final, 1, 1);
    fftwf_execute(plan_fft);

    int radial_Nx = int(floor((Nx_final)*radial));
    float sigma_Nx = float(Nx_final) * sigma;

// loop: Nx_final+2-Nx_final%2 (all Fourier components)
#pragma omp parallel for
    for (int i = 0; i < Nx_final + 2 - Nx_final % 2; i += 2) // radial filtering
    {
        if (i == 0) // DC
        {
            bufc[i] *= 0.2;
            bufc[i + 1] *= 0.2;
        }
        else if (i / 2 <= radial_Nx) // radial
        {
            bufc[i] *= (i / 2);
            bufc[i + 1] *= (i / 2);
        }
        else // Gaussian falloff
        {
            bufc[i] = bufc[i] * float(radial_Nx) * exp(-float((i / 2 - radial_Nx) * (i / 2 - radial_Nx)) / (sigma_Nx * sigma_Nx));
            bufc[i + 1] = bufc[i + 1] * float(radial_Nx) * exp(-float((i / 2 - radial_Nx) * (i / 2 - radial_Nx)) / (sigma_Nx * sigma_Nx));
        }
    }

    fftwf_execute(plan_ifft);
    fft2buf_padding_1D(data, bufc, Nx, Nx_final, 1, 1);
#pragma omp parallel for
    for (int i = 0; i < Nx; i++) // normalization
    {
        data[i] /= Nx;
    }
    fftwf_destroy_plan(plan_fft);
    fftwf_destroy_plan(plan_ifft);
    delete[] bufc;
}

static void filter_weighting_1D_many(float *data, int Nx, int Ny, float radial, float sigma)
{
    int Nx_padding = int(Nx / 10);
    int Nx_final = Nx + Nx_padding;
    fftwf_plan plan_fft, plan_ifft;
    float *bufc = new float[(Nx_final + 2 - Nx_final % 2) * Ny];
    plan_fft = fftwf_plan_many_dft_r2c(1, &Nx_final, Ny, (float *)bufc, NULL, 1, (Nx_final + 2 - Nx_final % 2), reinterpret_cast<fftwf_complex *>(bufc), NULL, 1, (Nx_final + 2 - Nx_final % 2) / 2, FFTW_ESTIMATE);
    plan_ifft = fftwf_plan_many_dft_c2r(1, &Nx_final, Ny, reinterpret_cast<fftwf_complex *>(bufc), NULL, 1, (Nx_final + 2 - Nx_final % 2) / 2, (float *)bufc, NULL, 1, (Nx_final + 2 - Nx_final % 2), FFTW_ESTIMATE);

    buf2fft_padding_1D(data, bufc, Nx, Nx_final, Ny, Ny);
    fftwf_execute(plan_fft);

    int radial_Nx = int(floor((Nx_final)*radial));
    float sigma_Nx = float(Nx_final) * sigma;
// loop: Ny (all Fourier components for y-axis)
#pragma omp parallel for
    for (int j = 0; j < Ny; j++)
    {
        // loop: Nx_final+2-Nx_final%2 (all Fourier components for x-axis)
        for (int i = 0; i < Nx_final + 2 - Nx_final % 2; i += 2)
        {
            if (i == 0) // DC
            {
                bufc[i + j * (Nx_final + 2 - Nx_final % 2)] *= 0.2;
                bufc[i + 1 + j * (Nx_final + 2 - Nx_final % 2)] *= 0.2;
            }
            else if (i / 2 <= radial_Nx) // radial
            {
                bufc[i + j * (Nx_final + 2 - Nx_final % 2)] *= (i / 2);
                bufc[i + 1 + j * (Nx_final + 2 - Nx_final % 2)] *= (i / 2);
            }
            else // Gaussian falloff
            {
                bufc[i + j * (Nx_final + 2 - Nx_final % 2)] = bufc[i + j * (Nx_final + 2 - Nx_final % 2)] * float(radial_Nx) * exp(-float((i / 2 - radial_Nx) * (i / 2 - radial_Nx)) / (sigma_Nx * sigma_Nx));
                bufc[i + 1 + j * (Nx_final + 2 - Nx_final % 2)] = bufc[i + 1 + j * (Nx_final + 2 - Nx_final % 2)] * float(radial_Nx) * exp(-float((i / 2 - radial_Nx) * (i / 2 - radial_Nx)) / (sigma_Nx * sigma_Nx));
            }
        }
    }

    fftwf_execute(plan_ifft);
    fft2buf_padding_1D(data, bufc, Nx, Nx_final, Ny, Ny);
#pragma omp parallel for
    for (int i = 0; i < Nx * Ny; i++) // normalization
    {
        data[i] /= Nx;
    }

    fftwf_destroy_plan(plan_fft);
    fftwf_destroy_plan(plan_ifft);
    delete[] bufc;
}

static void filter_weighting_2D(float *image, int Nx, int Ny, float radial, float sigma, float psi_rad)
{
    int Nx_padding = 0;
    int Nx_final = Nx_padding + Nx;
    fftwf_plan plan_fft, plan_ifft;
    float *bufc = new float[(Nx_final + 2 - Nx_final % 2) * Ny];
    plan_fft = fftwf_plan_dft_r2c_2d(Ny, Nx_final, (float *)bufc, reinterpret_cast<fftwf_complex *>(bufc), FFTW_ESTIMATE);
    plan_ifft = fftwf_plan_dft_c2r_2d(Ny, Nx_final, reinterpret_cast<fftwf_complex *>(bufc), (float *)bufc, FFTW_ESTIMATE);
    buf2fft(image, bufc, Nx, Ny);
    fftwf_execute(plan_fft);

    float radial_pi = M_PI * radial, sigma_pi = M_PI * sigma;
    float fft_x[Nx_final], fft_y[Ny];
// loop: Nx_final (all Fourier components for x-axis)
#pragma omp parallel for
    for (int i = 0; i < Nx_final; i++)
    {
        fft_x[i] = 2 * M_PI / (Nx_final)*i;
        if (fft_x[i] > M_PI)
        {
            fft_x[i] = fft_x[i] - 2 * M_PI;
        }
    }
// loop: Ny (all Fourier components for y-axis)
#pragma omp parallel for
    for (int j = 0; j < Ny; j++)
    {
        fft_y[j] = 2 * M_PI / Ny * j;
        if (fft_y[j] > M_PI)
        {
            fft_y[j] = fft_y[j] - 2 * M_PI;
        }
    }

    // loop: Ny (all Fourier components for y-axis)
    for (int j = 0; j < Ny; j++)
    {
        // loop: Nx_final+2-Nx_final%2 (all Fourier components for x-axis)
        for (int i = 0; i < Nx_final + 2 - Nx_final % 2; i += 2) // 2D radial filtering
        {
            float x_rot = fft_x[i / 2] * cos(-psi_rad) - fft_y[j] * sin(-psi_rad), y_rot = fft_x[i / 2] * sin(-psi_rad) + fft_y[j] * cos(-psi_rad);
            if (fabs(x_rot) < 1e-6) // DC
            {
                bufc[i + j * (Nx_final + 2 - Nx_final % 2)] *= (0.2 * fft_x[1] * cos(-psi_rad));
                bufc[i + 1 + j * (Nx_final + 2 - Nx_final % 2)] *= (0.2 * fft_x[1] * cos(-psi_rad));
            }
            else if (fabs(x_rot) <= radial_pi) // radial
            {
                bufc[i + j * (Nx_final + 2 - Nx_final % 2)] *= x_rot;
                bufc[i + 1 + j * (Nx_final + 2 - Nx_final % 2)] *= x_rot;
            }
            else // Gaussian falloff
            {
                bufc[i + j * (Nx_final + 2 - Nx_final % 2)] = bufc[i + j * (Nx_final + 2 - Nx_final % 2)] * radial_pi * exp(-((x_rot - radial_pi) * (x_rot - radial_pi)) / (sigma_pi * sigma_pi));
                bufc[i + 1 + j * (Nx_final + 2 - Nx_final % 2)] = bufc[i + 1 + j * (Nx_final + 2 - Nx_final % 2)] * radial_pi * exp(-((x_rot - radial_pi) * (x_rot - radial_pi)) / (sigma_pi * sigma_pi));
            }
        }
    }

    fftwf_execute(plan_ifft);
    fft2buf(image, bufc, Nx, Ny);
#pragma omp parallel for
    for (int i = 0; i < Nx * Ny; i++) // normalization
    {
        image[i] = image[i] / (Nx * Ny);
    }
    fftwf_destroy_plan(plan_fft);
    fftwf_destroy_plan(plan_ifft);
    delete[] bufc;
}

static void ctf_correction(float *image, int Nx, int Ny, CTF ctf, bool flip_contrast, float z_offset) // z_offset in pixels
{
    fftwf_plan plan_fft, plan_ifft;
    float *bufc = new float[(Nx + 2 - Nx % 2) * Ny];
    plan_fft = fftwf_plan_dft_r2c_2d(Ny, Nx, (float *)bufc, reinterpret_cast<fftwf_complex *>(bufc), FFTW_ESTIMATE);
    plan_ifft = fftwf_plan_dft_c2r_2d(Ny, Nx, reinterpret_cast<fftwf_complex *>(bufc), (float *)bufc, FFTW_ESTIMATE);
    buf2fft(image, bufc, Nx, Ny);
    fftwf_execute(plan_fft);

    //cout << "\tSctf_correction测试断点1" << endl;

// loop: Ny (all Fourier components for y-axis
    #pragma omp parallel for
    for (int j = 0; j < Ny; j++)
    {
        // loop: Nx+2-Nx%2 (all Fourier components for x-axis)
        for (int i = 0; i < (Nx + 2 - Nx % 2); i += 2)
        {
            float ctf_now = ctf.computeCTF2D(i / 2, j, Nx, Ny, true, flip_contrast, z_offset);
            bufc[i + j * (Nx + 2 - Nx % 2)] *= ctf_now;
            bufc[(i + 1) + j * (Nx + 2 - Nx % 2)] *= ctf_now;
        }
    }
    //cout << "\tSctf_correction测试断点2" << endl;

    fftwf_execute(plan_ifft);
    fft2buf(image, bufc, Nx, Ny);
//cout << "\tSctf_correction测试断点3" << endl;
#pragma omp parallel for
    for (int i = 0; i < Nx * Ny; i++) // normalization
    {
        image[i] = image[i] / (Nx * Ny);
    }
    //cout << "\tSctf_correction测试断点4" << endl;
    fftwf_destroy_plan(plan_fft);
    fftwf_destroy_plan(plan_ifft);
    //cout << "\tSctf_correction测试断点5" << endl;
    delete[] bufc;
    //cout << "\tSctf_correction测试断点6" << endl;
}

ReconstructionAlgo_WBP_RAM::~ReconstructionAlgo_WBP_RAM()
{
}

void ReconstructionAlgo_WBP_RAM::doReconstruction(map<string, string> &inputPara, map<string, string> &outputPara)
{
    cout << "Run doReconstruction() in ReconstructionAlgo_WBP_RAM" << endl;

    // Input
    map<string, string>::iterator it = inputPara.find("path");
    string path;
    if (it != inputPara.end())
    {
        path = it->second;
        cout << "File path: " << path << endl;
    }
    else
    {
        cout << "No specifit file path, set default: ./" << endl;
        path = "./";
    }

    it = inputPara.find("input_mrc");
    string input_mrc;
    if (it != inputPara.end())
    {
        input_mrc = path + "/" + it->second;
        cout << "Input file name: " << input_mrc << endl;
    }
    else
    {
        cerr << "No input file name!" << endl;
        abort();
    }
    MRC stack_orig(input_mrc.c_str(), "rb");
    if (!stack_orig.hasFile())
    {
        cerr << "Cannot open input mrc stack!" << endl;
        abort();
    }

    it = inputPara.find("output_mrc");
    string output_mrc;
    if (it != inputPara.end())
    {
        output_mrc = path + "/" + it->second;
        cout << "Output file name: " << output_mrc << endl;
    }
    else
    {
        cout << "No output file name, set default: tomo.rec" << endl;
        output_mrc = "tomo.rec";
    }

    it = inputPara.find("prfx");
    string prfx;
    if (it != inputPara.end())
    {
        prfx = path + "/" + it->second;
        cout << "Prefix: " << prfx << endl;
    }
    else
    {
        cout << "No prfx, set default: tomo" << endl;
        prfx = path + "/" + "tomo";
    }

    it = inputPara.find("h");
    int h;
    if (it != inputPara.end())
    {
        h = atoi(it->second.c_str());
        cout << "Reconstruction height: " << h << endl;
    }
    else
    {
        h = int(stack_orig.getNx() / 4);
        cout << "No height for reconstruction, set default (Nx/4): " << h << endl;
    }

    bool skip_ctfcorrection, skip_weighting, skip_3dctf;
    it = inputPara.find("skip_ctfcorrection");
    if (it != inputPara.end())
    {
        skip_ctfcorrection = atoi(it->second.c_str());
        cout << "Skip CTF correction: " << skip_ctfcorrection << endl;
    }
    else
    {
        cout << "No skip_ctfcorrection, set default: 0" << endl;
        skip_ctfcorrection = 0;
    }
    it = inputPara.find("skip_3dctf");
    if (it != inputPara.end())
    {
        skip_3dctf = atoi(it->second.c_str());
        cout << "Skip 3D-CTF: " << skip_3dctf << endl;
    }
    else
    {
        cout << "No skip_3dctf, set default: 0 (Perform 3D-CTF correction)" << endl;
        skip_3dctf = 0;
    }
    it = inputPara.find("skip_weighting");
    if (it != inputPara.end())
    {
        skip_weighting = atoi(it->second.c_str());
        cout << "Skip weighting: " << skip_weighting << endl;
    }
    else
    {
        cout << "No skip_weighting, set default: 0 (Perform WBP)" << endl;
        skip_weighting = 0;
    }

    float weighting_radial = 0.05, weighting_sigma = 0.5;
    if (!skip_weighting)
    {
        cout << "Weighting parameters:" << endl;
        it = inputPara.find("weighting_radial");
        if (it != inputPara.end())
        {
            weighting_radial = atof(it->second.c_str());
            cout << "Radial: " << weighting_radial << endl;
        }
        else
        {
            cout << "No weighting_radial, set default: 0.05" << endl;
            weighting_radial = 0.05;
        }
        it = inputPara.find("weighting_sigma");
        if (it != inputPara.end())
        {
            weighting_sigma = atof(it->second.c_str());
            cout << "Sigma: " << weighting_sigma << endl;
        }
        else
        {
            cout << "No weighting_sigma, set default: 0.5" << endl;
            weighting_sigma = 0.5;
        }
    }

    it = inputPara.find("input_tlt");
    string input_tlt;
    if (it != inputPara.end())
    {
        input_tlt = path + "/" + it->second;
        cout << "Input tlt file name: " << input_tlt << endl;
    }
    else
    {
        cerr << "No input tlt file name!" << endl;
        abort();
    }
    FILE *ftlt = fopen(input_tlt.c_str(), "r");
    if (ftlt == NULL)
    {
        cerr << "Cannot open tlt file!" << endl;
        abort();
    }
    float theta[stack_orig.getNz()];
    float theta_max = 0.0;
    //#pragma omp parallel for
    for (int n = 0; n < stack_orig.getNz(); n++)
    {
        fscanf(ftlt, "%f", &theta[n]);
        if (fabs(theta[n]) > theta_max)
        {
            theta_max = fabs(theta[n]);
        }
    }
    fflush(ftlt);
    fclose(ftlt);

    bool unrotated_stack = false;
    it = inputPara.find("unrotated_stack");
    if (it != inputPara.end())
    {
        unrotated_stack = atoi(it->second.c_str());
        cout << "Input unrotated stack: " << unrotated_stack << endl;
    }
    else
    {
        cout << "No unrotated stack, input rotated stack" << endl;
        unrotated_stack = 0;
    }

    int h_tilt_max = int(ceil(float(stack_orig.getNx()) * sin(theta_max / 180 * M_PI) + float(h) * cos(theta_max / 180 * M_PI))) + 1; // the maximum height after tilt

    string path_psi = path + "/" + "psi.txt";
    FILE *fpsi = fopen(path_psi.c_str(), "r");
    if (!fpsi)
    {
        cerr << "No psi found!" << endl;
        abort();
    }
    float psi_deg, psi_rad;
    fscanf(fpsi, "%f", &psi_deg);
    psi_rad = psi_deg * M_PI / 180;
    fflush(fpsi);
    fclose(fpsi);
    cout << "psi: " << psi_deg << endl;

    CTF ctf_para[stack_orig.getNz()];
    float Cs, pix, volt, w_cos;
    bool flip_contrast = false;
    int defocus_step = 1;
    it = inputPara.find("pixel_size");
    if (it != inputPara.end())
    {
        pix = atof(it->second.c_str());
        cout << "Pixel size (A): " << pix << endl;
    }
    else
    {
        cerr << "No pixel size!" << endl;
        abort();
    }
    if (!skip_ctfcorrection) // read in defocus file for CTF correction
    {
        it = inputPara.find("Cs");
        if (it != inputPara.end())
        {
            Cs = atof(it->second.c_str());
            cout << "Cs (mm): " << Cs << endl;
        }
        else
        {
            cerr << "No Cs!" << endl;
            abort();
        }
        it = inputPara.find("voltage");
        if (it != inputPara.end())
        {
            volt = atof(it->second.c_str());
            cout << "Accelerating voltage (kV): " << volt << endl;
        }
        else
        {
            cerr << "No accelerating voltage!" << endl;
            abort();
        }
        it = inputPara.find("w");
        if (it != inputPara.end())
        {
            w_cos = atof(it->second.c_str());
            cout << "Amplitude contrast: " << w_cos << endl;
        }
        else
        {
            cerr << "No amplitude contrast!" << endl;
            abort();
        }

        it = inputPara.find("flip_contrast");
        if (it != inputPara.end())
        {
            flip_contrast = atoi(it->second.c_str());
            cout << "Flip contrast: " << flip_contrast << endl;
        }
        else
        {
            cout << "No flip contrast, set default: 0" << endl;
            flip_contrast = false;
        }

        it = inputPara.find("defocus_file");
        string defocus_file;
        if (it != inputPara.end())
        {
            defocus_file = path + "/" + it->second;
            cout << "Defocus file name: " << defocus_file << endl;
        }
        else
        {
            cout << "No defocus file name, set default: defocus_file.txt" << endl;
            defocus_file = "defocus_file.txt";
        }
        FILE *fdefocus = fopen(defocus_file.c_str(), "r");
        if (!fdefocus)
        {
            cerr << "Cannot open defocus file!" << endl;
            abort();
        }

        for (int n = 0; n < stack_orig.getNz(); n++)
        {
            ctf_para[n].setN(n);
            ctf_para[n].setAllImagePara(pix, volt, Cs);
            float defocus_tmp[7];
            for (int i = 0; i < 7; i++) // CTFFIND4 style
            {
                fscanf(fdefocus, "%f", &defocus_tmp[i]);
            }
            if (unrotated_stack)
            {
                ctf_para[n].setAllCTFPara(defocus_tmp[1], defocus_tmp[2], defocus_tmp[3], defocus_tmp[4], w_cos);
            }
            else
            {
                ctf_para[n].setAllCTFPara(defocus_tmp[1], defocus_tmp[2], defocus_tmp[3] - psi_deg, defocus_tmp[4], w_cos); // 特别注意：目前的CTF估计结果取自CTFFIND4，是用原图（即
                未经旋转的图）估计的，因此对于重构旋转后的图，像散角（astig）也要旋转对应的角度！！！
            }
        }
        fflush(fdefocus);
        fclose(fdefocus);

        if (!skip_3dctf)
        {
            it = inputPara.find("defocus_step");
            if (it != inputPara.end())
            {
                defocus_step = atoi(it->second.c_str());
                cout << "Defocus step (pixels): " << defocus_step << endl;
            }
            else
            {
                cout << "No defocus step, set default: 1" << endl;
                defocus_step = 1;
            }
        }
    }

    // Reconstruction
    cout << endl
         << "Reconstruction with (W)BP in RAM:" << endl
         << endl;
    if (!unrotated_stack) // input rotated stack (y-axis as tilt axis)
    {
        cout << "Using rotated stack" << endl;

        float *stack_recon[stack_orig.getNy()]; // (x,z,y)
#pragma omp parallel for
        for (int j = 0; j < stack_orig.getNy(); j++)
        {
            stack_recon[j] = new float[stack_orig.getNx() * h];
            for (int i = 0; i < stack_orig.getNx() * h; i++)
            {
                stack_recon[j][i] = 0.0;
            }
        }

        cout << "Start reconstruction:" << endl;
        float x_orig_offset = float(stack_orig.getNx()) / 2.0, z_orig_offset = float(h) / 2.0;
        // loop: Nz (number of images)
        for (int n = 0; n < stack_orig.getNz(); n++) // loop for every micrograph
        {
            cout << "Image " << n << ":" << endl;
            float theta_rad = theta[n] / 180 * M_PI;
            float *image_now = new float[stack_orig.getNx() * stack_orig.getNy()];
            stack_orig.read2DIm_32bit(image_now, n);
            float *image_now_backup = new float[stack_orig.getNx() * stack_orig.getNy()];
            memcpy(image_now_backup, image_now, sizeof(float) * stack_orig.getNx() * stack_orig.getNy());

            if (skip_ctfcorrection) // no correction, simple (W)BP
            {
                cout << "\tSkip CTF correction, use raw micrograph!" << endl;

                // weighting
                if (!skip_weighting)
                {
                    cout << "\tStart weighting: " << endl;
                    filter_weighting_1D_many(image_now, stack_orig.getNx(), stack_orig.getNy(), weighting_radial, weighting_sigma);
                    cout << "\tDone!" << endl;
                }

                // reconstruction
                cout << "\tStart reconstruction, loop over xz-plane:" << endl;
                float *strip_now;
                float *recon_now;

                strip_now = new float[stack_orig.getNx()];
                recon_now = new float[stack_orig.getNx() * h]; // 第一维x，第二维z

                // loop: Ny (number of xz-slices)
                for (int j = 0; j < stack_orig.getNy(); j++)
                {
                    memcpy(strip_now, image_now + j * stack_orig.getNx(), sizeof(float) * stack_orig.getNx());

// BP
// loop: Nx*h (whole xz-slice)
#pragma omp parallel for
                    for (int i = 0; i < stack_orig.getNx() * h; i++)
                    {
                        recon_now[i] = 0.0;
                    }
                    // loop: Nx*h (whole xz-slice)
                    // #pragma omp parallel for
                    for (int k = 0; k < h; k++)
                    {
                        for (int i = 0; i < stack_orig.getNx(); i++) // loop for the xz-plane to perform BP
                        {
                            float x_orig = (float(i) - x_orig_offset) * cos(theta_rad) - (float(k) - z_orig_offset) * sin(theta_rad) + x_orig_offset;
                            float z_orig = (float(i) - x_orig_offset) * sin(theta_rad) + (float(k) - z_orig_offset) * cos(theta_rad) + z_orig_offset;
                            float coeff = x_orig - floor(x_orig);
                            if (floor(x_orig) >= 0 && ceil(x_orig) < stack_orig.getNx())
                            {
                                recon_now[i + k * stack_orig.getNx()] = (1 - coeff) * strip_now[int(floor(x_orig))] + (coeff)*strip_now[int(ceil(x_orig))];
                            }
                            else
                            {
                                recon_now[i + k * stack_orig.getNx()] = 0.0;
                            }
                        }
                    }
// loop: Nx*h (whole xz-slice)
#pragma omp parallel for
                    for (int i = 0; i < stack_orig.getNx() * h; i++)
                    {
                        stack_recon[j][i] += recon_now[i];
                    }
                }

                delete[] strip_now;
                delete[] recon_now;

                cout << "\tDone" << endl;
            }
            else // perform CTF correction
            {
                if (skip_3dctf) // perform simple CTF correction (no consideration of height)
                {
                    cout << "\tPerform uniform CTF correction!" << endl;

                    // correction
                    cout << "\tStart correction: " << endl;
                    ctf_correction(image_now, stack_orig.getNx(), stack_orig.getNy(), ctf_para[n], flip_contrast, 0.0);
                    cout << "\tDone!" << endl;

                    // weighting
                    if (!skip_weighting)
                    {
                        cout << "\tStart weighting: " << endl;
                        filter_weighting_1D_many(image_now, stack_orig.getNx(), stack_orig.getNy(), weighting_radial, weighting_sigma);
                        cout << "\tDone!" << endl;
                    }

                    // recontruction
                    cout << "\tStart reconstuction, loop over xz-plane:" << endl;

                    //---- float *strip_now;
                    //---- float *recon_now;

                    //---- strip_now=new float[stack_orig.getNx()];
                    //---- recon_now=new float[stack_orig.getNx()*h];  // 第一维x，第二维z

// loop: Ny (number of xz-slices)
// 应该有很多时间花在这个上面
#pragma omp parallel for
                    for (int j = 0; j < stack_orig.getNy(); j++)
                    {

                        float *strip_now;
                        float *recon_now;
                        strip_now = new float[stack_orig.getNx()];
                        recon_now = new float[stack_orig.getNx() * h]; // 第一维x，第二维z

                        memcpy(strip_now, image_now + j * stack_orig.getNx(), sizeof(float) * stack_orig.getNx());

// BP
// loop: Nx*h (whole xz-slice)
#pragma omp parallel for
                        for (int i = 0; i < stack_orig.getNx() * h; i++)
                        {
                            recon_now[i] = 0.0;
                        }
// loop: Nx*h (whole xz-slice)
#pragma omp parallel for
                        for (int k = 0; k < h; k++)
                        {
                            for (int i = 0; i < stack_orig.getNx(); i++) // loop for the xz-plane to perform BP
                            {
                                float x_orig = (float(i) - x_orig_offset) * cos(theta_rad) - (float(k) - z_orig_offset) * sin(theta_rad) + x_orig_offset;
                                float z_orig = (float(i) - x_orig_offset) * sin(theta_rad) + (float(k) - z_orig_offset) * cos(theta_rad) + z_orig_offset;
                                float coeff = x_orig - floor(x_orig);
                                if (floor(x_orig) >= 0 && ceil(x_orig) < stack_orig.getNx())
                                {
                                    recon_now[i + k * stack_orig.getNx()] = (1 - coeff) * strip_now[int(floor(x_orig))] + (coeff)*strip_now[int(ceil(x_orig))];
                                }
                                else
                                {
                                    recon_now[i + k * stack_orig.getNx()] = 0.0;
                                }
                            }
                        }
// loop: Nx*h (whole xz-slice)
#pragma omp parallel for
                        for (int i = 0; i < stack_orig.getNx() * h; i++)
                        {
                            stack_recon[j][i] += recon_now[i];
                        }
                        delete[] strip_now;
                        delete[] recon_now;
                    }

                    // delete [] strip_now;//------------------------------------------------------------
                    // delete [] recon_now;//----------------------------------

                    cout << "\tDone" << endl;
                }
                else // perform 3D-CTF correction
                {
                    cout << "\tPerform 3D-CTF correction!" << endl;

                    // write all corrected and weighted images in one mrc stack
                    cout << "\tPerform 3D correction & save corrected stack:" << endl;
                    float *stack_corrected[int(h_tilt_max / defocus_step) + 2]; // 第一维遍历不同高度，第二维x，第三维y
                    int n_zz = 0;

                    // weighting
                    if (!skip_weighting)
                    {
                        cout << "\tStart weighting..." << endl;
                        //    printf("Start weighting...\n");
                        filter_weighting_1D_many(image_now, stack_orig.getNx(), stack_orig.getNy(), weighting_radial, weighting_sigma);
                        cout << "\tDone" << endl;
                        //    printf("Done\n");
                    }

                    // 3D-CTF correction
                    //printf("测试节点1\n");
                    cout << "\tStart 3D-CTF correction..." << endl;
                    //printf("测试节点2\n");

                    //printf("float* image_now_temp = new float[stack_orig.getNx()*stack_orig.getNy()];..................\n");
                    float *image_now_temp = new float[stack_orig.getNx() * stack_orig.getNy()];
                    //cout << "\t测试断点1" << endl;
                    //loop: number of blocks (for 3D-CTF correction)
                    //printf("测试节点3\n");

                    // #pragma omp parallel for 加了之后会显示aborted的错误
                    //#pragma omp parallel for private(image_now_temp)
                    for (int zz = -int(h_tilt_max / 2); zz < int(h_tilt_max / 2); zz += defocus_step) // loop over every height (correct with different defocus)
                    {
                        int daxiao = stack_orig.getNx() * stack_orig.getNy();
                        int n_z = (zz + int(h_tilt_max / 2)) / defocus_step;
                        stack_corrected[n_z] = new float[daxiao];
                        memcpy(stack_corrected[n_z], image_now, sizeof(float) * daxiao); // get the raw image!!!
                        ctf_correction(stack_corrected[n_z], stack_orig.getNx(), stack_orig.getNy(), ctf_para[n], flip_contrast, float(zz) + float(defocus_step - 1) / 2);
                        n_zz++;
                    }

                    cout << "\tDone!" << endl;

                    // recontruction

                    cout << "\tPerform reconstruction:" << endl;

                    float *recon_now;

                    recon_now = new float[stack_orig.getNx() * h]; // 第一维x，第二维z

                    // loop: Ny (number of xz-slices)
                    //#pragma omp parallel for
                    for (int j = 0; j < stack_orig.getNy(); j++)
                    {
// BP
// loop: Nx*h (whole xz-slice)
#pragma omp parallel for
                        for (int i = 0; i < stack_orig.getNx() * h; i++)
                        {
                            recon_now[i] = 0.0;
                        }
// loop: Nx*h (whole xz-slice)
// 时间主要用在下面的两个for上面了,加了之后能快大概两分钟
#pragma omp parallel for
                        for (int k = 0; k < h; k++)
                        {
                            for (int i = 0; i < stack_orig.getNx(); i++) // loop for the xz-plane to perform BP
                            {
                                float x_orig = (float(i) - x_orig_offset) * cos(theta_rad) - (float(k) - z_orig_offset) * sin(theta_rad) + x_orig_offset;
                                float z_orig = (float(i) - x_orig_offset) * sin(theta_rad) + (float(k) - z_orig_offset) * cos(theta_rad) + z_orig_offset;
                                float coeff = x_orig - floor(x_orig);
                                int n_z = floor(((z_orig - z_orig_offset) + int(h_tilt_max / 2)) / defocus_step); // the num in the corrected stack for the current height
                                if (n_z >= 0 && n_z < n_zz)
                                {
                                    if (floor(x_orig) >= 0 && ceil(x_orig) < stack_orig.getNx())
                                    {
                                        recon_now[i + k * stack_orig.getNx()] = (1 - coeff) * stack_corrected[n_z][j * stack_orig.getNx() + int(floor(x_orig))] + (coeff)*stack_corrected[n_z][j * stack_orig.getNx() + int(ceil(x_orig))];
                                    }
                                    else
                                    {
                                        recon_now[i + k * stack_orig.getNx()] = 0.0;
                                    }
                                }
                                else
                                {
                                    recon_now[i + k * stack_orig.getNx()] = 0.0;
                                }
                            }
                        }
// loop: Nx*h (whole xz-slice)
#pragma omp parallel for
                        for (int i = 0; i < stack_orig.getNx() * h; i++)
                        {
                            stack_recon[j][i] += recon_now[i];
                        }
                    }

                    delete[] recon_now;

                    cout << "\tDone" << endl;

                    for (int n_z = 0; n_z < n_zz; n_z++)
                    {
                        delete[] stack_corrected[n_z];
                    }
                }
            }
            delete[] image_now;
            delete[] image_now_backup;
        }

        // write out final result
        cout << "Wrtie out final reconstruction result:" << endl;
        MRC stack_final(output_mrc.c_str(), "wb");
        stack_final.createMRC_empty(stack_orig.getNx(), h, stack_orig.getNy(), 2); // (x,z,y)
        // loop: Ny (number of xz-slices)
        for (int j = 0; j < stack_orig.getNy(); j++)
        {
            stack_final.write2DIm(stack_recon[j], j);
        }

        // update MRC header
        int threads = 3;
        float min_thread[threads], max_thread[threads];
        double mean_thread[threads];
#pragma omp parallel for
        for (int th = 0; th < threads; th++)
        {
            min_thread[th] = stack_recon[0][0];
            max_thread[th] = stack_recon[0][0];
            mean_thread[th] = 0.0;
        }
        //        #pragma omp parallel for
        for (int j = 0; j < stack_orig.getNy(); j++)
        {
            double mean_now = 0.0;
            for (int i = 0; i < stack_orig.getNx() * h; i++)
            {
                mean_now += stack_recon[j][i];
                if (min_thread[j % threads] > stack_recon[j][i])
                {
                    min_thread[j % threads] = stack_recon[j][i];
                }
                if (max_thread[j % threads] < stack_recon[j][i])
                {
                    max_thread[j % threads] = stack_recon[j][i];
                }
            }
            mean_thread[j % threads] += (mean_now / (stack_orig.getNx() * h));
        }
        float min_all = min_thread[0];
        float max_all = max_thread[0];
        double mean_all = 0;
        //#pragma omp parallel for
        for (int th = 0; th < threads; th++)
        {
            mean_all += mean_thread[th];
            if (min_all > min_thread[th])
            {
                min_all = min_thread[th];
            }
            if (max_all < max_thread[th])
            {
                max_all = max_thread[th];
            }
        }
        mean_all /= stack_orig.getNy();
        stack_final.computeHeader(pix, false, min_all, max_all, float(mean_all));

#pragma omp parallel for
        for (int j = 0; j < stack_orig.getNy(); j++)
        {
            delete[] stack_recon[j];
        }

        stack_final.close();
        cout << "Done" << endl;
    }

    stack_orig.close();

    cout << endl
         << "Finish reconstruction successfully!" << endl;
    cout << "All results save in: " << path << endl
         << endl;
}