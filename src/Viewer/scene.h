
#ifndef __SCENE_H__
#define __SCENE_H__

#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usdImaging/usdImagingGL/engine.h>
#include <pxr/base/gf/camera.h>
#include <GL/gl.h>


class Scene
{
public:
    Scene();
    ~Scene();
    // void prepare(float seconds);
    void draw(int width, int height);
    // void click();
    // void cursor(float x, float y);
    // void set_camera()

private:
    pxr::UsdStageRefPtr mStage;
    pxr::SdfPathVector mExcludePaths;
    pxr::UsdImagingGLEngine mRenderer;
    pxr::UsdImagingGLRenderParams mParams;

   
    pxr::GfCamera mCamera;
    pxr::SdfPath mCurrent;
    pxr::UsdPrim mRoot;
    int mWidth;
    int mHeight;
};




#endif