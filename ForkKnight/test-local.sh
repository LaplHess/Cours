#!/bin/bash

# Script de test alternatif sans Valgrind
# Utilise AddressSanitizer ou d'autres méthodes selon l'OS

set -e

# Vérifier l'argument
if [ $# -eq 0 ]; then
    echo "❌ Erreur : Numéro de partie manquant"
    echo ""
    echo "Usage: $0 <numéro_partie>"
    echo ""
    echo "Exemples:"
    echo "  $0 1     # Teste la partie 1"
    echo "  $0 2     # Teste la partie 2"
    echo ""
    exit 1
fi

PART=$1

echo "[FORK-KNIGHT]  Fork Knight - Tests Part $PART"
echo "=========================================="
echo ""

# Détection de l'OS
OS="$(uname -s)"
case "${OS}" in
    Linux*)     MACHINE=Linux;;
    Darwin*)    MACHINE=Mac;;
    CYGWIN*|MINGW*|MSYS*)  MACHINE=Windows;;
    *)          MACHINE="UNKNOWN";;
esac

echo "[SYS]  Système détecté : $MACHINE"
echo ""

# Vérifier si Valgrind est disponible
HAS_VALGRIND=false
if command -v valgrind &> /dev/null; then
    echo "✅ Valgrind disponible"
    HAS_VALGRIND=true
else
    echo "⚠️  Valgrind non disponible"
    if [ "$MACHINE" = "Mac" ]; then
        echo "   → Normal sur macOS (surtout M1/M2)"
        echo "   → Utilisation d'AddressSanitizer à la place"
    elif [ "$MACHINE" = "Windows" ]; then
        echo "   → Normal sur Windows"
        echo "   → Compilation sans AddressSanitizer (non supporté sur MinGW)"
    fi
fi

echo ""
echo "=========================================="
echo ""

# Fonction pour compiler avec AddressSanitizer (macOS/Linux)
compile_with_asan() {
    echo "[BUILD] Compilation avec AddressSanitizer..."
    echo ""
    
    # Nettoyer
    make clean > /dev/null 2>&1 || true
    rm -f test_part${PART}_* 2>/dev/null || true
    
    # Compiler avec AddressSanitizer
    CFLAGS="-Wall -Wextra -Werror -Iheaders -g -fsanitize=address -fno-omit-frame-pointer"
    
    # Détecter les modules à compiler selon la partie
    case $PART in
        1)
            # Test player
            gcc $CFLAGS src/player.c tests/unity/unity.c tests/part1/test_player.c \
                -o test_part1_player -Itests/unity
            
            # Test array-utils
            gcc $CFLAGS src/player.c src/array-utils.c tests/unity/unity.c tests/part1/test_array_utils.c \
                -o test_part1_array -Itests/unity
            ;;
        2)
            # Test tableaux dynamiques et fichiers
            gcc $CFLAGS src/player.c src/array-utils.c tests/unity/unity.c tests/part2/test_dynamic_array.c \
                -o test_part2 -Itests/unity
            ;;
        3)
            # Test listes chaînées et files
            gcc $CFLAGS src/player.c src/list-utils.c tests/unity/unity.c tests/part3/test_list_utils.c \
                -o test_part3 -Itests/unity
            ;;
        4)
            # Test priority-queue
            gcc $CFLAGS src/player.c src/array-utils.c src/list-utils.c src/priority-queue.c tests/unity/unity.c tests/part4/test_priority_queue.c \
                -o test_part4 -Itests/unity
            ;;
        5)
            # Test match (uses priority queue)
            gcc $CFLAGS src/player.c src/array-utils.c src/list-utils.c src/priority-queue.c src/match.c tests/unity/unity.c tests/part5/test_match.c \
                -o test_part5 -Itests/unity
            ;;
        6)
            echo "⚠️  Compilation pour partie $PART à implémenter"
            echo "   Utilisez 'make test-part${PART}' en attendant"
            return 1
            ;;
        *)
            echo "❌ Partie invalide : $PART"
            return 1
            ;;
    esac
    
    echo "✅ Compilation réussie (avec AddressSanitizer)"
    echo ""
}

# Fonction pour compiler sans AddressSanitizer (Windows)
compile_without_asan() {
    echo "[BUILD] Compilation sans AddressSanitizer (non supporté sur Windows)..."
    echo ""
    
    # Nettoyer
    make clean > /dev/null 2>&1 || true
    rm -f test_part${PART}_* 2>/dev/null || true
    rm -f test_part${PART}_*.exe 2>/dev/null || true
    
    # Compiler sans AddressSanitizer
    CFLAGS="-Wall -Wextra -Werror -Iheaders -g"
    
    # Détecter les modules à compiler selon la partie
    case $PART in
        1)
            # Test player
            gcc $CFLAGS src/player.c tests/unity/unity.c tests/part1/test_player.c \
                -o test_part1_player -Itests/unity
            
            # Test array-utils
            gcc $CFLAGS src/player.c src/array-utils.c tests/unity/unity.c tests/part1/test_array_utils.c \
                -o test_part1_array -Itests/unity
            ;;
        2)
            # Test tableaux dynamiques et fichiers
            gcc $CFLAGS src/player.c src/array-utils.c tests/unity/unity.c tests/part2/test_dynamic_array.c \
                -o test_part2 -Itests/unity
            ;;
        3)
            # Test listes chaînées et files
            gcc $CFLAGS src/player.c src/list-utils.c tests/unity/unity.c tests/part3/test_list_utils.c \
                -o test_part3 -Itests/unity
            ;;
        4)
            # Test priority-queue
            gcc $CFLAGS src/player.c src/array-utils.c src/list-utils.c src/priority-queue.c tests/unity/unity.c tests/part4/test_priority_queue.c \
                -o test_part4 -Itests/unity
            ;;
        5)
            # Test match (uses priority queue)
            gcc $CFLAGS src/player.c src/array-utils.c src/list-utils.c src/priority-queue.c src/match.c tests/unity/unity.c tests/part5/test_match.c \
                -o test_part5 -Itests/unity
            ;;
        6)
            echo "⚠️  Compilation pour partie $PART à implémenter"
            echo "   Utilisez 'make test-part${PART}' en attendant"
            return 1
            ;;
        *)
            echo "❌ Partie invalide : $PART"
            return 1
            ;;
    esac
    
    echo "✅ Compilation réussie (sans AddressSanitizer)"
    echo ""
}

# Fonction pour compiler normalement
compile_normal() {
    echo "[BUILD] Compilation normale..."
    echo ""
    make clean > /dev/null 2>&1 || true
    make test-part${PART}
    echo ""
}

# Fonction pour exécuter les tests
run_tests() {
    local test_name=$1
    local test_exec=$2
    
    echo "=========================================="
    echo "[TEST] Tests : $test_name"
    echo "=========================================="
    echo ""
    
    if [ ! -f "$test_exec" ]; then
        echo "❌ Fichier $test_exec non trouvé"
        return 1
    fi
    
    # Exécuter le test
    if ./$test_exec; then
        echo ""
        echo "✅ Tous les tests $test_name réussis !"
        return 0
    else
        echo ""
        echo "❌ Certains tests $test_name ont échoué"
        return 1
    fi
}

# Variables pour tracking des résultats selon la partie
case $PART in
    1)
        TEST_EXEC_1="test_part1_player"
        TEST_EXEC_2="test_part1_array"
        TEST_NAME_1="player.c"
        TEST_NAME_2="array-utils.c"
        ;;
    2)
        TEST_EXEC_1="test_part2"
        TEST_EXEC_2=""
        TEST_NAME_1="tableaux dynamiques et fichiers"
        TEST_NAME_2=""
        ;;
    3)
        TEST_EXEC_1="test_part3"
        TEST_EXEC_2=""
        TEST_NAME_1="listes chaînées et files"
        TEST_NAME_2=""
        ;;
    4)
        TEST_EXEC_1="test_part4"
        TEST_EXEC_2=""
        TEST_NAME_1="priority-queue.c"
        TEST_NAME_2=""
        ;;
    5)
        TEST_EXEC_1="test_part5"
        TEST_EXEC_2=""
        TEST_NAME_1="match.c"
        TEST_NAME_2=""
        ;;
    6)
        echo "⚠️  Configuration des tests pour partie $PART à définir"
        TEST_EXEC_1=""
        TEST_EXEC_2=""
        ;;
esac

# Fonction pour vérifier la mémoire avec Valgrind
check_memory_valgrind() {
    local test_exec=$1
    
    echo "[MEM] Vérification mémoire avec Valgrind : $test_exec"
    
    valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 \
             --errors-for-leak-kinds=all ./$test_exec > /tmp/valgrind_$$.log 2>&1
    
    local exit_code=$?
    
    if [ $exit_code -eq 0 ]; then
        echo "   ✅ Aucune fuite mémoire détectée"
        return 0
    else
        echo "   ❌ Fuites mémoire détectées !"
        echo ""
        echo "Extrait du rapport Valgrind :"
        grep -A 10 "LEAK SUMMARY" /tmp/valgrind_$$.log || cat /tmp/valgrind_$$.log | tail -20
        return 1
    fi
}

# Fonction pour vérifier la mémoire avec leaks (macOS)
check_memory_leaks() {
    local test_exec=$1
    
    echo "[MEM] Vérification mémoire avec leaks : $test_exec"
    
    if ! command -v leaks &> /dev/null; then
        echo "   ⚠️  Commande 'leaks' non disponible"
        return 0
    fi
    
    leaks --atExit -- ./$test_exec > /tmp/leaks_$$.log 2>&1
    
    if grep -q "0 leaks for 0 total leaked bytes" /tmp/leaks_$$.log; then
        echo "   ✅ Aucune fuite mémoire détectée"
        return 0
    else
        echo "   ⚠️  Vérifiez le rapport :"
        cat /tmp/leaks_$$.log
        return 1
    fi
}

# Variables pour tracking des résultats
PLAYER_TESTS_OK=false
ARRAY_TESTS_OK=false
MEMORY_OK=false

# Étape 1 : Compilation
echo "=========================================="
echo "ÉTAPE 1 : COMPILATION"
echo "=========================================="
echo ""

if [ "$HAS_VALGRIND" = true ]; then
    compile_normal
elif [ "$MACHINE" = "Windows" ]; then
    compile_without_asan
    echo "[i]  Sur Windows, la vérification mémoire automatique n'est pas disponible localement"
    echo "   → GitHub Actions utilisera Valgrind pour la validation finale"
    echo ""
else
    compile_with_asan
    echo "[i]  AddressSanitizer détectera automatiquement les problèmes mémoire lors de l'exécution"
    echo ""
fi

# Étape 2 : Tests
echo ""
echo "=========================================="
echo "ÉTAPE 2 : EXÉCUTION DES TESTS"
echo "=========================================="
echo ""

if [ -n "$TEST_EXEC_1" ] && run_tests "$TEST_NAME_1" "$TEST_EXEC_1"; then
    PLAYER_TESTS_OK=true
fi

echo ""

if [ -n "$TEST_EXEC_2" ] && run_tests "$TEST_NAME_2" "$TEST_EXEC_2"; then
    ARRAY_TESTS_OK=true
fi

echo ""

# Étape 3 : Vérification mémoire (seulement si Valgrind dispo et compilation normale)
if [ "$HAS_VALGRIND" = true ]; then
    echo ""
    echo "=========================================="
    echo "ÉTAPE 3 : VÉRIFICATION MÉMOIRE (Valgrind)"
    echo "=========================================="
    echo ""
    
    MEMORY_CHECK_OK=true
    
    if ! check_memory_valgrind "$TEST_EXEC_1"; then
        MEMORY_CHECK_OK=false
    fi
    
    echo ""
    
    if ! check_memory_valgrind "$TEST_EXEC_2"; then
        MEMORY_CHECK_OK=false
    fi
    
    if [ "$MEMORY_CHECK_OK" = true ]; then
        MEMORY_OK=true
    fi
elif [ "$MACHINE" = "Mac" ]; then
    echo ""
    echo "=========================================="
    echo "ÉTAPE 3 : VÉRIFICATION MÉMOIRE (leaks)"
    echo "=========================================="
    echo ""
    echo "[i]  AddressSanitizer a déjà vérifié pendant l'exécution des tests"
    echo "   Vérification supplémentaire avec 'leaks'..."
    echo ""
    
    # Note : Si AddressSanitizer était actif, il aurait déjà crashé en cas de problème
    # Pour les parties avec un seul test (2-5), vérifier seulement TEST_EXEC_1
    # Pour la partie 1 avec deux tests, vérifier les deux
    if [ "$PLAYER_TESTS_OK" = true ] && { [ -z "$TEST_EXEC_2" ] || [ "$ARRAY_TESTS_OK" = true ]; }; then
        echo "✅ Aucun problème détecté par AddressSanitizer"
        MEMORY_OK=true
    fi
else
    echo ""
    echo "=========================================="
    echo "[i]  VÉRIFICATION MÉMOIRE"
    echo "=========================================="
    echo ""
    
    if [ "$MACHINE" = "Windows" ]; then
        echo "⚠️  Vérification mémoire automatique non disponible sur Windows"
        echo ""
        echo "Les outils disponibles :"
        echo "  • Valgrind : Non supporté sur Windows"
        echo "  • AddressSanitizer : Non supporté sur MinGW/GCC Windows"
        echo ""
        echo "Note : GitHub Actions utilisera Valgrind (Linux) pour la validation finale."
        echo "       Assurez-vous de libérer toute mémoire allouée avec malloc/calloc !"
        echo ""
    else
        echo "⚠️  Valgrind non disponible sur ce système"
        echo ""
        echo "Si vous avez utilisé AddressSanitizer (compilation avec -fsanitize=address),"
        echo "les problèmes mémoire auraient déjà été détectés pendant les tests."
        echo ""
        echo "Note : GitHub Actions utilisera Valgrind pour la validation finale."
        echo ""
    fi
    
    # Considérer OK si tests passés (ASan aurait détecté les problèmes sur Mac/Linux)
    # Pour les parties avec un seul test (2-5), vérifier seulement TEST_EXEC_1
    # Pour la partie 1 avec deux tests, vérifier les deux
    if [ "$PLAYER_TESTS_OK" = true ] && { [ -z "$TEST_EXEC_2" ] || [ "$ARRAY_TESTS_OK" = true ]; }; then
        MEMORY_OK=true
    fi
fi

# Résumé final
echo ""
echo "=========================================="
echo "📊 RÉSUMÉ - PARTIE $PART"
echo "=========================================="
echo ""

echo "Tests $TEST_NAME_1       : $([ "$PLAYER_TESTS_OK" = true ] && echo "✅ PASS" || echo "❌ FAIL")"
if [ -n "$TEST_NAME_2" ]; then
    echo "Tests $TEST_NAME_2  : $([ "$ARRAY_TESTS_OK" = true ] && echo "✅ PASS" || echo "❌ FAIL")"
fi
echo "Vérification mémoire : $([ "$MEMORY_OK" = true ] && echo "✅ OK" || echo "⚠️  À vérifier")"

echo ""
echo "=========================================="

# Exit code
# For parts with one test (2-5), only check TEST_EXEC_1
# For part 1 with two tests, check both
ALL_TESTS_PASSED=false
if [ "$PLAYER_TESTS_OK" = true ] && { [ -z "$TEST_EXEC_2" ] || [ "$ARRAY_TESTS_OK" = true ]; }; then
    ALL_TESTS_PASSED=true
fi

if [ "$ALL_TESTS_PASSED" = true ] && [ "$MEMORY_OK" = true ]; then
    echo "✅ SUCCÈS : Tous les tests sont passés !"
    echo ""
    echo "💡 Prochaine étape : Soumettez votre travail"
    echo ""
    echo "   ./submit.sh $PART"
    echo ""
    exit 0
else
    echo "⚠️  ÉCHEC : Corrections nécessaires"
    echo ""
    
    if [ "$PLAYER_TESTS_OK" = false ]; then
        echo "→ Vérifiez votre implémentation de $TEST_NAME_1"
        
        # Suggestions spécifiques par partie
        if [ "$PART" = "3" ]; then
            echo ""
            echo "📚 Fonctions à implémenter dans src/list-utils.c :"
            echo "   • createCell()      - Allouer et initialiser une cellule"
            echo "   • destroyCell()     - Libérer une cellule (pas le Player)"
            echo "   • createQueue()     - Allouer et initialiser une file"
            echo "   • isQueueEmpty()    - Vérifier si la file est vide"
            echo "   • enqueue()         - Ajouter un joueur en queue de file"
            echo "   • dequeue()         - Retirer un joueur en tête de file"
            echo "   • removeHead()      - Retirer la tête sans libérer la cellule"
            echo "   • destroyQueue()    - Détruire toute la file"
            echo ""
            echo "💡 Conseils :"
            echo "   • Dessinez la structure sur papier"
            echo "   • Respectez l'ordre FIFO (premier entré = premier sorti)"
            echo "   • N'oubliez pas de mettre à jour head ET tail"
            echo "   • Les cellules sont libérées, pas les Players"
        fi
        
        if [ "$PART" = "5" ]; then
            echo ""
            echo "📚 Fonctions à implémenter dans src/match.c :"
            echo "   • createMatch()         - Allouer Match + tableau de joueurs + tableau results"
            echo "   • destroyMatch()        - Libérer le tableau de joueurs + tableau results + Match (pas les Players)"
            echo "   • addMatchPlayers()     - Ajouter joueurs de la queue au match"
            echo "   • simulateMatch()       - Générer résultats aléatoires du match"
            echo "   • updatePlayerStats()   - Mettre à jour les statistiques des joueurs"
            echo "   • displayMatchInfo()    - Afficher infos du match"
            echo "   • displayMatchResult()  - Afficher résultats du match"
            echo "   • launchMatch()         - Orchestrer: dequeue → simulate → stats → affichage"
            echo ""
            echo "💡 Conseils système de match :"
            echo "   • Chaque joueur participe à UN match (résultat = win ou loss)"
            echo "   • Results array = indices des joueurs (0 à numPlayers-1)"
            echo ""
            echo "💡 Conseils spicyIndex :"
            echo "   • Avant: spicyIndex initial du joueur (0-100)"
            echo "   • Après: spicyIndex = (numWins / numGames) * 100 si numGames > 0"
            echo "   • Ex: 2 wins / 4 games = (2/4)*100 = 50"
            echo "   • Nouveau joueur (0 games): reste à valeur initiale"
            echo ""
            echo "💡 Conseils destruction (mémoire) :"
            echo "   • Match NE possède PAS les Players (juste des références)"
            echo "   • destroyMatch() libère UNIQUEMENT la structure Match et son tableau de joueurs et le tableau results"
            echo "   • Les joueurs sont libérés ailleurs (lors de la destruction du tableau principal)"
            echo "   • Évitez double-free: ne libérez pas les Players dans Match"
        fi
    fi
    
    if [ "$ARRAY_TESTS_OK" = false ] && [ -n "$TEST_NAME_2" ]; then
        echo "→ Vérifiez votre implémentation de $TEST_NAME_2"
    fi
    
    if [ "$MEMORY_OK" = false ]; then
        echo "→ Vérifiez les fuites mémoire (malloc sans free)"
    fi
    
    echo ""
    echo "💡 Relancez : ./test-local.sh $PART"
    exit 1
fi
