/*******************************************************************
 *       Filename:  ReconstructionBase.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/07/2020 05:33:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruan Huabin
 *          Email:  ruanhuabin@tsinghua.edu.cn
 *        Company:  Dep. of CS, Tsinghua Unversity
 *
 *******************************************************************/


#ifndef  RECONSTRUCTIONBASE_H
#define  RECONSTRUCTIONBASE_H
#include <map>
#include <string>
using namespace std;
class ReconstructionBase
{
    public:
        virtual void doReconstruction(map<string, string> &inputPara, map<string, string> &outputPara) = 0;
        virtual ~ReconstructionBase();

};


#endif