using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using UnityEngine;

public class FCoreDll
{
    [DllImport("FSCore")]
    public static extern int f3drm_modifyFrustumDebug(ref FrustumData frustumData, ref Matrix4x4 matView, ref Matrix4x4 matProjection,
float screenDistance, float screenHeight, float pupilDistance, bool isLeftHanded, Vector3 glassPosition, Vector3 penP, Vector3 penD);
}

public struct FrustumData
{
    //左眼相机View矩阵
    public Matrix4x4 matViewL;
    public   //右眼相机View矩阵
       Matrix4x4 matViewR;

    //左眼Projection矩阵
    public Matrix4x4 matProjectionL;
    //右眼Projection矩阵
    public Matrix4x4 matProjectionR;

    //笔尖的坐标，分别在设置上面相机的ModelView之后应该能够正确渲染。
    //如左眼图像画笔首先使用上面的View矩阵设置GL_MODELVIEW：
    // glMatrixMode(GL_MODELVIEW); 
    // glLoadMatrixf(fd.matViewL.m);
    // 使用这个坐标来画线即可
    public Vector3 penPosition;
    //笔尖的方向向量
    public Vector3 penDirection;
};

