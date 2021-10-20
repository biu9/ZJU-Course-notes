//#pragma once
#include "stdio.h"
#include "util.h"

class Track
{
public:
    Track();
    Track(float marker3D_x_new,float marker3D_y_new,float marker3D_z_new);
    ~Track();

public:
    int getLength();
    float getMarker3D_x();
    float getMarker3D_y();
    float getMarker3D_z();
    float getMarker2D_x(int k);
    float getMarker2D_y(int k);
    int getMarker2D_n(int k);
    bool getMarker2D_avail(int k);
    bool getStatus();

    void setMarker3D(float marker3D_x_new,float marker3D_y_new,float marker3D_z_new);
    void setMarker2D(float marker2D_x_new,float marker2D_y_new,int n_now);
    void addPatch(float marker2D_x_now,float marker2D_y_now,int n_now);
    void changeStatus(bool status_new);
    void changeStatus2D(bool status_new,int n_now);
    void move_origin(float dx,float dy,bool flip_x,bool flip_y);

//    int deletePatch(int n_now);

private:
    int length;
    float marker3D_x,marker3D_y,marker3D_z;
    vector<float> marker2D_x,marker2D_y;
    vector<int> n;  // 存图像在原stack中的序号
    vector<bool> marker2D_avail; // 该特征点是否保留
    bool status;    // 该track是否保留
};