/*
    Resource type enum.
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

#ifndef CRESOURCETYPE_H
#define CRESOURCETYPE_H

#include <type_traits>

namespace Interface {
    /**
     * Enum which lists what resources the manager supports.
     */
    enum class eResourceType {
        Texture,
        Font,
        Buffer,
        
        _count,         //Size of enum.
    };
    
    typedef std::integral_constant<eResourceType, eResourceType::Texture> TextureType;
    typedef std::integral_constant<eResourceType, eResourceType::Font> FontType;
    typedef std::integral_constant<eResourceType, eResourceType::Buffer> BufferType;
};

#endif