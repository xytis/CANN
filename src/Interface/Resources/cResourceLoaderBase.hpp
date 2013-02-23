/*
    Resource loader base interface.
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


#ifndef CRESOURCELOADERBASE_H
#define CRESOURCELOADERBASE_H

#include "Utils/exception.hpp"
#include "Interface/Resources/eResourceType.hpp"

namespace Interface
{
class cResource;

class cResourceLoaderBase {
protected:
    eResourceType   m_type;
    std::string     m_filename;
    bool            m_loaded;
    int             m_reference_count;
    const int       m_frame;
public:
    cResourceLoaderBase(eResourceType type, std::string filename, int frame) noexcept;
    virtual ~cResourceLoaderBase() throw(exception::Fatal);
    //Explicitly removed.
    cResourceLoaderBase& operator=(const cResourceLoaderBase& other) = delete;
    cResourceLoaderBase(const cResourceLoaderBase & copy) = delete;
    cResourceLoaderBase(cResourceLoaderBase && move) = delete;

    bool            IsLoaded() const noexcept;
    bool            IsUsed() const noexcept;
    bool            InFrame(int frame) const noexcept;

    virtual bool    Load() = 0;
    virtual bool    Release() = 0;
    virtual cResource * Get() = 0;
    virtual void    Return(cResource *) = 0;
    
    void            IncReference();
    void            DecReference();
};
};

#endif // CRESOURCELOADERBASE_H
