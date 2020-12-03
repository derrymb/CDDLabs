/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
 */

/*! \page Event.h
    \file Event.h
    \author Derry Brennan 
    \date 27/11/2020
    \copyright This code is covered by the GNU General Public License v3.0
    \name Event.h

    The declarations for the Event object
*/

/* Code: */
#pragma once
class Event{
    private:
        char theChar;
    public:
        Event();
        void consume();
};
/* Event.h ends here */
