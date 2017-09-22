set(Arduino_FOUND False)

# find root path
if (NOT DEFINED Arduino_ROOT_DIR)
  if (IS_DIRECTORY /usr/share/arduino)
    set(Arduino_ROOT_DIR /usr/share/arduino CACHE PATH "Arduino root directory")
  elseif (IS_DIRECTORY /usr/local/share/arduino)
    set(Arduino_ROOT_DIR /usr/local/share/arduino CACHE PATH "Arduino root directory")
  elseif (IS_DIRECTORY /Applications/Arduino.app/Contents/Java)
    set(Arduino_ROOT_DIR /Applications/Arduino.app/Contents/Java CACHE PATH "Arduino root directory")
  endif ()
endif ()

# default component (arduino core)
if (NOT DEFINED Arduino_FIND_COMPONENTS)
  set(Arduino_FIND_COMPONENTS core_arduino)
endif ()

if (NOT DEFINED Arduino_USER_LIBRARIES_DIR)
  set(Arduino_USER_LIBRARIES_DIR $ENV{HOME}/Arduino CACHE PATH "Arduino user libraries directory")
endif ()

# default variant
if (NOT DEFINED Arduino_VARIANT)
  set(Arduino_VARIANT standard CACHE STRING "Arduino variant (see ${Arduino_ROOT_DIR}/hardware/arduino/avr/variants)")
endif ()

# check if all component are founds
set(Arduino_FOUND True)
set(Arduino_INCLUDE_DIRS "")
set(Arduino_LIBRARIES "")

foreach (COMPONENT ${Arduino_FIND_COMPONENTS})
  if (${COMPONENT} MATCHES core_.*)
    # component is a core module

    # remove "core_" prefix
    string(REGEX REPLACE core_ "" Arduino_CORE_NAME ${COMPONENT})

    set(core_dir ${Arduino_ROOT_DIR}/hardware/arduino/avr/cores/${Arduino_CORE_NAME})
    if (IS_DIRECTORY ${core_dir})
      set(Arduino_FOUND_${COMPONENT} True)
      set(Arduino_CORE_ROOT_DIR ${core_dir})
      set(Arduino_INCLUDE_DIRS ${Arduino_INCLUDE_DIRS} "${core_dir}")
      set(Arduino_LIBRARIES ${Arduino_LIBRARIES} "${COMPONENT}")
    else ()
      set(Arduino_FOUND_${COMPONENT} False)
    endif ()
  else ()
    set(lib_dir ${Arduino_ROOT_DIR}/libraries/${COMPONENT})
    set(user_lib_dir ${Arduino_USER_LIBRARIES_DIR}/${COMPONENT})

    if (IS_DIRECTORY ${lib_dir})
      # component is a bundled library

      set(Arduino_FOUND_${COMPONENT} True)
      set(Arduino_${COMPONENT}_ROOT_DIR ${lib_dir})
      set(Arduino_INCLUDE_DIRS ${Arduino_INCLUDE_DIRS} "${lib_dir}")
      set(Arduino_LIBRARIES ${Arduino_LIBRARIES} "${COMPONENT}")
    elseif (IS_DIRECTORY ${user_lib_dir})
      # component is a user library

      set(Arduino_FOUND_${COMPONENT} True)
      set(Arduino_${COMPONENT}_ROOT_DIR ${user_lib_dir})
      set(Arduino_INCLUDE_DIRS ${Arduino_INCLUDE_DIRS} "${user_lib_dir}")
      set(Arduino_LIBRARIES ${Arduino_LIBRARIES} "${COMPONENT}")
    else ()
      set(Arduino_FOUND_${COMPONENT} False)
    endif ()
  endif ()

  if (NOT ${Arduino_FOUND_${COMPONENT}})
    if (${Arduino_FIND_REQUIRED_${COMPONENT}})
      set(Arduino_FOUND False)
    else ()
      message(WARNING "Arduino optional component ${COMPONENT} not found")
    endif ()
  endif ()
endforeach ()

if (NOT IS_DIRECTORY ${Arduino_ROOT_DIR}/hardware/arduino/avr/variants/${Arduino_VARIANT})
  set(Arduino_FOUND False)
endif ()

if (${Arduino_FOUND})
  # add components as CMake libraries

  set(Arduino_VARIANT_DIR ${Arduino_ROOT_DIR}/hardware/arduino/avr/variants/${Arduino_VARIANT})
  set(Arduino_INCLUDE_DIRS ${Arduino_INCLUDE_DIRS} "${Arduino_VARIANT_DIR}")
  set(Arduino_LIBRARIES_ROOT_DIR ${Arduino_ROOT_DIR}/libraries)

  foreach (COMPONENT ${Arduino_FIND_COMPONENTS})
    if (${COMPONENT} MATCHES core_.*)
      # component is a core module

      # get all files in the core directory
      file(GLOB SOURCE ${Arduino_CORE_ROOT_DIR}/*.c ${Arduino_CORE_ROOT_DIR}/*.cpp)
      avr_add_library(${COMPONENT} ${SOURCE})
      target_include_directories(${COMPONENT}
        PUBLIC ${Arduino_CORE_ROOT_DIR}
        PRIVATE ${Arduino_VARIANT_DIR})
    else ()
      # component is a library

      # get all files in the library
      file(GLOB SOURCE ${Arduino_${COMPONENT}_ROOT_DIR}/*.c ${Arduino_${COMPONENT}_ROOT_DIR}/*.cpp)
      avr_add_library(${COMPONENT} ${SOURCE})
      target_include_directories(${COMPONENT}
        PUBLIC ${Arduino_${COMPONENT}_ROOT_DIR}
        PRIVATE ${Arduino_CORE_ROOT_DIR} ${Arduino_VARIANT_DIR} ${Arduino_LIBRARIES_ROOT_DIR})
    endif ()
  endforeach ()
else ()
  if (${Arduino_FIND_REQUIRED})
    message(FATAL_ERROR "Arduino libraries not found")
  else (${Arduino_FIND_REQUIRED})
    if (NOT {Arduino_FIND_QUIETLY})
      message(WARNING "Arduino libraries not found")
    endif (NOT {Arduino_FIND_QUIETLY})
  endif (${Arduino_FIND_REQUIRED})
endif (${Arduino_FOUND})

