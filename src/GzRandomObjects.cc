/** Copyright 2024 William L. Thomson Jr. <w@wltjr.com>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 */

#include <vector>

#include <gz/sim/Model.hh>
#include <gz/sim/Util.hh>
#include <gz/sim/SdfEntityCreator.hh>
#include <gz/sim/System.hh>
#include <gz/plugin/Register.hh>
#include <sdf/sdf.hh>

#include "GzRandomObjects.hh"

using namespace gz;
using namespace sim;
using namespace systems;

/**
 * @brief Class that stores all values from plugin xml
 */
class gz::sim::systems::GzRandomObjectsPrivate
{
    public:
        long parent{0};
        double x_min{0};
        double x_max{0};
        long x_range{0};
        double x_scale{0};
        double y_min{0};
        double y_max{0};
        long y_range{0};
        double y_scale{0};
        double z_scale{0};
        int objects{0};
        std::vector<std::string> meshURIs;
};

GzRandomObjects::GzRandomObjects()
  : dataPtr(std::make_unique<GzRandomObjectsPrivate>())
{
}

void GzRandomObjects::Configure(const Entity &/*_entity*/,
                                const std::shared_ptr<const sdf::Element> &_sdf,
                                EntityComponentManager &_ecm,
                                EventManager &_eventManager)
{
    // Get params from SDF
    auto sdfElem = _sdf->FindElement("mesh");
    while (sdfElem)
    {
        this->dataPtr->meshURIs.push_back(sdfElem->Get<std::string>());
        sdfElem = sdfElem->GetNextElement("mesh");
    }

    this->dataPtr->objects = _sdf->Get<int>("objects",
                                            this->dataPtr->objects).first;

    this->dataPtr->parent = _sdf->Get<int>("parent",
                                           this->dataPtr->parent).first;

    // x values
    this->dataPtr->x_min = _sdf->Get<double>("x_min",
                                             this->dataPtr->x_min).first;
    this->dataPtr->x_max = _sdf->Get<double>("x_max",
                                             this->dataPtr->x_max).first;
    // set x range
    this->dataPtr->x_range = this->dataPtr->x_max - this->dataPtr->x_min;
    this->dataPtr->x_scale = _sdf->Get<double>("x_scale",
                                               this->dataPtr->x_scale).first;

    // y values
    this->dataPtr->y_min = _sdf->Get<double>("y_min",
                                             this->dataPtr->y_min).first;
    this->dataPtr->y_max = _sdf->Get<double>("y_max",
                                             this->dataPtr->y_max).first;
    // set y range
    this->dataPtr->y_range = this->dataPtr->y_max - this->dataPtr->y_min;
    this->dataPtr->y_scale = _sdf->Get<double>("y_scale",
                                               this->dataPtr->y_scale).first;
                         
    // z values                      
    this->dataPtr->z_scale = _sdf->Get<double>("z_scale",
                                               this->dataPtr->z_scale).first;

    SdfEntityCreator sec = SdfEntityCreator(_ecm, _eventManager);
    srand(time(0));

    for( int i = 1 ; i <= this->dataPtr->objects; i++ )
    {
        Entity objEntity;
        sdf::Model objModel;
        sdf::SDF objSDF;
        std::stringstream ss;
        std::stringstream mesh;

        float x = ((rand() % this->dataPtr->x_range) + this->dataPtr->x_min) / 1000.0;
        float y = ((rand() % this->dataPtr->y_range) + this->dataPtr->y_min) / 1000.0;

        mesh << "\
                <geometry>\
                    <mesh>\
                        <uri>" << this->dataPtr->meshURIs[i-1] << "</uri>\
                        <scale>" << this->dataPtr->x_scale << " " << this->dataPtr->y_scale << " " << this->dataPtr->z_scale << "</scale>\
                    </mesh>\
                </geometry>";

        ss << "<?xml version='1.0'?>\
            <sdf version='1.7'>\
            <model name='obj" << i << "'>\
                <pose>" << std::setw(5) << x << " " << std::setw(5) << y << " 0 0 0 0</pose>\
                <link name='obj" << i << "'>\
                <collision name='obj" << i << "_collision'>\
                    " << mesh.str() << "\
                </collision>\
                <visual name='obj" << i << "_visual'>\
                    <pose>0 0 0 0 0 0</pose>\
                    " << mesh.str() << "\
                    <meta>\
                    <layer>0</layer>\
                    </meta>\
                </visual>\
                </link>\
                <static>1</static>\
            </model>\
            </sdf>";

        objSDF.SetFromString(ss.str());
        objModel.Load(objSDF.Root()->GetElement("model"));
        objEntity = sec.CreateEntities(&objModel);
        sec.SetParent(objEntity, this->dataPtr->parent);
    }
}

#ifdef USE_GZ8
// Register plugin
GZ_ADD_PLUGIN(GzRandomObjects,
              gz::sim::System,
              GzRandomObjects::ISystemConfigure)

// Add plugin alias so that we can refer to the plugin without the version namespace
GZ_ADD_PLUGIN_ALIAS(GzRandomObjects, "gz::sim::systems::GzRandomObjects")
#else
// Register plugin
IGNITION_ADD_PLUGIN(GzRandomObjects,
                    gz::sim::System,
                    GzRandomObjects::ISystemConfigure)

// Add plugin alias so that we can refer to the plugin without the version namespace
IGNITION_ADD_PLUGIN_ALIAS(GzRandomObjects, "gz::sim::systems::GzRandomObjects")
#endif
