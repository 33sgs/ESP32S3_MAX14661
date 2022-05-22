# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/aperture/esp/esp-idf/components/bootloader/subproject"
  "/home/aperture/MAX14661Config/build/bootloader"
  "/home/aperture/MAX14661Config/build/bootloader-prefix"
  "/home/aperture/MAX14661Config/build/bootloader-prefix/tmp"
  "/home/aperture/MAX14661Config/build/bootloader-prefix/src/bootloader-stamp"
  "/home/aperture/MAX14661Config/build/bootloader-prefix/src"
  "/home/aperture/MAX14661Config/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/aperture/MAX14661Config/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
