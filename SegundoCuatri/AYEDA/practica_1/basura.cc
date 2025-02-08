
#include <iostream>
#include <vector>

int main () {

  int numero = 1234;
  std::vector<int> digitos;
  while (numero > 0) {
    digitos.push_back(numero % 10);
    numero /= 10;
  }

  for (int i : digitos) {
    std::cout << i << " ";
  }
}


/**  
function ggit() {
    # Verificar si se proporcionó un mensaje de commit
    if [[ -z "${1}" ]]; then
        echo -e "\n[ERROR] Debes proporcionar un mensaje para el commit"
        echo -e "Uso: ggit \"mensaje del commit\"\n"
        return 1
    fi

    # Verificar si estamos en un repositorio git
    if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
        echo -e "\n[ERROR] No estás en un repositorio git\n"
        return 1
    fi

    # Verificar si hay cambios para commitear
    if [[ -z "$(git status --porcelain)" ]]; then
        echo -e "\n[INFO] No hay cambios para commitear\n"
        return 0
    fi

    # Git add
    echo -e "\n[INFO] Ejecutando git add ."
    if ! git add .; then
        echo -e "\n[ERROR] Error al ejecutar git add\n"
        return 1
    fi
    echo -e "[✓] Git add completado con éxito\n"

    # Git commit
    echo -e "[INFO] Ejecutando git commit con mensaje: ${1}"
    if ! git commit -m "${1}"; then
        echo -e "\n[ERROR] Error al ejecutar git commit\n"
        return 1
    fi
    echo -e "[✓] Git commit completado con éxito\n"

    # Verificar si hay una rama remota configurada
    if ! git remote get-url origin >/dev/null 2>&1; then
        echo -e "[ERROR] No hay un repositorio remoto configurado\n"
        return 1
    fi

    # Git push
    echo -e "[INFO] Ejecutando git push"
    if ! git push; then
        echo -e "\n[ERROR] Error al ejecutar git push\n"
        return 1
    fi
    echo -e "[✓] Git push completado con éxito\n"

    # Mostrar estado final
    echo -e "\n[✓] Proceso completado exitosamente"
    echo -e "- Rama actual: $(git branch --show-current)"
    echo -e "- Último commit: $(git log -1 --pretty=format:'%h - %s')\n"
}
*/