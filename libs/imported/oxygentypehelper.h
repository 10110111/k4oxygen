/* This file is part of the K4Oxygen project
 * Copyright (C) 2016 Ruslan Kabatsayev <b7.10110111@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef OXYGNE_TYPE_HELPER_20160608
#define OXYGNE_TYPE_HELPER_20160608

namespace Oxygen
{

#define DECLARE_ENUM(Class,Enum) template<> struct EnumIsDeclared<Class::Enum>{ static const bool value=true; typedef Class EnclosingClass; };
template<typename T> struct EnumIsDeclared { static const bool value=false; };

template<bool B, class T=void> struct enable_if{};
template<class T>              struct enable_if<true,T> { typedef T type; };

}

#endif
