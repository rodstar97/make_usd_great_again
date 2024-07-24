
#ifndef __SCENE_H__
#define __SCENE_H__

#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usdImaging/usdImagingGL/engine.h>
#include <pxr/base/gf/camera.h>
#include <GL/gl.h>
#include <QMatrix4x4>


class Scene
{
public:
    Scene();
    ~Scene();
    void draw(int width, int height);
    void set_camera(QMatrix4x4 cam_matrix);
    void create_view_camera(pxr::UsdStageRefPtr stage);

    void ZoomCamera(float delta);
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