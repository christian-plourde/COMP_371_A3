#include "ObjectContainer.h"

ObjectContainer::ObjectContainer() {}

ObjectContainer::~ObjectContainer() {}

void ObjectContainer::addObject(Object obj)
{
    objects.push_back(obj);
}

