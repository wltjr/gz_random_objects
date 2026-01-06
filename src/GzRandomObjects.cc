/** Copyright 2024 William L. Thomson Jr. <w@wltjr.com>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 */

#include <random>
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
        double x_scale{0};
        double y_min{0};
        double y_max{0};
        double y_scale{0};
        double z_scale{0};
        int objects{0};
        std::vector<std::string> meshURIs;
};

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
    this->dataPtr->x_scale = _sdf->Get<double>("x_scale",
                                               this->dataPtr->x_scale).first;

    // y values
    this->dataPtr->y_min = _sdf->Get<double>("y_min",
                                             this->dataPtr->y_min).first;
    this->dataPtr->y_max = _sdf->Get<double>("y_max",
                                             this->dataPtr->y_max).first;
    this->dataPtr->y_scale = _sdf->Get<double>("y_scale",
                                               this->dataPtr->y_scale).first;
                         
    // z values                      
    this->dataPtr->z_scale = _sdf->Get<double>("z_scale",
                                               this->dataPtr->z_scale).first;

    SdfEntityCreator sec = SdfEntityCreator(_ecm, _eventManager);
    std::random_device rd;
    std::mt19937 gen(rd());

    int meshes = this->dataPtr->meshURIs.size() - 1;

    for( int i = 1, m = 0 ; i <= this->dataPtr->objects; i++, m++ )
    {
        Entity objEntity;
        sdf::Model objModel;
        sdf::SDF objSDF;
        std::stringstream ss;
        std::stringstream mesh;

        std::uniform_real_distribution<float> x_dist(this->dataPtr->x_min,
                                                     this->dataPtr->x_max);
        std::uniform_real_distribution<float> y_dist(this->dataPtr->y_min,
                                                     this->dataPtr->y_max);
        float x = x_dist(gen) / 1000.0;
        float y = y_dist(gen) / 1000.0;

        if(m > meshes)
            m = 0;

        mesh << "\n"
                "<geometry>\n"
                "    <mesh>\n"
                "        <uri>" << this->dataPtr->meshURIs[m] << "</uri>\n"
                "        <scale>" << this->dataPtr->x_scale << " " << this->dataPtr->y_scale << " " << this->dataPtr->z_scale << "</scale>\n"
                "    </mesh>\n"
                "</geometry>";

        ss << "<?xml version='1.0'?>\n"
            "<sdf version='1.7'>\n"
            "<model name='obj" << i << "'>\n"
            "    <pose>" << std::setw(5) << x << " " << std::setw(5) << y << " 0 0 0 0</pose>\n"
            "    <link name='obj" << i << "'>\n"
            "    <collision name='obj" << i << "_collision'>\n"
            "        " << mesh.str() << "\n"
            "    </collision>\n"
            "    <visual name='obj" << i << "_visual'>\n"
            "        <pose>0 0 0 0 0 0</pose>\n"
            "        " << mesh.str() << "\n"
            "        <meta>\n"
            "        <layer>0</layer>\n"
            "        </meta>\n"
            "    </visual>\n"
            "    </link>\n"
            "    <static>1</static>\n"
            "</model>\n"
            "</sdf>";

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
