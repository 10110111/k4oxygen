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

#ifndef OXYGEN_MACROS_H
#define OXYGEN_MACROS_H

// From kdemacros.h
/**
 * @def KDE_NO_EXPORT
 * @ingroup KDEMacros
 *
 * The KDE_NO_EXPORT macro marks the symbol of the given variable
 * to be hidden. A hidden symbol is stripped during the linking step,
 * so it can't be used from outside the resulting library, which is similar
 * to static. However, static limits the visibility to the current
 * compilation unit. Hidden symbols can still be used in multiple compilation
 * units.
 *
 * \code
 * int KDE_NO_EXPORT foo;
 * int KDE_EXPORT bar;
 * \endcode
 *
 * @sa KDE_EXPORT
 */

/**
 * @def KDE_EXPORT
 * @ingroup KDEMacros
 *
 * The KDE_EXPORT macro marks the symbol of the given variable
 * to be visible, so it can be used from outside the resulting library.
 *
 * \code
 * int KDE_NO_EXPORT foo;
 * int KDE_EXPORT bar;
 * \endcode
 *
 * @sa KDE_NO_EXPORT
 */

/**
 * @def KDE_IMPORT
 * @ingroup KDEMacros
 */

#ifdef __GNUC__
#define KDE_NO_EXPORT __attribute__ ((visibility("hidden")))
#define KDE_EXPORT __attribute__ ((visibility("default")))
#define KDE_IMPORT __attribute__ ((visibility("default")))
#elif defined(_WIN32) || defined(_WIN64)
#define KDE_NO_EXPORT
#define KDE_EXPORT __declspec(dllexport)
#define KDE_IMPORT __declspec(dllimport)
#else
#define KDE_NO_EXPORT
#define KDE_EXPORT
#define KDE_IMPORT
#endif

#define KDEUI_EXPORT KDE_EXPORT
#define KDECORE_EXPORT KDE_EXPORT

#endif
