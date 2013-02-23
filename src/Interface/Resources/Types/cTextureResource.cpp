/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  Vytis Valentinavičius <vytis.valentinavicius@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "cTextureResource.hpp"
#include <Interface/Resources/Loaders/cTextureResourceLoader.hpp>

using namespace Interface;


cTextureResource::cTextureResource(cTextureResourceLoader* loader)
: m_proxy(true) 
, m_surface(nullptr)    
, m_loader(loader) {
    if (m_loader->IsLoaded()) {
        m_surface = m_loader->RealSurface();
        m_proxy = false;
    } else {
        m_surface = m_loader->ProxySurface();
        m_proxy = true;
    }
    
    m_loader->IncReference();
}

cTextureResource::~cTextureResource() {
    m_loader->DecReference();
}

bool cTextureResource::IsProxy() {
    return m_proxy;
}

SDL_Surface* cTextureResource::Surface() {
    //Try to return the surface:
    if (m_proxy) {
        //Check if loader did his job
        if (m_loader->IsLoaded()) {
            //Get Your surface:
            m_surface = m_loader->RealSurface();
            m_proxy = false;
        }
    }
    return m_surface;
}

