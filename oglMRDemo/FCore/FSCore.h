#pragma once
#ifndef _F3D_FSCORE_H_
#    define _F3D_FSCORE_H_

#    if defined FSCORE_EXPORTS
#        define FSCORE_EXPORT __declspec(dllexport)
#    else
#        pragma comment(lib, "FSCore.lib")
#        define FSCORE_EXPORT __declspec(dllimport)
#    endif

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
///         From 0 to 15 is the index in memory.
///         从0到15是内存中的顺序.
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
/// This structure contains all the calculation data of
/// the VR projection matrix. It is our own projection
/// matrix calculation method. It can also design the
/// projection matrix according to the position of the
/// glasses and the pen(stylus). Its members have input to the
/// ModelView matrix (or view matrix) and the
/// Projection matrix, and define the calculation
/// results returned after the screen distance and the
/// height of the screen.
/// 这个结构体包含了所有的VR投影矩阵的计算数据，是我们自己的一种投影矩阵计算方法，也可以根据眼镜和笔的位置自己设计投影矩阵。
/// 它的成员有输入ModelView矩阵(或view矩阵)和Projection矩阵，同时定义了屏幕距离和屏幕的高度之后返回的计算结果.
/// </summary>
///
/// <remarks>
/// The coordinates of the nib of the pen(stylus) should be
/// correctly rendered after setting the ModelView of
/// the camera above. For example, the left eye image
/// brush first sets GL_MODELVIEW using the View
/// matrix above:
///      glMatrixMode(GL_MODELVIEW);
///      glLoadMatrixf(fd.matViewL.m);
/// Then call the calculation API and use this penPosition
/// and penDirection to draw the line.
/// 分别在设置上面相机的ModelView之后应该能够正确渲染。
/// 如左眼图像画笔首先使用上面的View矩阵设置GL_MODELVIEW：
///      glMatrixMode(GL_MODELVIEW);
///      glLoadMatrixf(fd.matViewL.m);
/// 然后调用计算API之后使用这个penPosition和penDirection来画线即可.
///
/// Dx, 2018/8/15. </remarks>
///-------------------------------------------------------------------------------------------------
struct FrustumData
{
    // Left eye camera View matrix.
    // 左眼相机View矩阵.
    f3d::Matrix4 matViewL;

    // Right eye camera View matrix.
    // 右眼相机View矩阵.
    f3d::Matrix4 matViewR;

    // Left eye Projection matrix.
    // 左眼Projection矩阵.
    f3d::Matrix4 matProjectionL;

    // Right eye Projection matrix.
    // 右眼Projection矩阵.
    f3d::Matrix4 matProjectionR;

    // Nib of the pen(stylus) coordinates
    // 笔尖的坐标
    f3d::Vector3 penPosition;

    // Direction vector of the pen(stylus)
    // 笔的方向向量
    f3d::Vector3 penDirection;
};
} // namespace f3d
///-------------------------------------------------------------------------------------------------
/// <summary>
/// Initialization, the program needs to be called once
/// when it starts working.
/// 初始化,程序一开始工作的时候需要调用一次.
/// </summary>
///
/// <remarks> Xian Dai, 2017/5/7. </remarks>
///
/// <param name="isStartServer"> (Optional)By default,
///                              the service is started
///                              when the service is not
///                              started, and should
///                              normally be set to
///                              true.
///                              默认在服务未启动的时候启动服务,
///                              通常应该设置为true. </param>
///
/// <returns> Whether to initialize the successful state, 0 means success, non-zero is failure.
///           是否初始化成功的状态,0表示成功,非0为失败. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmInit(bool isStartServer = true);

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Shut down system.
/// 关闭系统.
/// </summary>
///
/// <remarks> Xian Dai, 2017/5/7. </remarks>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT void __stdcall fmClose();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Get the status of the glasses.
/// 得到眼镜状态.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> Return non-zero means that the system has detected glasses.
///           返回非零表示当前系统有检测到眼镜. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetGlassStatus();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Get glasses coordinates.
/// 得到眼镜坐标.
/// </summary>
///
/// <remarks>
/// The coordinate system is in meters, the center of
/// the display screen is the world origin, the x-axis
/// points to the right, the y-axis points to the top,
/// and the z-axis points to the inside of the screen.
/// 坐标系以米为单位,显示器屏幕中心为世界原点,x轴指向右,y轴指向上,z轴指向屏幕内部.
/// Xian Dai, 2018/1/23.
/// </remarks>
///
/// <returns>
/// Return the coordinates of the glasses.
/// 返回眼镜的坐标.
/// </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT f3d::Vector3 __stdcall fmGetGlassPosition();

///-------------------------------------------------------------------------------------------------
/// <summary> Glasses rotation.
///           眼镜旋转.z轴向前 </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 眼镜旋转的四元数. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT f3d::Quaternion __stdcall fmGetGlassRotation();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Pen detection status. 笔的检测状态.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns>
/// Return non-zero means the current system has
/// detected the pen(stylus). 返回非零表示当前系统有检测到笔.
/// </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetPenStatus();

///-------------------------------------------------------------------------------------------------
/// <summary> Pen(stylus) coordinates, which is the coordinates of the pen nib.
///           笔坐标，它是笔尖的坐标. </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 笔尖坐标. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT f3d::Vector3 __stdcall fmGetPenPosition();
///-------------------------------------------------------------------------------------------------
/// <summary>
/// Pen direction vector.The pen(stylus) actually has only two
/// points, so it is optically impossible to derive the
/// three-axis direction, so here the direction is not
/// rotation. In the 3D system, you can combine the
/// following roll angle to generate a quaternion
/// rotation.
/// 笔方向向量(笔实际上只有两点，所以在光学上无法得出三轴方向，所以这里是方向不是旋转)，
/// 在3D系统中可以自己结合下面的滚转角生成一个四元数旋转。.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> Pen direction vector.
///           笔的方向向量. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT f3d::Vector3 __stdcall fmGetPenDirection();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// The roll angle of the pen(stylus), clockwise.
/// 笔的滚转角，向右手旋转为正方向.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns>
/// The roll angle of the pen(stylus).
/// 笔的滚转角.
/// </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT float __stdcall fmGetPenRoll();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Get the current button value status flag of the
/// pen(stylus), 0x01 middle key, 0x02 left key, 0x04
/// right key.
/// 得到笔的当前按键值状态标志,0x01中键,0x02左键,0x04右键.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns>
/// the current button value status flag of the
/// pen(stylus).
/// 得到笔的按键状态.
/// </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetPenKey();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// The tilt angle of the whole body and the desktop, when the unit body is completely vertical, it is 0 degrees.
/// 整个一体机机身和桌面的倾斜角，当一体机机身完全垂直的时候它为0度.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> angle.
///           机身的倾斜角. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT float __stdcall fmGetSlantAngle();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Set the pen vibration. Calling this function will
/// make the pen vibrate. At present, there is only
/// mode=1. Continuously calling this function can make
/// the pen continuously vibrate.
/// 设置笔震动，调用此函数会让笔震动一下,
/// 目前只有mode =1的模式.连续调用这个函数可以让笔连续震动.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <param name="mode"> (Optional) The mode. </param>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT void __stdcall fmSetPenShake(int mode = 1);

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Mark yourself as an active user and call it once
/// every 5 seconds. If this function is not called for
/// more than 10 seconds, the background detection
/// system will stop detecting. This function needs to
/// be called periodically in a timer. This is because
/// when an active VR program is not running in the
/// operating system, the background detection system
/// will close some work to reduce overhead and will
/// turn off the infrared light. When a VR program
/// marks itself as an active user, it will immediately
/// turn on the infrared light and start the test. PS:
/// You can observe whether the infrared light on both
/// sides of the device screen is on, and know if the
/// test program starts working.
/// 标记自己是活动用户,每5秒内需要调用一次，如果超过10秒没有调用这个函数，那么后台检测系统会停止检测。需要在
/// 一个定时器里定时调用这个函数。
/// 这是因为当操作系统中没有运行一个活动的VR程序的时候，后台检测系统会关闭一些工作以减少开销,
/// 并且会关闭红外灯. 当有VR程序标记自己是活动用户时，会马上打开红外灯并且启动检测程序
/// PS:可以观察设备屏幕两侧红外灯是否亮起，知道检测程序是否开始工作.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT void __stdcall fmSetActiveUser();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Set the flag of the screen VR mode, 0 means that
/// the screen is a normal display mode other than vr,
/// and 1 means that it is an LR format screen display
/// of the VR mode. This function is used to notify the
/// screen to switch the display mode.
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
/// Set the flag of the screen VR mode other than the
/// GC100, 0 means that the screen is a normal
/// display mode other than vr, and 1 means that it is
/// an LR format screen display of the VR mode. This
/// function is used to notify other screens to switch
/// the display mode.
/// 设置一体机以外的其他屏幕VR模式的flag，0表示屏幕是非vr的正常显示模式，1表示是VR模式的LR格式画面显示。
/// 这个函数用以通知其他屏幕切换显示模式.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <param name="flag"> The flag. </param>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT void __stdcall fmSetflagVRModeOther(int flag);

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Set the display mode of the dual screen. Currently,
/// flag=1 indicates the extended mode, flag=2 is the
/// copy mode, and flag=3 is the state before the
/// previous operation.
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
/// The current dual-screen display mode is obtained.
/// Currently, flag=1 indicates an extended mode,
/// flag=2 is a copy mode, and flag=3 is a state before
/// the previous operation is restored.
/// 得到当前的双屏的显示模式，目前flag=1表示为扩展模式，flag=2为复制模式，flag=3为恢复上一次操作前的状态.
/// </summary>
///
/// <remarks> Xian Dai, 2018/3/26. </remarks>
///
/// <returns> The flag. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetCurDualScreenStatus();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// The service program is in the sleep state,
/// 0 is the normal check, and greater than 0 is the
/// sleep state.
/// 一体机检测程序是否在睡眠状态,0为正常检查,大于0为睡眠状态.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> The is sleep. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetIsSleep();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// The working status of the service program:
/// 0 means it has been turned off; 1 means it is
/// working; 2 means it is sleeping at low overhead.
/// 一体机检测程序的工作状态:0表示已经关闭; 1表示正在工作; 2表示正在低开销休眠.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> 当前的工作状态标记. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetWorkStatus();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Current frame rate of the current service program.
/// 当前一体机检测程序的工作帧率.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns> The FPS. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT float __stdcall fmGetFps();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Get camera hardware error flag.
/// 获取摄像头硬件错误标志.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns>
/// camera hardware error flag.
/// 摄像头硬件错误标志 .
/// </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetCameraDevErrorCode();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Get pen(stylus) hardware error flag.
/// 获取笔硬件错误标志.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns>
/// pen(stylus) hardware error flag.
/// 笔硬件错误标志.
/// </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetPenDevErrorCode();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Get the main control board hardware error flag.
/// 获取主控板硬件错误标志.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns>
/// the main control board hardware error
/// flag.主控板硬件错误标志.
/// </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetMCDevErrorCode();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Get the software error flag.
/// 得到软件是否发生了错误的标志.
/// </summary>
///
/// <remarks> Dx, 2018/10/30. </remarks>
///
/// <returns>
/// the software error flag.
/// 处理软件自己发生了错误的标志.
/// </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetProcErrorCode();

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Get the hardware ID of the main control board.
/// 获取主控板硬件id号.
/// </summary>
///
/// <remarks> Xian Dai, 2018/1/23. </remarks>
///
/// <returns>
/// the hardware ID.
/// 主控板硬件id号.
/// </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetMCDevID();

///-------------------------------------------------------------------------------------------------
/// <summary> Get the two projection matrices of the left and right eyes.
///           得到当前视锥的左眼和右眼两个投影矩阵. </summary>
///
/// <remarks> Dx, 2018/8/8. </remarks>
///
/// <param name="matL">          [out]Left eye projection matrix. 左眼投影矩阵. </param>
/// <param name="matR">          [out]Right eye projection matrix. 右眼投影矩阵. </param>
/// <param name="disNear">       Near clipping distance. 近裁剪面距离. </param>
/// <param name="disFar">        Far clipping distance. 远裁剪面距离. </param>
/// <param name="pupilDistance"> (Optional)
///                              Eye distance. 两眼瞳距(现实空间中的瞳距)，默认6.6cm. </param>
/// <param name="aspectRatio">   (Optional)
///                              Screen aspect ratio. 屏幕纵横比，默认是16比9. </param>
///
/// <returns> Error code. </returns>
///-------------------------------------------------------------------------------------------------
extern "C" FSCORE_EXPORT int __stdcall fmGetFrustumLR(f3d::Matrix4* matL, f3d::Matrix4* matR, float disNear, float disFar, float pupilDistance = 0.066, float aspectRatio = 16 / 9.0f);
extern "C" FSCORE_EXPORT int __stdcall fmGetFrustumLR2(f3d::Matrix4* matL, f3d::Matrix4* matR, float disNear, float disFar, float pupilDistance = 0.066, float aspectRatio = 16 / 9.0f);

///-------------------------------------------------------------------------------------------------
/// <summary>
/// Modify some of the matrix parameters used in rendering.
/// This function only supports a specific case of the left-handed system and
/// a specific case of the right-handed system.
/// 修改渲染使用的一些矩阵参数.这个函数只支持左手系的一种特定情形和右手系的一种特定情形.
/// </summary>
///
/// <remarks> Dx, 2018/8/15. </remarks>
///
/// <param name="frustumData">    [out]Output result. 输出结果. </param>
/// <param name="matView">        [in]Original view matrix. 原来的视图矩阵. </param>
/// <param name="matProjection">  [in]Original projection matrix. 原来的投影矩阵. </param>
/// <param name="screenDistance"> Camera to imaginary screen distance. 相机到假想屏幕距离（相机空间）. </param>
/// <param name="screenHeight">   Hypothetical screen height. 假想屏幕的高度（相机空间）. </param>
/// <param name="pupilDistance">  Eye distance. 两眼瞳距(现实空间中的瞳距)，默认6.6cm. </param>
/// <param name="isLeftHanded">   Whether it is a left-hand coordinate system. 是否是左手坐标系. </param>
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