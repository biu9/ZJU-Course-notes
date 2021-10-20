/*******************************************************************
 *       Filename:  AlignmentBase.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07/07/2020 04:22:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruan Huabin
 *          Email:  ruanhuabin@tsinghua.edu.cn
 *        Company:  Dep. of CS, Tsinghua Unversity
 *
 *******************************************************************/

#ifndef  ALIGNMENTBASE_H
#define  ALIGNMENTBASE_H
#include <map>
#include <string>
using namespace std;
class AlignmentBase
{
    public:
        virtual void doAlignment(map<string, string> &inputPara, map<string, string> &outputPara) = 0;
        virtual ~AlignmentBase();

};

#endif