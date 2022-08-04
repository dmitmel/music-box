find_program(CPPLINT cpplint)

function(cpplint TARGET_NAME)
  set(SRCS ${${TARGET_NAME}_SRCS})
  set(EXCLUDE ${${TARGET_NAME}_CPPLINT_EXCLUDE})

  foreach(file ${EXCLUDE})
    LIST(REMOVE_ITEM SRCS "${file}")
  endforeach()

  set(LINE_LENGTH ${${TARGET_NAME}_CPPLINT_LINE_LENGTH})
  set(FILTER ${${TARGET_NAME}_CPPLINT_FILTER})
  string(REPLACE ";" "," FILTER "${FILTER}")

  if(SRCS)
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND ${CPPLINT} --linelength=${LINE_LENGTH} --filter=${FILTER} ${SRCS}
      COMMENT "cpplint: Checking source code style"
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  endif()
endfunction()
