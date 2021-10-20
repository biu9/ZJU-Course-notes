/*******************************************************************
 *       Filename:  CTFAlgo.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/07/2020 05:31:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruan Huabin
 *          Email:  ruanhuabin@tsinghua.edu.cn
 *        Company:  Dep. of CS, Tsinghua Unversity
 *
 *******************************************************************/
#ifndef  CTFALGO_H
#define  CTFALGO_H
#include "CTFBase.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

class CTFAlgo:public CTFBase
{
    public:
        void doCTF(map<string, string> &inputPara, map<string, string> &outputPara);
        ~CTFAlgo();

};


#endif