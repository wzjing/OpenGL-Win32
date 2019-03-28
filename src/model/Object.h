//
// Created by android1 on 2019/3/6.
//

#ifndef OPENGLFOO_OBJECT_H
#define OPENGLFOO_OBJECT_H

#include "component/RigidBody.h"
#include "component/Material.h"
#include "component/Transform.h"

class Object {
 public:
  void * verteces;
  void * indices;
  RigidBody * rigidBody;
  Material * material;
  Transform * transform;

  void draw();

  void onFrame();

};


#endif //OPENGLFOO_OBJECT_H
