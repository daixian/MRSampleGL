using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class Test : MonoBehaviour {

    Matrix4x4 viewMatrix;
    Matrix4x4 projectionMatrix;

    public Vector3 glassP =new Vector3(0.0f, 0.0f, -0.4f);
    public Vector3 PenP = new Vector3(0.1f, 0.1f, -0.1f);
    public Vector3 PenD = new Vector3(0.0f, 0.0f, -1.0f);

    // Use this for initialization
    void Start()
    {
        viewMatrix = Camera.main.worldToCameraMatrix;

        Debug.Log("viewMatrix:\r\n" + viewMatrix);
        projectionMatrix = Camera.main.projectionMatrix;
        Debug.Log("projectionMatrix:\r\n" + projectionMatrix);

        Vector4 res = viewMatrix * new Vector4(0, 0, 0, 1);



    }

    FrustumData frustumData;

    // Update is called once per frame
    void Update () {

        FCoreDll.f3drm_modifyFrustumDebug(ref frustumData, ref viewMatrix, ref projectionMatrix, -10, 3, 0.066f, false,
        glassP, PenP, PenD);

        Camera.main.worldToCameraMatrix = frustumData.matViewL;
        Camera.main.projectionMatrix  = frustumData.matProjectionL;

        //Debug.Log("frustumData.matViewL:\r\n" + frustumData.matViewL);
    }
}
