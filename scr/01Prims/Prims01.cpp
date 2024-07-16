#include <iostream>
#include <string>

#include <pxr/base/vt/value.h>
#include <pxr/usd/sdf/attributeSpec.h>
#include <pxr/usd/sdf/path.h>
#include <pxr/usd/sdf/types.h>
#include <pxr/usd/usd/attribute.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/stage.h>


void as_usd()
{
    auto stage = pxr::UsdStage::CreateInMemory();
    auto prim = stage->DefinePrim(pxr::SdfPath {"/root"});
    auto attribute = prim.CreateAttribute(
        pxr::TfToken {"some_name"},
        pxr::SdfValueTypeNames->Int,
        true
    );

    attribute.Set(8);

    auto layer = stage->GetEditTarget().GetLayer();  // By default, this is `stage.GetRootLayer`
    layer->SetTimeSample(attribute.GetPath(), 10.5, 9);

    auto* result = new std::string();
    stage->GetRootLayer()->ExportToString(result);
    std::cout << *result << std::endl;
    delete result;
    result = nullptr;
}

int main() {
    as_usd();

    return 0;
}