#pragma once
#include <string>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

std::string defaultCameraPath = "/viewer/camera1";

class Camera
{
public:
    Camera(pxr::UsdStageRefPtr mStage, pxr::SdfPath cameraPath);
    Camera(pxr::UsdStageRefPtr mStage, pxr::UsdGeomCamera camera);

    ~Camera();
    static pxr::SdfPath CreateDefaultCamera(std::string cameraPath);

    void ZoomCamera(const float &delta);
    void RotateCamera(const pxr::GfVec2f &delta);
    void PanCamera(const pxr::GfVec2f &delta);

private:
    pxr::UsdGeomCamera GeomCamera;
    pxr::GfCamera GfCamera;

};

Camera:Camera(pxr::UsdStageRefPtr mStage, pxr::SdfPath cameraPath)
{


}

static pxr::SdfPath Camera::CreateDefaultCamera(pxr::UsdStageRefPtr stage, pxr::SdfPath cameraPath)
{
    pxr::UsdGeomCamera camera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath(defaultCameraPath));
    camera.CreateProjectionAttr();
    pxr::UsdGeomXformCommonAPI xformAPI(camera);
    xformAPI.SetTranslate(pxr::GfVec3f(4.0f, 5.0f, 20.0f)); // Example translation
    return pxr::SdfPath(defaultCameraPath)
    //mCamera = camera.GetCamera(pxr::UsdTimeCode::Default());
}