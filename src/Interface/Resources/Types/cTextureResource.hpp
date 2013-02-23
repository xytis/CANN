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


#ifndef TEXTURERESOURCE_HPP
#define TEXTURERESOURCE_HPP

#include <Interface/Resources/eResourceType.hpp>
#include <Interface/Resources/cResource.hpp>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

namespace Interface {

class cTextureResourceLoader;

class cTextureResource : public cResource {
public:
    typedef TextureType Type;
public:
    cTextureResource(cTextureResourceLoader * loader);
    virtual ~cTextureResource();
    
    /// Returns true if full resource is not loaded yet.
    bool IsProxy();
    
    /// Returns undelying resource or proxy resource.
    SDL_Surface * Surface();
    
private:
    bool                m_proxy;
    SDL_Surface *       m_surface;
    cTextureResourceLoader * m_loader;
};

//Inline definitions

};

#endif // TEXTURERESOURCE_HPP
