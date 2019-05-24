#pragma once
#ifndef _F3D_FSCORE_H_
#define _F3D_FSCORE_H_

#if defined FSCORE_EXPORTS
#define FSCORE_EXPORT __declspec(dllexport)
#else
#pragma comment(lib, "FSCore.lib")
#define FSCORE_EXPORT __declspec(dllimport)
#endif

namespace f3d {

///-------------------------------------------------------------------------------------------------
/// <summary> A vector 3. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///-------------------------------------------------------------------------------------------------
struct Vector3
{
    float x;
    float y;
    float z;
};

///-------------------------------------------------------------------------------------------------
/// <summary> A quaternion. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///-------------------------------------------------------------------------------------------------
struct Quaternion
{
    float x;
    float y;
    float z;
    float w;
};

///-------------------------------------------------------------------------------------------------
/// <summary> A matrix 4.
///         是竖着记录到数组中的.
///         | m0  m4  m8  m12 |
///         | m1  m5  m9  m13 |
///         | m2  m6  m10 m14 |
///         | m3  m7  m11 m15 |</summary>
///
/// <remarks> Dx, 2018/8/8. </remarks>
///-------------------------------------------------------------------------------------------------
struct Matrix4
{
    float m[16];
};

///-------------------------------------------------------------------------------------------------
/// <summary>
/// 输入ModelView矩阵(或view矩阵)和Projection矩阵，同时定义了屏幕距离和屏幕的高度之后返回的计算结果.
/// </summary>
///
/// <remarks> Dx, 2018/8/15. </remarks>
///-------------------------------------------------------------------------------------------------
struct FrustumData
{
    //左眼相机View矩阵
    f3d::Matrix4 matViewL;
    //右眼相机View矩阵
    f3d::Matrix4 matViewR;

    //左眼Projection矩阵
    f3d::Matrix4 matProjectionL;
    //右眼Projection矩阵
    f3d::Matrix4 matProjectionR;

    //笔尖的坐标，分别在设置上面相机的ModelView之后应该能够正确渲染。
    //如左眼图像画笔首先使用上面的View矩阵设置GL_MODELVIEW：
    // glMatrixMode(GL_MODELVIEW);
    // glLoadMatrixf(fd.matViewL.m);
    // 使用这个坐标来画线即可
    f3d::Vector3 penPosition;
    //笔尖的方向向量
    f3d::Vector3 penDirection;
};
} // namespace f3d

///-------------------------------------------------------------------------------------------------
/// <summary> 初始化. </summary>
///
/// <remarks> Xian Dai, 2017/5/7. </remarks>
///
/// <param name="isStartServer"> (Optional)
///                              默认在服务未启动的时候启动服务,
///                              通常应该设置为true. </param>
///
/// <returns> 是否初始化成功的状态,0表示成功,非0为失败. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmInit(bool isStartServer = true);

///-------------------------------------------------------------------------------------------------
/// <summary> 关闭系统. </summary>
///
/// <remarks> Xian Dai, 2017/5/7. </remarks>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT void __stdcall fmClose();

///-------------------------------------------------------------------------------------------------
/// <summary> 得到眼镜状态. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 返回非零表示当前系统有检测到眼镜. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetGlassStatus();

///-------------------------------------------------------------------------------------------------
/// <summary> 得到眼镜坐标. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 返回眼镜的坐标. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT f3d::Vector3 __stdcall fmGetGlassPosition();

///-------------------------------------------------------------------------------------------------
/// <summary> 眼镜旋转.z轴向前 </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 眼镜旋转的四元数. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT f3d::Quaternion __stdcall fmGetGlassRotation();

///-------------------------------------------------------------------------------------------------
/// <summary> 笔的检测状态. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 返回非零表示当前系统有检测到笔. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetPenStatus();

///-------------------------------------------------------------------------------------------------
/// <summary> 笔坐标，它是笔尖的坐标. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 笔尖坐标. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT f3d::Vector3 __stdcall fmGetPenPosition();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// 笔方向向量(笔实际上只有两点，所以在光学上无法得出三轴方向，所以这里是方向不是旋转)，
/// 在3D系统中可以自己结合下面的滚转角生成一个四元数旋转。
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 笔的方向向量. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT f3d::Vector3 __stdcall fmGetPenDirection();

///-------------------------------------------------------------------------------------------------
/// <summary> 笔的滚转角，向右手旋转为正方向. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 笔的滚转角. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT float __stdcall fmGetPenRoll();

///-------------------------------------------------------------------------------------------------
/// <summary> 得到笔的当前按键值状态标志,0x01中键,0x02左键,0x04右键. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 得到笔的按键状态. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetPenKey();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// 整个一体机机身和桌面的倾斜角，当一体机机身完全垂直的时候它为0度.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 机身的倾斜角. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT float __stdcall fmGetSlantAngle();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// 设置笔震动，调用此函数会让笔震动一下,目前只有mode =1的模式.连续调用这个函数可以让笔连续震动.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <param name="mode"> (Optional) The mode. </param>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT void __stdcall fmSetPenShake(int mode = 1);

///-------------------------------------------------------------------------------------------------
/// <summary>
/// 标记自己是活动用户,每5秒内需要调用一次，如果超过10秒没有调用这个函数，那么后台检测系统会停止检测。需要在
/// 一个定时器里定时调用这个函数。
/// 这是因为当操作系统中没有运行一个活动的VR程序的时候，后台检测系统会关闭一些工作以减少开销,并且会关闭红外灯.
/// 当有VR程序标记自己是活动用户时，会马上打开红外灯并且启动检测程序
/// PS:可以观察设备屏幕两侧红外灯是否亮起，知道检测程序是否开始工作。
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT void __stdcall fmSetActiveUser();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// 设置屏幕VR模式的flag，0表示屏幕是非vr的正常显示模式，1表示是VR模式的LR格式画面显示。
/// 这个函数用以通知屏幕切换显示模式.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <param name="flag"> The flag. </param>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT void __stdcall fmSetflagVRMode(int flag);

///-------------------------------------------------------------------------------------------------
/// <summary>
/// 设置一体机以外的其他屏幕VR模式的flag，0表示屏幕是非vr的正常显示模式，1表示是VR模式的LR格式画面显示。
/// 这个函数用以通知屏幕切换显示模式.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <param name="flag"> The flag. </param>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT void __stdcall fmSetflagVRModeOther(int flag);

///-------------------------------------------------------------------------------------------------
/// <summary>
/// 设置双屏的显示模式，目前flag=1表示为扩展模式，flag=2为复制模式，flag=3为恢复上一次操作前的状态.
/// </summary>
///
/// <remarks> Xian Dai, 2018/3/26. </remarks>
///
/// <param name="flag"> The flag. </param>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT void __stdcall fmSetflagDualScreenMode(int flag);

///-------------------------------------------------------------------------------------------------
/// <summary>
/// 得到当前的双屏的显示模式，目前flag=1表示为扩展模式，flag=2为复制模式，flag=3为恢复上一次操作前的状态.
/// </summary>
///
/// <remarks> Xian Dai, 2018/3/26. </remarks>
///
/// <param name="flag"> The flag. </param>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetCurDualScreenStatus();

///-------------------------------------------------------------------------------------------------
/// <summary> 一体机检测程序是否在睡眠状态,0为正常检查,大于0为睡眠状态. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> The is sleep. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetIsSleep();

///-------------------------------------------------------------------------------------------------
/// <summary> 一体机检测程序的工作状态:0表示已经关闭; 1表示正在工作; 2表示正在低开销休眠. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 当前的工作状态标记. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetWorkStatus();

///-------------------------------------------------------------------------------------------------
/// <summary> 当前一体机检测程序的工作帧率. </summary>
///
/// <remarks>  Xian Dai, 2018/1/23. </remarks>
///
/// <returns> The FPS. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT float __stdcall fmGetFps();

///-------------------------------------------------------------------------------------------------
/// <summary> 获取摄像头硬件错误标志. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 摄像头硬件错误标志 . </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetCameraDevErrorCode();

///-------------------------------------------------------------------------------------------------
/// <summary> 获取笔硬件错误标志. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 笔硬件错误标志. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetPenDevErrorCode();

///-------------------------------------------------------------------------------------------------
/// <summary> 获取主控板硬件错误标志. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 主控板硬件错误标志. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetMCDevErrorCode();

///-------------------------------------------------------------------------------------------------
/// <summary> 得到软件是否发生了错误的标志. </summary>
///
/// <remarks> Dx, 2018/10/30. </remarks>
///
/// <returns> 处理软件自己发生了错误的标志. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetProcErrorCode();

///-------------------------------------------------------------------------------------------------
/// <summary> 获取主控板硬件id号. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 主控板硬件id号. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetMCDevID();

///-------------------------------------------------------------------------------------------------
/// <summary> 得到当前视锥的左眼和右眼两个投影矩阵. </summary>
///
/// <remarks> Dx, 2018/8/8. </remarks>
///
/// <param name="matL">          [out] 左眼投影矩阵. </param>
/// <param name="matR">          [out] 右眼投影矩阵. </param>
/// <param name="disNear">       近裁剪面. </param>
/// <param name="disFar">        远裁剪面. </param>
/// <param name="pupilDistance"> (Optional)
///                              两眼瞳距(现实空间中的瞳距)，默认6.6cm. </param>
/// <param name="aspectRatio">   (Optional)
///                              屏幕纵横比，默认是16比9. </param>
///
/// <returns> Error code. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetFrustumLR(f3d::Matrix4* matL, f3d::Matrix4* matR, float disNear, float disFar, float pupilDistance = 0.066, float aspectRatio = 16 / 9.0f);
extern "C" FSCORE_EXPORT int __stdcall fmGetFrustumLR2(f3d::Matrix4* matL, f3d::Matrix4* matR, float disNear, float disFar, float pupilDistance = 0.066, float aspectRatio = 16 / 9.0f);

///-------------------------------------------------------------------------------------------------
/// <summary>
/// 修改渲染使用的一些矩阵参数.这个函数只支持左手系的一种特定情形和右手系的一种特定情形.
/// </summary>
///
/// <remarks> Dx, 2018/8/15. </remarks>
///
/// <param name="frustumData">    [out]输出结果. </param>
/// <param name="matView">        [in]原来的视图矩阵. </param>
/// <param name="matProjection">  [in]原来的投影矩阵. </param>
/// <param name="screenDistance"> 相机到假想屏幕距离（相机空间）. </param>
/// <param name="screenHeight">   假想屏幕的高度（相机空间）. </param>
/// <param name="pupilDistance">  两眼瞳距(现实空间中的瞳距)，默认6.6cm. </param>
/// <param name="isLeftHanded">   是否是左手坐标系. </param>
///
/// <returns> Error Code. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmModifyFrustum(f3d::FrustumData* frustumData, f3d::Matrix4* matView, f3d::Matrix4* matProjection,
                                                       float screenDistance, float screenHeight, float pupilDistance, bool isLeftHanded);

extern "C" FSCORE_EXPORT int __stdcall fmModifyFrustumDebug2(f3d::FrustumData* frustumData, f3d::Matrix4* matView, f3d::Matrix4* matProjection,
                                                             float screenDistance, float screenHeight, float pupilDistance, bool isLeftHanded,
                                                             int kProjX, int kProjY, int kProjZ,
                                                             int kPenX, int kPenY, int kPenZ);

#endif