#ifndef SCENECAMERA_H
#define SCENECAMERA_H

#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <pxr/base/gf/camera.h>



class SceneCamera
{
public:
    SceneCamera();
    ~SceneCamera();
    //static pxr::UsdGeomCamera CreateDefaultCamera(pxr::UsdStageRefPtr stage);

    void ZoomCamera(const float &delta);
    void RotateCamera(const pxr::GfVec2f &delta);
    void PanCamera(const pxr::GfVec2f &delta);

    void SetCameraPrim(pxr::UsdStageRefPtr stage, pxr::SdfPath path);
    pxr::GfCamera* GetGfCamera();


private:
    bool cameraTransformDirty;
    pxr::GfCamera GfCamera;
    pxr::UsdGeomCamera GeomCameraPrim;
    pxr::GfMatrix4d XformCamera;




};
#endif // SCENECAMERA_H

