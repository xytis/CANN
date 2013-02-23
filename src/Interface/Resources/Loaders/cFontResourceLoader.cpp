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


#include "cFontResourceLoader.hpp"
#include "Interface/Resources/Types/cFontResource.hpp"


#include <iostream>

using namespace Interface;

cFontResourceLoader::cFontResourceLoader(std::string filename, int frame, int size)
: cResourceLoaderBase(cFontResource::Type::value, filename, frame)
, m_size(size) {

}

cFontResourceLoader::~cFontResourceLoader() throw(exception::Fatal)
{


}

cResource* cFontResourceLoader::Get() {
    cFontResource * result = new cFontResource(this);
    
    return result;
}

bool cFontResourceLoader::Load() {

    m_font = TTF_OpenFont(m_filename.c_str(), m_size);
    
    m_loaded = (bool) m_font;
    
    return m_loaded;
}

bool cFontResourceLoader::Release() {
    if (m_font) {
        TTF_CloseFont(m_font);
        m_font = nullptr;
        
        m_loaded = false;
    }    
}

void cFontResourceLoader::Return(cResource* resource) {
    //Delete the pointer if type is right:
    delete resource;    
}
