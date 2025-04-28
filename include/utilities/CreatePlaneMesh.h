// include/utilities/CreatePlaneMesh.h
#pragma once

#include "core/Mesh.h"

// Create a plane mesh centered at origin, facing +Z
// width: X axis extent
// height: Y axis extent
// uvRepeat: how many times UV wraps (default 1.0f)
Mesh CreatePlaneMesh(float width, float height, float uvRepeat = 1.0f);
