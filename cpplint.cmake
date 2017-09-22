find_program(CPPLINT cpplint)

set(CPPLINT_LINE_LENGTH 120)
set(CPPLINT_FILTER
  -build/header_guard
  -build/include_subdir
  -whitespace)
string(REPLACE ";" "," CPPLINT_FILTER "${CPPLINT_FILTER}")

function(cpplint TARGET_NAME)
  set(SOURCES_LIST ${ARGN})
  list(REMOVE_DUPLICATES SOURCES_LIST)

  if(SOURCES_LIST)
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND ${CPPLINT} --linelength=${CPPLINT_LINE_LENGTH} --filter=${CPPLINT_FILTER} ${SOURCES_LIST}
      COMMENT "cpplint: Checking source code style"
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  endif()
endfunction()
