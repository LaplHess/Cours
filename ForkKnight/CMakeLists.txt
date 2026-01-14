# CMakeLists.txt pour Fork Knight
# Compatible avec CLion et autres IDEs modernes
cmake_minimum_required(VERSION 3.15)
project(ForkKnight C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -g")

# Inclure les headers
include_directories(headers)
include_directories(tests/unity)

# ==========================================
# Programme Principal
# ==========================================
set(MAIN_SOURCES
    src/player.c
    src/array-utils.c
    src/main.c
        src/list-utils.c
)

add_executable(main ${MAIN_SOURCES})

# ==========================================
# Tests Partie 1
# ==========================================
set(COMMON_SOURCES
    src/player.c
    src/array-utils.c
    tests/unity/unity.c
)

# Tests module player
add_executable(test_part1_player
    ${COMMON_SOURCES}
    tests/part1/test_player.c
)

# Tests module array-utils
add_executable(test_part1_array
    ${COMMON_SOURCES}
    tests/part1/test_array_utils.c
)

# ==========================================
# Tests Partie 4
# ==========================================
set(PART4_SOURCES
    src/player.c
    src/array-utils.c
    src/list-utils.c
    src/priority-queue.c
    tests/unity/unity.c
    tests/part4/test_priority_queue.c
)

add_executable(test_part4 ${PART4_SOURCES})

# Valgrind pour la partie 4
if(VALGRIND)
    add_custom_target(valgrind-part4
        COMMAND ${VALGRIND} --leak-check=full --error-exitcode=1 ./test_part4
        DEPENDS test_part4
        COMMENT "Vérification mémoire avec Valgrind (priority-queue.c)"
    )
endif()

# ==========================================
# Tests Partie 5
# ==========================================
set(PART5_SOURCES
    src/player.c
    src/array-utils.c
    src/list-utils.c
    src/priority-queue.c
    src/match.c
    tests/unity/unity.c
    tests/part5/test_match.c
)

add_executable(test_part5 ${PART5_SOURCES})

# Valgrind pour la partie 5
if(VALGRIND)
    add_custom_target(valgrind-part5
        COMMAND ${VALGRIND} --leak-check=full --error-exitcode=1 ./test_part5
        DEPENDS test_part5
        COMMENT "Vérification mémoire avec Valgrind (match.c)"
    )
endif()

# ==========================================
# Simulation complète (Partie 6)
# ==========================================
set(SIMULATION_SOURCES
    src/player.c
    src/array-utils.c
    src/list-utils.c
    src/priority-queue.c
    src/match.c
    src/simulation.c
    src/test-simulation.c
)

add_executable(test-simulation ${SIMULATION_SOURCES})

# ==========================================
# Configuration CLion
# ==========================================
# Définir les configurations de run pour CLion
# Les étudiants pourront sélectionner :
# - "main" : Exécuter le programme
# - "test_part1_player" : Tests du module player
# - "test_part1_array" : Tests du module array-utils
# - "test_part4" : Tests du module priority-queue
# - "test_part5" : Tests du module match

# ==========================================
# Commandes personnalisées (optionnel)
# ==========================================
# Valgrind (si disponible)
find_program(VALGRIND valgrind)
if(VALGRIND)
    add_custom_target(valgrind-part1-player
        COMMAND ${VALGRIND} --leak-check=full --error-exitcode=1 ./test_part1_player
        DEPENDS test_part1_player
        COMMENT "Vérification mémoire avec Valgrind (player.c)"
    )
    
    add_custom_target(valgrind-part1-array
        COMMAND ${VALGRIND} --leak-check=full --error-exitcode=1 ./test_part1_array
        DEPENDS test_part1_array
        COMMENT "Vérification mémoire avec Valgrind (array-utils.c)"
    )
endif()
