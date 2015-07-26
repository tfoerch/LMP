add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_node.hpp ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_node.cpp
  DEPENDS ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_node.idl
  COMMAND omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -I${PROJECT_SOURCE_DIR}/idl ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_node.idl
)

add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_node_registry.hpp ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_node_registry.cpp
  DEPENDS ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_node_registry.idl
  COMMAND omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -I${PROJECT_SOURCE_DIR}/idl ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_node_registry.idl
)

add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_neighbor.hpp ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_neighbor.cpp
  DEPENDS ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_neighbor.idl
  COMMAND omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -I${PROJECT_SOURCE_DIR}/idl ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_neighbor.idl
)

add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_ipcc.hpp ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_ipcc.cpp
  DEPENDS ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_ipcc.idl
  COMMAND omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -I${PROJECT_SOURCE_DIR}/idl ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_ipcc.idl
)

add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_ipcc_observer.hpp ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_ipcc_observer.cpp
  DEPENDS ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_ipcc_observer.idl
  COMMAND omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -I${PROJECT_SOURCE_DIR}/idl ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_ipcc_observer.idl
)

add_library (
lmp_mgtif SHARED
${PROJECT_BINARY_DIR}/idl/lmp_mgtif_node.cpp
${PROJECT_BINARY_DIR}/idl/lmp_mgtif_node_registry.cpp
${PROJECT_BINARY_DIR}/idl/lmp_mgtif_neighbor.cpp
${PROJECT_BINARY_DIR}/idl/lmp_mgtif_ipcc.cpp
${PROJECT_BINARY_DIR}/idl/lmp_mgtif_ipcc_observer.cpp )

INSTALL(TARGETS lmp_mgtif DESTINATION lib)
