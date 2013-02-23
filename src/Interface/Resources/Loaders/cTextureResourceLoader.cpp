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


#include "cTextureResourceLoader.hpp"
#include "Interface/Resources/Types/cTextureResource.hpp"

#include <iostream>

using namespace Interface;

cTextureResourceLoader::cTextureResourceLoader(std::string filename, int frame)
: cResourceLoaderBase(cTextureResource::Type::value, filename, frame) {

}

cTextureResourceLoader::~cTextureResourceLoader() throw(exception::Fatal)
{


}

cResource* cTextureResourceLoader::Get() {
    cTextureResource * result = new cTextureResource(this);
    
    return result;
}

bool cTextureResourceLoader::Load() {

    SDL_Surface * loaded_surface = nullptr;

    loaded_surface = IMG_Load(m_filename.c_str());

    if(loaded_surface) {
        m_surface = SDL_DisplayFormatAlpha(loaded_surface);
        std::cout << "Image loaded: " << m_filename << std::endl;
        SDL_FreeSurface(loaded_surface);
        
        m_loaded = true;
        return true;
    } else {
        std::cout << "Image failed to load: " << IMG_GetError() << std::endl;
        
        m_loaded = false;
        return false;
    }
}

bool cTextureResourceLoader::Release() {
    if (m_surface) {
        SDL_FreeSurface(m_surface);
        m_surface = nullptr;
        
        m_loaded = false;
    }    
}

void cTextureResourceLoader::Return(cResource* resource) {
    //Delete the pointer if type is right:
    delete resource;    
}




SDL_Surface* cTextureResourceLoader::RealSurface() {

}

SDL_Surface* cTextureResourceLoader::ProxySurface() {

}
