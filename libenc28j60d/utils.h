/*
libenc28j60d - ENC28J60 low-level driver for AVR MCUs
Copyright (C) 2011  Simon Marchi
                    Philippe Proulx

This library is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#ifndef _UTILS_H
#define _UTILS_H

#define SET(reg, bit)	do { reg |= _BV(bit); } while (0)
#define CLR(reg, bit)	do { reg &= ~_BV(bit); } while (0)

#endif /* _UTILS_H */
