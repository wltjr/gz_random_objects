/** Copyright 2024 William L Thomson Jr <w@wltjr.com>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 */
#ifndef GZ_SIM_SYSTEMS_GzRandomObjects_HH_
#define GZ_SIM_SYSTEMS_GzRandomObjects_HH_

#include <memory>

#include <gz/sim/System.hh>

#ifdef USE_GZ8
namespace gz
{
    namespace sim
    {
        // Inline bracket to help doxygen filtering.
        inline namespace GZ_SIM_VERSION_NAMESPACE
#else
namespace ignition
{
    namespace gazebo
    {
        // Inline bracket to help doxygen filtering.
        namespace v6
#endif
        {
            namespace systems
            {
                /**
                 * @brief Class that stores all values from plugin xml
                 */
                class GzRandomObjectsPrivate;

                /**
                 * @brief Class that adds the random objects to gazebo
                 */
                class GzRandomObjects
                    : public System,
                      public ISystemConfigure
                {
                    public:
                        /**
                         * @brief Construct a new GzRandomObjects object, empty
                         *        just initializes a private class
                         */
                        GzRandomObjects();

                        /**
                         * @brief Destroy the GzRandomObjects object, empty/unused
                         */
                        ~GzRandomObjects() override = default;

                        /**
                         * @brief Configure the object from plugin xml
                         *
                         * @param _entity   The entity this plugin is attached to.
                         * @param _sdf      The SDF Element associated with this
                         *                  system plugin.
                         * @param _ecm      The EntityComponentManager of the  
                         *                  given simulation instance.
                         * @param  _eventMgr The EventManager of the given
                         *                   simulation instance.
                         */
                        void Configure(const Entity &_entity,
                                       const std::shared_ptr<const sdf::Element> &_sdf,
                                       EntityComponentManager &_ecm,
                                       EventManager &_eventMgr) override;

                    private:
                        std::unique_ptr<GzRandomObjectsPrivate> dataPtr = 
                            std::make_unique<GzRandomObjectsPrivate>();
                };
            }
        }
    }
}

#endif