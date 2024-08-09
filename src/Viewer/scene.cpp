#include <cstdio>
#include <QDebug>
#include <iostream>

#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usd/references.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include "pxr/imaging/glf/simpleLightingContext.h"
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include <pxr/base/tf/token.h>
#include <pxr/base/vt/value.h>
#include <string>
#include "scene.h"
#include "sceneCamera.h"

const std::string defaultCameraPath = "/viewer/camera1";

Scene::Scene() :
    mWidth(0),
    mHeight(0),
    mStage(pxr::UsdStage::Open("/workspaces/make_usd_great_again/media/HelloWorld.usda")),
    mRoot(mStage->GetPseudoRoot()),
    mCamera(SceneCamera())
 {
    
    GLint major = 0;
    GLint minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    printf("OpenGL version is %i.%i\n", major, minor);
    
    pxr::GlfSimpleLight light;
    // light.SetPosition(pxr::GfVec4f(8.0, 10.0, 6.0, 1.0));
    // light.SetDiffuse(pxr::GfVec4f(2.0,2.0, 2.0, 1.0));
    light.SetIsDomeLight(true);
    pxr::GlfSimpleLightVector lights;
    lights.push_back(light);
    pxr::GlfSimpleMaterial material;
    pxr::GfVec4f ambient(0.1, 0.1, 0.1, 1.0);
    mRenderer.SetLightingState(lights, material, ambient);


    mParams.frame = 1.0;
    mParams.complexity = 1.1f;

    mParams.enableLighting = true;
    pxr::UsdGeomCamera camera = pxr::UsdGeomCamera::Define(mStage, pxr::SdfPath(defaultCameraPath));
    camera.CreateFocalLengthAttr(pxr::VtValue(50.0)); // Focal length
    camera.CreateFocusDistanceAttr(pxr::VtValue(5.0)); // Focus distance
    camera.CreateHorizontalApertureAttr(pxr::VtValue(20.955)); // Horizontal aperture
    camera.CreateVerticalApertureAttr(pxr::VtValue(15.2908)); // Vertical aperture
    camera.CreateHorizontalApertureOffsetAttr(pxr::VtValue(0.0)); // Horizontal aperture offset
    camera.CreateVerticalApertureOffsetAttr(pxr::VtValue(0.0)); // Vertical aperture offset
    camera.CreateClippingRangeAttr(pxr::VtValue(pxr::GfVec2f(0.1, 1000.0))); // Clipping range
    camera.CreateProjectionAttr(pxr::VtValue(pxr::UsdGeomTokens->perspective)); // 
    //std::cout  << camera << std::endl;
    pxr::UsdGeomXformCommonAPI xformAPI(camera);
    //xformAPI.SetTranslate(pxr::GfVec3f(4.0f, 5.0f, 20.0f)); // Example translation
    
    mCamera.SetCameraPrim(mStage, pxr::SdfPath(defaultCameraPath));

    auto* result = new std::string();
    mStage->GetRootLayer()->ExportToString(result);
    std::cout << *result << std::endl;
    delete result;
    result = nullptr;

}

void Scene::draw(int width, int height)

{
    mWidth = width;
    mHeight = height;
    //auto frustum = mCamera.GetGfCamera()->GetFrustum();
    auto gfc = pxr::UsdGeomCamera::Get(mStage, pxr::SdfPath(defaultCameraPath));
    auto frustum = gfc.GetCamera(pxr::UsdTimeCode::Default()).GetFrustum();
    // std::cout << "frustum" << std::endl;
    // std::cout << frustum  << std::endl;
    // std::cout << "frustum end" << std::endl;
    pxr::GfMatrix4d viewMat = frustum.ComputeViewMatrix();
    pxr::GfMatrix4d projMat = frustum.ComputeProjectionMatrix();

    const pxr::GfVec4d viewport(0, 0, width, height);
    mRenderer.SetRenderViewport(viewport);
    
    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);

    // float position[4] = { 0,10.5,2,0 };
    // glLightfv(GL_LIGHT0, GL_POSITION, position);
    // //mParams.showGuides = pxr:UsdIm
    //mRenderer.SetLightingStateFromOpenGL();
    mRenderer.SetCameraState(
            viewMat,
            projMat
            );
   
    // USD render.
    mRenderer.Render(mRoot, mParams);
    
    // Clear OpenGL errors. Because UsdImagingGL::TestIntersection prints them.
    while (glGetError() != GL_NO_ERROR) {
        printf("GL ERROR");
    }

}

SceneCamera Scene::GetSceneCamera()
{
    return mCamera;
}

pxr::UsdStageRefPtr Scene::GetStage()
{
    return mStage;
}
// void Scene::set_camera(QMatrix4x4 cam_matrix)
// {
//     //pxr::GfMatrix4d pre_pos = mCamera.GetTransform();
//     // auto frustum = mCamera.GetFrustum();
//     // auto view_matrix = frustum.ComputeViewMatrix();
//     auto new_matrix = pxr::GfMatrix4d(
//         static_cast<double>(cam_matrix(0, 0)), static_cast<double>(cam_matrix(0, 1)), static_cast<double>(cam_matrix(0, 2)), static_cast<double>(cam_matrix(0, 3)),
//         static_cast<double>(cam_matrix(1, 0)), static_cast<double>(cam_matrix(1, 1)), static_cast<double>(cam_matrix(1, 2)), static_cast<double>(cam_matrix(1, 3)),
//         static_cast<double>(cam_matrix(2, 0)), static_cast<double>(cam_matrix(2, 1)), static_cast<double>(cam_matrix(2, 2)), static_cast<double>(cam_matrix(2, 3)),
//         static_cast<double>(cam_matrix(3, 0)), static_cast<double>(cam_matrix(3, 1)), static_cast<double>(cam_matrix(3, 2)), static_cast<double>(cam_matrix(3, 3))
//     );
//     mCamera.SetTransform(new_matrix);//mCamera.GetTransform() *
//     // //auto new_matrix = pxr::GfMatrix4f(*cam_matrix.data());
//     // pxr::GfMatrix4d viewMat = new_matrix ;//view_matrix * 
//     // pxr::GfMatrix4d projMat = frustum.ComputeProjectionMatrix();
//     // mRenderer.SetCameraState(
//     //         viewMat,
//     //         projMat
//     //         );
//     auto SpherePrim = mStage->GetPrimAtPath(pxr::SdfPath("/hello/world"));
//     auto color_attr = SpherePrim.GetAttribute(pxr::TfToken{"primvars:displayColor"});
//     float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//     srand (static_cast <unsigned> (time(0)));

//     float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//     srand (static_cast <unsigned> (time(0)));

//     float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//     // color.Set(1.0,1.0,1.0);
//     pxr::VtArray<pxr::GfVec3f> color {{r, g, b}};
//     color_attr.Set(color);

//     qDebug() << "Camera Update";
    
// }

// void Scene::create_view_camera(pxr::UsdStageRefPtr stage)
// {
//     pxr::UsdGeomCamera camera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/tmp/persp1"));
//     camera.CreateProjectionAttr();
//     //camera.AddTranslateOp
//     pxr::UsdGeomXformCommonAPI xformAPI(camera);
//     xformAPI.SetTranslate(pxr::GfVec3f(4.0f, 5.0f, 20.0f)); // Example translation

//     mCamera = camera.GetCamera(pxr::UsdTimeCode::Default()) ;
// }
// // }

// void Scene::ZoomCamera(float delta) {
//     float zoomSpeed = 0.1f;
//     pxr::GfVec3f zoomTranslation(0.0f, 0.0f, delta * zoomSpeed);

//     // Apply the zoom to the camera transform
//     pxr::GfMatrix4d cameraTransform = mCamera.GetTransform();
//     cameraTransform.SetTranslate(cameraTransform.ExtractTranslation() + zoomTranslation);
//     cameraTransform.GetXformOp().Set(cameraTransform);
// }