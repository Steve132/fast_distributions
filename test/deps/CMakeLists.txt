include(FetchContent)

FetchContent_Declare(
  cimg_fc
  URL "https://cimg.eu/files/CImg_latest.zip"
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Populate(cimg_fc)
add_library(CImg INTERFACE)
find_package(X11)
target_include_directories(CImg INTERFACE ${cimg_fc_SOURCE_DIR})
target_link_libraries(CImg INTERFACE X11)