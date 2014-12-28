#    Copyright (C) 2014 libtext_bayes authors(Antonio Costa, Cooler_),
#    
#    This file is part of libtext_bayers
#    
#    libtext_bayes is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    libtext_bayes is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#    You should have received a copy of the GNU Lesser General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CPP_FLAGS "-Ofast -fstack-protector-all -Wl,-z,relro,-z,now")

SET(libtext_bayesSources libtext_bayes)
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

ADD_LIBRARY(libtext_bayes SHARED ${libtext_bayesSources})
SET_TARGET_PROPERTIES(libtext_bayes PROPERTIES LINKER_LANGUAGE C)

ADD_LIBRARY(libtext_bayes_static STATIC ${libtext_bayesSources})
SET_TARGET_PROPERTIES(libtext_bayes_static PROPERTIES LINKER_LANGUAGE C)



