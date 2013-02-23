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


#include "cResourceLoaderBase.hpp"

#include <cassert>

using namespace Interface;

cResourceLoaderBase::cResourceLoaderBase(eResourceType type, std::string filename, int frame) noexcept
: m_type(type)        //Child clases have to set this value.
, m_filename(filename)
, m_loaded(false) //On construction resource is not loaded
, m_reference_count(0)
, m_frame(frame) {
}

cResourceLoaderBase::~cResourceLoaderBase() throw(exception::Fatal) {
    //On destruction -- make shure the resource is unloaded.
    //If resource is still in use -- raise some error.
    if (IsUsed()) {
        throw exception::Fatal("Used resource is destoyed!");
    }
    //Final check
    if (IsLoaded()) {
        throw exception::Fatal("Resource unload failed! Possibly bad implementation.");
    }
}

bool cResourceLoaderBase::IsLoaded() const noexcept {
    return m_loaded;
}

bool cResourceLoaderBase::IsUsed() const noexcept {
    return m_reference_count > 0;
}

bool cResourceLoaderBase::InFrame(int frame) const noexcept {
    return m_frame == frame;
}

void cResourceLoaderBase::IncReference() {
    ++m_reference_count;
}

void cResourceLoaderBase::DecReference() {
    --m_reference_count;
    assert(m_reference_count > -1);
}
