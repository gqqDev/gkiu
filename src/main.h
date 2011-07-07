/*
 * GKiu
 * Copyright (C) 2011 GQQ Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MAIN_H
#define MAIN_H

/*
  debug
 */
#define DEBUG
#ifndef DEBUG   /* if it isn't debugging or in development */
#    define NDEBUG
#    define RELEASE
#endif /* DEBUG */

/*
  Some definations
 */
#define WHERE_ICON	PACKAGE_DATA_DIR "/pictures/icon.png"

#endif /* MAIN_H */
