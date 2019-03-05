using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class Test : MonoBehaviour
{
    public Texture2D tex;
    public GameObject m_obj;

    private Color32[] texDataColor;
    private GCHandle pixelHandle;
    private IntPtr imgDataPtr;

#if UNITY_EDITOR
    [DllImport("OpenCV_Bridge_Windows_Dll")]
    private static extern float Foopluginmethod();
    [DllImport("OpenCV_Bridge_Windows_Dll")]
    private static extern float GetRawImage(IntPtr texData, int width, int height);
#elif UNITY_ANDROID
    [DllImport("OpenCV_Bridge")]
    private static extern float Foopluginmethod();
    [DllImport("OpenCV_Bridge")]
    private static extern float GetRawImage(IntPtr texData, int width, int height);
#endif

    private void TextureToCVMat(Texture2D texData)
    {
        texDataColor = tex.GetPixels32();
        Debug.Log(texDataColor.Length);
        Debug.Log(texDataColor[0].a + ", " + texDataColor[0].r + ", " + texDataColor[0].g + ", " + texDataColor[0].b);

        pixelHandle = GCHandle.Alloc(texDataColor, GCHandleType.Pinned);
        imgDataPtr = pixelHandle.AddrOfPinnedObject();
        GetRawImage(imgDataPtr, tex.width, tex.height);

        var newTex = new Texture2D(tex.width, tex.height, TextureFormat.RGBA32, false);
        Debug.Log(texDataColor[0].a + ", " + texDataColor[0].r + ", " + texDataColor[0].g + ", " + texDataColor[0].b);

        newTex.SetPixels32(texDataColor);
        newTex.Apply();

        m_obj.GetComponent<MeshRenderer>().material.mainTexture = newTex;
    }

    private void Start()
    {
        TextureToCVMat(tex);
    }

    private void OnGUI()
    {
        GUI.Label(new Rect(15, 125, 450, 100), "Foopluginmethod: " + Foopluginmethod());
    }

    private void OnApplicationQuit()
    {
        pixelHandle.Free();
    }


}
