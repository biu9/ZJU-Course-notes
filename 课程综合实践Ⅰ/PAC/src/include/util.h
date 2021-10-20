/*******************************************************************
 *       Filename:  util.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  06/16/2020 10:41:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ruan Huabin
 *          Email:  ruanhuabin@tsinghua.edu.cn
 *        Company:  Dep. of CS, Tsinghua Unversity
 *
 *******************************************************************/
#ifndef  UTIL_H
#define  UTIL_H

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;
void readParaFile(map<string, string> &paraMap, const char *fileName);
void getAllParas(map<string, string> paraMap);
#endif