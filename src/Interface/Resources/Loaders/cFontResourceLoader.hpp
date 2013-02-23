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


#ifndef CFONTRESOURCELOADER_HPP
#define CFONTRESOURCELOADER_HPP

#include "Interface/Resources/cResourceLoaderBase.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

namespace Interface {

class cFontResourceLoader : public cResourceLoaderBase {

public:
    cFontResourceLoader(std::string filename, int frame, int size);
    virtual ~cFontResourceLoader() throw(exception::Fatal);
    
    virtual bool    Load();
    virtual bool    Release();
    virtual cResource * Get();
    virtual void    Return(cResource *);
    
private:
    friend class cFontResource;
    TTF_Font * Font();
    
private:
    int m_size;
    TTF_Font * m_font;    
};

};
#endif // CFONTRESOURCELOADER_HPP
