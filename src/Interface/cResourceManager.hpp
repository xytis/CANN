#ifndef CRESOURCEMANAGER_H_INCLUDED
#define CRESOURCEMANAGER_H_INCLUDED

#include "Utils/exception.hpp"
#include "Utils/sdl_video.hpp"

#include "Interface/Resources/eResourceType.hpp"

#include "Interface/Resources/cResource.hpp"
#include "Interface/Resources/cResourceLoaderBase.hpp"

#include "Interface/Resources/Loaders/cFontResourceLoader.hpp"
#include "Interface/Resources/Loaders/cTextureResourceLoader.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

#include <algorithm>

namespace Interface
{
    class cResourceLoaderBase;
    
    class cResourceManager
    {
        private:
            typedef std::unordered_map<std::string, cResourceLoaderBase *> resource_map;
            typedef std::pair<std::string, cResourceLoaderBase *> resource_pair;
            
            std::vector< resource_map > m_resources;
            std::string m_root_path;
            
            //Resources are allocated in frames. On clean event only last frame is cleaned.
            int m_frame;
            
            //Helper functions
            resource_map & container(eResourceType type);
            void clean_this_frame();
            
        public:
            cResourceManager(std::string root_path);
            ~cResourceManager() noexcept(false);        //May throw!
            
            std::string GetRealPath(std::string filename);
            
            //Loading methods
            
            ///Create one resource loader from relative path.
            template<typename Loader, typename... Args>
            cResourceLoaderBase * Create(std::string filename, Args... args);
            ///Loading is executed by resource loader. If force load is set -- loading is done on spot.
            void Register(std::string id, cResourceLoaderBase * loader, bool force_load = false);
            
            //Frame control
            void PushFrame() noexcept;
            void PopFrame() throw(exception::Fatal);
            int CurrentFrame() const noexcept;
            void CleanUp();
            
            //Resource getters.
            cResource * Get(eResourceType type, std::string id);
            
            template<typename Resource>
            Resource * Get(std::string id);
    };
};            

// Inline definitions
inline Interface::cResourceManager::resource_map& Interface::cResourceManager::container(Interface::eResourceType type) {
    return this->m_resources[(size_t) type];
}


inline Interface::cResource * Interface::cResourceManager::Get(Interface::eResourceType type, std::string id) {
    return container(type)[id]->Get();
}

inline std::string Interface::cResourceManager::GetRealPath(std::string filename) {
    return m_root_path + "/" + filename;
}


// Templated definitions

template<typename Resource>
Resource * Interface::cResourceManager::Get(std::string id) {
    return dynamic_cast<Resource *> (Get(Resource::Type::value, id));
}

template<typename Loader, typename... Args>
Interface::cResourceLoaderBase * Interface::cResourceManager::Create(std::string filename, Args... args) {
    return new Loader(GetRealPath(filename), args...);
}

#endif // CRESOURCEMANAGER_H_INCLUDED
