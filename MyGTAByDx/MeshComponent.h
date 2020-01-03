/* MeshComponent is an abstract base for any component that is an instance of a renderable collection of triangles.
 *
 * @see StaticMeshComponent
 * @see SkeletalMeshComponent(��û��)
 */

#pragma once
#include "PrimitiveComponent.h"
class MeshComponent : public PrimitiveComponent {
public:
    MeshComponent();
    virtual ~MeshComponent();
};
