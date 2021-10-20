#include "mrc.h"
#include "stdio.h"
#include <cstring>
#include "omp.h"

MRC::MRC()
{
    memset((void *)&m_header, 0, sizeof(MRCHeader));
    m_header.mode = 2;
    m_header.cellb[0] = 90;
    m_header.cellb[1] = 90;
    m_header.cellb[2] = 90;
    m_header.mapc = 1;
    m_header.mapr = 2;
    m_header.maps = 3;
    m_fp = NULL;
}

MRC::MRC(const char *filename, const char *mode)
{
    memset((void *)&m_header, 0, sizeof(MRCHeader));
    m_header.mode = 2;
    m_header.cellb[0] = 90;
    m_header.cellb[1] = 90;
    m_header.cellb[2] = 90;
    m_header.mapc = 1;
    m_header.mapr = 2;
    m_header.maps = 3;
    m_fp = NULL;
    open(filename, mode);
}

MRC::~MRC()
{
}

int MRC::open(const char *filename, const char *mode)
{
    close();
    m_fp = fopen(filename, mode);

    if (m_fp == NULL)
    {
        return 0;
    }

    //read file header
    rewind(m_fp);

    if (fread(&m_header, 1, 1024, m_fp) < 1024)
    {
        return -1;
    }

    return 1;
}

void MRC::close()
{
    if (m_fp != NULL)
    {
        fclose(m_fp);
    }

    m_fp = NULL;
}

void MRC::printInfo()
{
    if (m_fp == NULL)
    {
        printf("No MRC file was opened!");
        return;
    }

    printf("\tMRC Header size:                   %12d\n", sizeof(MRCHeader));
    printf("\tNum of columns, rows,sections:     %12d %12d %12d\n", m_header.nx, m_header.ny, m_header.nz);
    printf("\tMode:                              %12d\n", m_header.mode);
    printf("\tNum of First column, row, section: %12d %12d %12d\n", m_header.nxstart, m_header.nystart, m_header.nzstart);
    printf("\tNum of intervals along x, y, z:    %12d %12d %12d\n", m_header.mx, m_header.my, m_header.mz);
    printf("\tCell dimensions in angstroms:      %12.3f %12.3f %12.3f\n", m_header.cella[0], m_header.cella[1], m_header.cella[2]);
    printf("\tCell angles in degrees:            %12.3f %12.3f %12.3f\n", m_header.cellb[0], m_header.cellb[1], m_header.cellb[2]);
    printf("\tAxis for cols, rows, sections:     %12d %12d %12d\n", m_header.mapc, m_header.mapr, m_header.maps);
    printf("\tMin, max, mean density value:      %12.3f %12.3f %12.3f\n", m_header.dmin, m_header.dmax, m_header.dmean);
    printf("\tSpace group number:                %12d\n", m_header.ispg);
    printf("\tNum of bytes for symmetry data:    %12d\n", m_header.nsymbt);
    //printf("\tExtra:                             %s\n",m_header.extra);
    printf("\tOrigin in X,Y,Z:                   %12.3f %12.3f %12.3f\n", m_header.origin[0], m_header.origin[1], m_header.origin[2]);
    printf("\tFile type:                         %c%c%c%c\n", m_header.map[0], m_header.map[1], m_header.map[2], m_header.map[3]);
    printf("\tMachine stamp:                     %12d\n", m_header.machst);
    printf("\trms deviationfrom mean density:    %12.3f\n", m_header.rms);
    printf("\tNum of labels being used:          %12d\n", m_header.nlabels);

    for (int i = 0; i < m_header.nlabels; i++)
    {
        printf("\t\t%s\n", m_header.label[i]);
    }
}

void MRC::getHeader(const MRCHeader *pheader)
{
    memcpy((void *)pheader, (void *)&m_header, 1024);
}

int MRC::getNx()
{
    return m_header.nx;
}

int MRC::getNy()
{
    return m_header.ny;
}

int MRC::getNz()
{
    return m_header.nz;
}

int MRC::getWordLength()
{
    switch (m_header.mode)
    {
        case 0:
            return 1;

        case 1:
            return 2;

        case 2:
            return 4;

        case 3:
            return 4;

        case 4:
            return 8;

        case 5:
            return 1;

        case 6:
            return 2;
    }

    return 0;
}

int MRC::getImSize()
{
    return getNx() * getNy() * getWordLength();
}

int MRC::getMode()
{
    return m_header.mode;
}

int MRC::getSymdatasize()
{
    return m_header.nsymbt;
}

float MRC::getMin()
{
    return m_header.dmin;
}

float MRC::getMax()
{
    return m_header.dmax;
}

float MRC::getMean()
{
    return m_header.dmean;
}

int MRC::readAllData(void *buf)
{
    int ImSize = getNx() * getNy() * getNz() * getWordLength();
    long offset = 1024 + getSymdatasize();

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fread(buf, 1, ImSize, m_fp);
}

int MRC::writeAllData(void *buf)
{
    int ImSize = getNx() * getNy() * getNz() * getWordLength();
    long offset = 1024 + getSymdatasize();

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fwrite(buf, 1, ImSize, m_fp);
}

int MRC::read2DIm(void *buf, int n)
{
    size_t ImSize = getImSize();
    size_t offset = 1024 + getSymdatasize() + (size_t)n * ImSize;

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fread(buf, 1, ImSize, m_fp);
}

int MRC::readLine(void *buf, int nimage, int nline)
{
    size_t ImSize = getImSize();
    size_t LineLength = getNx() * getWordLength();
    size_t offset = 1024 + getSymdatasize() + (size_t)nimage * ImSize + nline * LineLength;      

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fread(buf, 1, LineLength, m_fp);
}

int MRC::readPixel(void *buf, int nimage, int nline, int npixel)
{
    size_t ImSize = getImSize();
    size_t LineLength = getNx() * getWordLength();

    if (npixel >= LineLength)
    {
        return 0;
    }

    size_t offset = 1024 + getSymdatasize() + nimage * ImSize + nline * LineLength + npixel * getWordLength();

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fread(buf, 1, getWordLength(), m_fp);
}

int MRC::readnPixels(void *buf, int nimage, int nline, int npixel, int n)
{
    size_t ImSize = getImSize();
    size_t LineLength = getNx() * getWordLength();

    if (npixel >= LineLength)
    {
        return 0;
    }

    size_t offset = 1024 + getSymdatasize() + nimage * ImSize + nline * LineLength + npixel * getWordLength();

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fread(buf, 1, n * getWordLength(), m_fp);
}


int MRC::readGainInHeader(float *buf)
{
    if (buf == NULL)
    {
        return 0;
    }

    size_t SymDataSize = getSymdatasize();
    size_t GainSize = m_header.nx * m_header.ny * sizeof(float);
    size_t offset = SymDataSize - GainSize; //the SymDatam may contain other data in the beginning

    if (offset < 0)
    {
        return 0;
    }

    if (fseek(m_fp, 1024 + offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fread(buf, 1, GainSize, m_fp);
}


int MRC::write2DIm(void *buf, int n)
{
    size_t ImSize = (size_t)getImSize();
    size_t offset = 1024 + getSymdatasize() + (size_t)n * ImSize;

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fwrite(buf, 1, ImSize, m_fp);
}

int MRC::writeLine(void *buf, int nimage, int nline)
{
    size_t ImSize = getImSize();
    size_t LineLength = getNx() * getWordLength();
    size_t offset = 1024 + getSymdatasize() + nimage * ImSize + nline * LineLength;

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fwrite(buf, 1, LineLength, m_fp);
}

int MRC::writePixel(void *buf, int nimage, int nline, int npixel)
{
    size_t ImSize = getImSize();
    size_t LineLength = getNx() * getWordLength();

    if (npixel >= LineLength)
    {
        return 0;
    }

    size_t offset = 1024 + getSymdatasize() + nimage * ImSize + nline * LineLength + npixel * getWordLength();

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fwrite(buf, 1, getWordLength(), m_fp);
}

int MRC::readSymData(void *buf)
{
    if (buf == NULL)
    {
        return 0;
    }

    size_t ImSize = (size_t)getSymdatasize();
    size_t offset = 1024;

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fread(buf, 1, ImSize, m_fp);
}

int MRC::writeSymData(void *buf)
{
    if (buf == NULL)
    {
        return 0;
    }

    size_t ImSize = (size_t)getSymdatasize();
    size_t offset = 1024;

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fwrite(buf, 1, ImSize, m_fp);
}

void MRC::setHeader(const MRCHeader *pheader)
{
    memcpy((void *)&m_header, (void *)pheader, 1024);
    rewind(m_fp);
    fwrite(&m_header, 1, 1024, m_fp);
}

void MRC::setMin(float min)
{
    m_header.dmin = min;
}

void MRC::setMax(float max)
{
    m_header.dmax = max;
}

void MRC::setMean(float mean)
{
    m_header.dmean = mean;
}

void MRC::updateHeader()
{
    rewind(m_fp);
    fwrite(&m_header, 1, 1024, m_fp);
}

void MRC::computeHeader(float pix,bool is_image)
{
    m_header.cella[0]=float(m_header.nx)*pix;
    m_header.cella[1]=float(m_header.ny)*pix;
    m_header.cella[2]=float(m_header.nz)*pix;

/*    float min_thread[threads],max_thread[threads],mean_thread[threads];
    float *tmp=new float[m_header.nx*m_header.ny];
    read2DIm_32bit(tmp,0);
    for(int th=0;th<threads;th++)
    {
        min_thread[th]=tmp[0];
        max_thread[th]=tmp[0];
        mean_thread[th]=0.0;
    }
    delete [] tmp;
    #pragma omp parallel for num_threads(threads)
    for(int k=0;k<m_header.nz;k++)
    {
        float *slice_now=new float[m_header.nx*m_header.ny];
        read2DIm_32bit(slice_now,k);
        for(int i=0;i<m_header.nx*m_header.ny;i++)
        {
            mean_thread[omp_get_thread_num()]+=slice_now[i];
            if(min_thread[omp_get_thread_num()]>slice_now[i])
            {
                min_thread[omp_get_thread_num()]=slice_now[i];
            }
            if(max_thread[omp_get_thread_num()]<slice_now[i])
            {
                max_thread[omp_get_thread_num()]=slice_now[i];
            }
        }
        delete [] slice_now;
    }
    float min_all=min_thread[0],max_all=max_thread[0],mean_all=mean_thread[0];
    for(int th=1;th<thread_num;th++)
    {
        mean_all+=mean_thread[th];
        if(min_all>min_thread[th])
        {
            min_all=min_thread[th];
        }
        if(max_all<max_thread[th])
        {
            max_all=max_thread[th];
        }
    }
    mean_all/=(m_header.nx*m_header.ny*m_header.nz);
    m_header.dmin=min_all;
    m_header.dmax=max_all;
    m_header.dmean=mean_all;*/

    float *tmp=new float[m_header.nx*m_header.ny];
    read2DIm_32bit(tmp,0);
    float min_all=tmp[0],max_all=tmp[0];
    double mean_all=0.0;
    delete [] tmp;
    for(int k=0;k<m_header.nz;k++)
    {
        float *slice_now=new float[m_header.nx*m_header.ny];
        double mean_now=0.0;
        read2DIm_32bit(slice_now,k);
        for(int i=0;i<m_header.nx*m_header.ny;i++)
        {
            mean_now+=slice_now[i];
            if(min_all>slice_now[i])
            {
                min_all=slice_now[i];
            }
            if(max_all<slice_now[i])
            {
                max_all=slice_now[i];
            }
        }
        mean_all+=(mean_now/(m_header.nx*m_header.ny));
        delete [] slice_now;
    }
    mean_all/=m_header.nz;
    m_header.dmin=min_all;
    m_header.dmax=max_all;
    m_header.dmean=float(mean_all);

    if(is_image)
    {
        m_header.ispg=0;
    }
    else
    {
        m_header.ispg=1;
    }
//    m_header.ispg=0;

    m_header.map[0]='M';
    m_header.map[1]='A';
    m_header.map[2]='P';
    m_header.map[3]=' ';

    m_header.machst=17476;

    updateHeader();

}

void MRC::computeHeader_omp(float pix,bool is_image,int threads)
{
    m_header.cella[0]=float(m_header.nx)*pix;
    m_header.cella[1]=float(m_header.ny)*pix;
    m_header.cella[2]=float(m_header.nz)*pix;

    float min_thread[threads],max_thread[threads];
    double mean_thread[threads];
    float *tmp=new float[m_header.nx*m_header.ny];
    read2DIm_32bit(tmp,0);
    for(int th=0;th<threads;th++)
    {
        min_thread[th]=tmp[0];
        max_thread[th]=tmp[0];
        mean_thread[th]=0.0;
    }
    delete [] tmp;
    #pragma omp parallel for num_threads(threads)
    for(int k=0;k<m_header.nz;k++)
    {
        float *slice_now=new float[m_header.nx*m_header.ny];
        double mean_now=0.0;
        #pragma omp critical
        {
            read2DIm_32bit(slice_now,k);
        }
        for(int i=0;i<m_header.nx*m_header.ny;i++)
        {
            mean_now+=slice_now[i];
            if(min_thread[omp_get_thread_num()]>slice_now[i])
            {
                min_thread[omp_get_thread_num()]=slice_now[i];
            }
            if(max_thread[omp_get_thread_num()]<slice_now[i])
            {
                max_thread[omp_get_thread_num()]=slice_now[i];
            }
        }
        mean_thread[omp_get_thread_num()]+=(mean_now/(m_header.nx*m_header.ny));
        delete [] slice_now;
    }
    float min_all=min_thread[0],max_all=max_thread[0];
    double mean_all=mean_thread[0];
    for(int th=1;th<threads;th++)
    {
        mean_all+=mean_thread[th];
        if(min_all>min_thread[th])
        {
            min_all=min_thread[th];
        }
        if(max_all<max_thread[th])
        {
            max_all=max_thread[th];
        }
    }
    mean_all/=m_header.nz;
    m_header.dmin=min_all;
    m_header.dmax=max_all;
    m_header.dmean=float(mean_all);

    if(is_image)
    {
        m_header.ispg=0;
    }
    else
    {
        m_header.ispg=1;
    }
//    m_header.ispg=0;

    m_header.map[0]='M';
    m_header.map[1]='A';
    m_header.map[2]='P';
    m_header.map[3]=' ';

    m_header.machst=17476;

    updateHeader();

}

void MRC::computeHeader(float pix,bool is_image,float min_now,float max_now,float mean_now)      
{
    m_header.cella[0]=float(m_header.nx)*pix;
    m_header.cella[1]=float(m_header.ny)*pix;
    m_header.cella[2]=float(m_header.nz)*pix;

    m_header.dmin=min_now;
    m_header.dmax=max_now;
    m_header.dmean=mean_now;

    if(is_image)
    {
        m_header.ispg=0;
    }
    else
    {
        m_header.ispg=1;
    }
//    m_header.ispg=0;

    m_header.map[0]='M';
    m_header.map[1]='A';
    m_header.map[2]='P';
    m_header.map[3]=' ';

    m_header.machst=17476;

    updateHeader();

}

int MRC::createMRC(float *data, int nx, int ny, int nz)
{
    m_header.nx = nx;
    m_header.ny = ny;
    m_header.nz = nz;
    m_header.mx = nx;
    m_header.my = ny;
    m_header.mz = nz;
    m_header.mode = 2;
    m_header.cellb[0] = 90;
    m_header.cellb[1] = 90;
    m_header.cellb[2] = 90;
    m_header.mapc = 1;
    m_header.mapr = 2;
    m_header.maps = 3;
    size_t i, size = nx * ny * nz;
    float min = data[0], max = data[0];
    double mean = 0;

    for (i = 0; i < size; i++)
    {
        if (min > data[i])
        {
            min = data[i];
        }

        if (max < data[i])
        {
            max = data[i];
        }

        mean += data[i];
    }

    mean /= size;
    m_header.dmin = min;
    m_header.dmax = max;
    m_header.dmean = mean;
    updateHeader();
    size_t ImSize = size * sizeof(float);
    size_t offset = 1024 + getSymdatasize();

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fwrite(data, 1, ImSize, m_fp);
}

int MRC::createMRC(short *data, int nx, int ny, int nz)
{
    m_header.nx = nx;
    m_header.ny = ny;
    m_header.nz = nz;
    m_header.mx = nx;
    m_header.my = ny;
    m_header.mz = nz;
    m_header.mode = 1;
    m_header.cellb[0] = 90;
    m_header.cellb[1] = 90;
    m_header.cellb[2] = 90;
    m_header.mapc = 1;
    m_header.mapr = 2;
    m_header.maps = 3;
    size_t i, size = nx * ny * nz;
    short min = data[0], max = data[0];
    double mean = 0;

    for (i = 0; i < size; i++)
    {
        if (min > data[i])
        {
            min = data[i];
        }

        if (max < data[i])
        {
            max = data[i];
        }

        mean += data[i];
    }

    mean /= size;
    m_header.dmin = min;
    m_header.dmax = max;
    m_header.dmean = mean;
    updateHeader();
    size_t ImSize = size * sizeof(short);
    size_t offset = 1024 + getSymdatasize();

    if (fseek(m_fp, offset, SEEK_SET) != 0)
    {
        return 0;
    }

    return fwrite(data, 1, ImSize, m_fp);
}

int MRC::createMRC_empty(int nx, int ny, int nz, int mode)
{
    m_header.nx = nx;
    m_header.ny = ny;
    m_header.nz = nz;
    m_header.mx = nx;
    m_header.my = ny;
    m_header.mz = nz;
    m_header.mode = mode;
    m_header.cellb[0] = 90;
    m_header.cellb[1] = 90;
    m_header.cellb[2] = 90;
    m_header.mapc = 1;
    m_header.mapr = 2;
    m_header.maps = 3;
    size_t i, size = nx * ny * nz;
    float min = 0, max = 0;
    double mean = 0;

    updateHeader();
    size_t ImSize = size * sizeof(float);
    size_t offset = 1024 + getSymdatasize();

    return 1;
}

void MRC::setLabel(const char *str, int line)
{
    strcpy(m_header.label[line], str);
}

char *MRC::getLabel(int line)
{
    return m_header.label[line];
}

bool MRC::hasFile()
{
    if (m_fp == NULL)
    {
        return false;
    }

    else
    {
        return true;
    }
}

int MRC::read2DIm_32bit(float *buf, int n)
{
    int mode = m_header.mode;
    size_t size = m_header.nx * m_header.ny;

    if (size <= 0)
    {
        return 0;
    }

    char *buf8 = NULL;
    unsigned char *bufu8 = NULL;
    short *buf16 = NULL;
    unsigned short *bufu16 = NULL;
    size_t r, i;

    switch (mode)
    {
        case 0:
            buf8 = new char[size];
            r = read2DIm((void *)buf8, n);

            if (r <= 0)
            {
                delete [] buf8;
                return 0;
            }

            for (i = 0; i < size; i++)
            {
                buf[i] = float(buf8[i]);
            }

            delete [] buf8;
            return r;

        case 1:
            buf16 = new short[size];
            r = read2DIm((void *)buf16, n);

            if (r <= 0)
            {
                delete [] buf16;
                return 0;
            }

            for (i = 0; i < size; i++)
            {
                buf[i] = float(buf16[i]);
            }

            delete [] buf16;
            return r;

        case 2:
            return read2DIm((void *)buf, n);

        case 5:
            bufu8 = new unsigned char[size];
            r = read2DIm((void *)bufu8, n);

            if (r <= 0)
            {
                delete [] bufu8;
                return 0;
            }

            for (i = 0; i < size; i++)
            {
                buf[i] = float(bufu8[i]);
            }

            delete [] bufu8;
            return r;

        case 6:
            bufu16 = new unsigned short[size];
            r = read2DIm((void *)bufu16, n);

            if (r <= 0)
            {
                delete [] bufu16;
                return 0;
            }

            for (i = 0; i < size; i++)
            {
                buf[i] = float(bufu16[i]);
            }

            delete [] bufu16;
            return r;
    }

    return 0;
}
