
#include <pxr/base/gf/camera.h>
#include "sceneCamera.h"
#include <iostream>
#include <pxr/base/gf/frustum.h>

SceneCamera::SceneCamera()
    : GfCamera(pxr::GfCamera()),
      XformCamera(GfCamera.GetTransform())
{
    // pxr::UsdGeomXformCommonAPI xformAPI(GfCamera);
    // xformAPI.SetTranslate(pxr::GfVec3f(4.0f, 5.0f, 20.0f));
    pxr::GfMatrix4d start_offset = pxr::GfMatrix4d();
    start_offset.SetTranslate(pxr::GfVec3f(3.0f, 4.0f, 20.0f));
    GfCamera.SetTransform(start_offset);
}

SceneCamera::~SceneCamera()
{

}
pxr::GfCamera* SceneCamera::GetGfCamera()
{
    return &GfCamera;
}


void SceneCamera::PanCamera(const pxr::GfVec2f &delta)
{
    pxr::GfMatrix4d start_pos = GeomCameraPrim.GetCamera(pxr::UsdTimeCode::Default()).GetTransform() ;   
    pxr::GfMatrix4d offset = pxr::GfMatrix4d();
    offset.SetTranslate(pxr::GfVec3f(delta[0]*-0.1, delta[1]*-0.1, 0.0f));
    std::cout << "Transform before :" << GfCamera.GetTransform() << std::endl;
    std::cout << "Frustum before :" << GfCamera.GetFrustum() << std::endl;
    GfCamera.SetTransform(start_pos * offset);
    std::cout << "Transform after :" << GfCamera.GetTransform() << std::endl;
    std::cout << "Frustum after :" << GfCamera.GetFrustum() << std::endl;
    GeomCameraPrim.SetFromCamera(GfCamera, pxr::UsdTimeCode::Default());
}

void SceneCamera::ZoomCamera(const float &delta)
{
    pxr::GfMatrix4d start_pos = GeomCameraPrim.GetCamera(pxr::UsdTimeCode::Default()).GetTransform() ;   
    pxr::GfMatrix4d offset = pxr::GfMatrix4d();
    offset.SetTranslate(pxr::GfVec3f(0.0f , 0.0f, delta*-1.0f));
    std::cout << "Transform before :" << GfCamera.GetTransform() << std::endl;
    std::cout << "Frustum before :" << GfCamera.GetFrustum() << std::endl;
    GfCamera.SetTransform(start_pos * offset);
    std::cout << "Transform after :" << GfCamera.GetTransform() << std::endl;
    std::cout << "Frustum after :" << GfCamera.GetFrustum() << std::endl;
    GeomCameraPrim.SetFromCamera(GfCamera, pxr::UsdTimeCode::Default()); 

}

// pxr::UsdGeomCamera SceneCamera::CreateDefaultCamera(pxr::UsdStageRefPtr stage)
// {
//     pxr::UsdGeomCamera camera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath(defaultCameraPath));
//     camera.CreateProjectionAttr();
//     pxr::UsdGeomXformCommonAPI xformAPI(camera);
//     xformAPI.SetTranslate(pxr::GfVec3f(4.0f, 5.0f, 20.0f)); // Example translation
//     return camera;
// }

void SceneCamera::SetCameraPrim(pxr::UsdStageRefPtr stage, pxr::SdfPath path)
{
    GeomCameraPrim = pxr::UsdGeomCamera::Get(stage, path);
    GfCamera= GeomCameraPrim.GetCamera(pxr::UsdTimeCode::Default());
    XformCamera = GfCamera.GetTransform();
}