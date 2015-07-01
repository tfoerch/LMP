add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_node.hpp ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_node.cpp
  COMMAND omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -I${PROJECT_SOURCE_DIR}/idl ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_node.idl
)

add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_node_registry.hpp ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_node_registry.cpp
  COMMAND omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -I${PROJECT_SOURCE_DIR}/idl ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_node_registry.idl
)

add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_neighbor.hpp ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_neighbor.cpp
  COMMAND omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -I${PROJECT_SOURCE_DIR}/idl ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_neighbor.idl
)

add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_ipcc.hpp ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_ipcc.cpp
  COMMAND omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -I${PROJECT_SOURCE_DIR}/idl ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_ipcc.idl
)

add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_ipcc_observer.hpp ${PROJECT_BINARY_DIR}/idl/lmp_mgtif_ipcc_observer.cpp
  COMMAND omniidl -bcxx -Wbh=.hpp -Wbs=.cpp -I${PROJECT_SOURCE_DIR}/idl ${PROJECT_SOURCE_DIR}/idl/lmp_mgtif_ipcc_observer.idl
)

add_library (
lmp_mgtif
${PROJECT_BINARY_DIR}/idl/lmp_mgtif_node.cpp
${PROJECT_BINARY_DIR}/idl/lmp_mgtif_node_registry.cpp
${PROJECT_BINARY_DIR}/idl/lmp_mgtif_neighbor.cpp
${PROJECT_BINARY_DIR}/idl/lmp_mgtif_ipcc.cpp
${PROJECT_BINARY_DIR}/idl/lmp_mgtif_ipcc_observer.cpp )

