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