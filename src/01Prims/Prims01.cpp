#include <iostream>
#include <string>

#include <pxr/base/vt/value.h>
#include <pxr/usd/sdf/attributeSpec.h>
#include <pxr/usd/sdf/path.h>
#include <pxr/usd/sdf/types.h>
#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usdImaging/usdImagingGL/engine.h>
#include <pxr/base/gf/camera.h>
#include "pxr/imaging/garch/glApi.h"


void as_usd()
{
    // auto stage = pxr::UsdStage::CreateInMemory();
    auto stage = pxr::UsdStage::Open("/workspaces/make_usd_great_again/media/HelloWorld.usda");

    pxr::UsdImagingGLEngine mRenderer;
    mRenderer.GetRendererDisplayName(mRenderer.GetCurrentRendererId());
    const pxr::GfVec4d viewport(0, 0, 1280, 720);
    mRenderer.SetRenderViewport(viewport);
    // auto prim = stage->DefinePrim(pxr::SdfPath {"/root"});
    // auto attribute = prim.CreateAttribute(
    //     pxr::TfToken {"some_name"},
    //     pxr::SdfValueTypeNames->Int,
    //     true
    // );

    // attribute.Set(8);

    // auto layer = stage->GetEditTarget().GetLayer();  // By default, this is `stage.GetRootLayer`
    // layer->SetTimeSample(attribute.GetPath(), 10.5, 9);

    auto* result = new std::string();
    stage->GetRootLayer()->ExportToString(result);
    std::cout << *result << std::endl;
    delete result;
    result = nullptr;
}

int main() {
    pxr::Open *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_elapsed.start();
    as_usd();

    return 0;
}