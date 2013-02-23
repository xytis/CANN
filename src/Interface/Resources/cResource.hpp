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


#ifndef RESOURCE_H
#define RESOURCE_H

namespace Interface {

class cResource
{
public:
    //Child classes must overload this typedef. Otherwise compilation error will occur.
    typedef void Type;
public:
    cResource();
    virtual ~cResource();
    
    cResource(const cResource& other) = delete;
    virtual cResource& operator=(const cResource& other) = delete;
};

};
#endif // RESOURCE_H
