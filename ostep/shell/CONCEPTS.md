# Concepts difficiles rencontrés en construisant le shell

Récap des points qui ont posé problème pendant l'implémentation, à relire avant LFD210.

## 1. Process et PID

- **Program** = fichier exécutable sur disque (`/bin/ls`)
- **Process** = instance en cours d'exécution d'un program
- **PID** (Process ID) = entier unique attribué par le kernel à chaque process
- Tous les process descendent par fork du process `init` (PID 1, `launchd` sur macOS)
- Le kernel n'est pas un process — c'est la couche en dessous

## 2. Fork et Exec

- `fork()` duplique le process appelant
  - Retourne `0` dans l'enfant
  - Retourne le PID de l'enfant dans le parent
  - Retourne `-1` en cas d'erreur
- `execve()` (et ses variantes `execvp` etc.) **remplace** le contenu du process actuel par celui d'un programme du disque. Le PID reste le même, la table des FDs aussi.
- Pattern standard : `fork` puis `execvp` dans l'enfant. Le parent continue son code.
- `execve` sans `fork` est rare (le process appelant disparaît).

## 3. File descriptors — les trois niveaux

```
Process A : FD table         Process B : FD table
  FD 3 →                       FD 5 →
        ↓                            ↓
    open file description     open file description
       (position, flags)         (position, flags)
        ↓                            ↓
              inode (fichier sur disque)
```

- **File descriptor (FD)** = entier, **par-process**, qui sert de handle
- **File descriptor table** = tableau des FDs ouverts d'un process
- **Open file description (OFD)** = objet kernel partageable (contient la position de lecture)
- **Inode** = le fichier réel (un seul par fichier)

Deux `open()` indépendants sur le même fichier → deux OFDs distinctes → positions indépendantes.

## 4. Héritage des FDs au fork

Lors de `fork()` :
- La table des FDs est **dupliquée** (mêmes numéros chez parent et enfant)
- Les entrées dupliquées **pointent vers les mêmes OFDs**
- Conséquence : si parent lit 10 octets sur un fichier hérité, l'enfant verra la position avancée à 10 (curseur partagé)

C'est ce qui rend les pipes utilisables entre parent et enfant.

## 5. dup et dup2

```c
int dup2(int oldfd, int newfd);
```

- `oldfd` = FD source (déjà ouvert vers la chose qu'on veut)
- `newfd` = FD cible (sera fermé s'il était ouvert, puis fait pointer vers la même OFD que oldfd)

Usage typique pour redirection :
```c
int fd = open("out.txt", O_WRONLY | O_CREAT, 0644);
dup2(fd, STDOUT_FILENO);  // FD 1 pointe maintenant vers out.txt
close(fd);                // hygiène : on n'a plus besoin du handle original
```

Après ça, `printf` (qui écrit sur FD 1) écrit dans `out.txt`.

## 6. Pipes anonymes

```c
int fds[2];
pipe(fds);
// fds[0] = read end
// fds[1] = write end
```

- Boîte FIFO en mémoire kernel
- `pipe()` doit être appelé **avant** `fork()` pour que parent et enfant partagent les extrémités
- Pipe nommé (`mkfifo`) = variante avec un nom dans le filesystem, accessible aux process non apparentés

### Pourquoi le parent DOIT fermer les ends inutilisés

Un pipe a un refcount sur chaque extrémité. `read()` retourne EOF (0) **seulement quand toutes les write ends sont fermées**.

Si le parent garde `fds[1]` ouvert (même sans s'en servir), le reader bloque éternellement après que l'écrivain a fini, parce qu'il existe encore une write end "potentielle".

**Règle d'or** : chaque process ferme tous les ends qu'il n'utilise pas — y compris le parent.

## 7. Pipe + fork pour `cmd1 | cmd2`

```
1. pipe(fds)                                  — crée le pipe
2. fork enfant1                               — sera cmd1
   - dup2(fds[1], STDOUT_FILENO)              — sa stdout → write end
   - close(fds[0]); close(fds[1])             — hygiène
   - execvp("cmd1", ...)
3. fork enfant2                               — sera cmd2
   - dup2(fds[0], STDIN_FILENO)               — sa stdin ← read end
   - close(fds[0]); close(fds[1])             — hygiène
   - execvp("cmd2", ...)
4. parent : close(fds[0]); close(fds[1])     — CRITIQUE
5. parent : waitpid des deux enfants
```

cmd1 et cmd2 sont inchangés — ils écrivent/lisent sur stdout/stdin comme d'habitude. C'est le shell qui maquille FD 1 et FD 0 avant `execvp`.

## 8. Pipes vs fichiers temporaires

Un pipe est meilleur qu'un fichier `/tmp/buffer` parce que :
- Performance : tout en mémoire kernel, pas de disque
- Synchronisation : `read` bloque jusqu'à ce que des données arrivent (vs EOF immédiat sur fichier vide)
- Pas de fichier qui traîne en cas de crash
- Pas de conflit de nom entre instances
- Isolation : invisible aux autres process

## 9. Background et zombies

- `&` à la fin → ne pas attendre l'enfant
- Mais un enfant qui meurt sans `wait` reste **zombie** dans la table des process
- Solution : au début de chaque itération du shell, `waitpid(-1, NULL, WNOHANG)` non-bloquant pour récupérer tous les zombies en attente
  - `-1` = n'importe quel enfant
  - `WNOHANG` = ne bloque pas si aucun n'est prêt

Les notifications "[done]" apparaissent à la prochaine commande, pas en temps réel — pour faire mieux il faudrait `SIGCHLD`.

## 10. Pièges C qu'on a rencontrés

### Initialisation partielle d'un tableau

```c
int fds[2] = {-1};        // fds[0]=-1, fds[1]=0  (pas -1 !)
int fds[2] = {-1, -1};    // les deux à -1
```

Les éléments non spécifiés sont **zero-initialized**, pas remplis avec la dernière valeur.

### Pointer-to-array vs pointer

```c
pid_t (*p)[2]  // pointeur VERS UN TABLEAU de 2 — p[1] saute 8 octets
pid_t *p       // pointeur vers pid_t — p[1] saute 4 octets
```

Pour passer un tableau à une fonction, préférer `pid_t *p` (le tableau decay automatiquement).

### `strcmp` retourne 0 quand égal

```c
if (strcmp(a, "exit") == 0) ...   // BON : test d'égalité
if (strcmp(a, "exit"))            // teste DIFFÉRENT (souvent un bug)
```

### `getline` alloue avec malloc

Déclarer `char *line = NULL; size_t cap;` **avant** la boucle pour que `getline` réutilise le même buffer. `free(line)` une seule fois à la fin.

### EOF sur stdin

`getline` retourne `-1` à la fois en cas d'erreur **et** d'EOF. Distinguer avec `feof(stdin)` :

```c
if (result == -1) {
    if (feof(stdin)) break;     // Ctrl-D normal
    perror("getline"); exit(1); // vraie erreur
}
```

### Builtins doivent vivre dans le process shell

`cd`, `exit`, etc. modifient l'état du shell (répertoire courant, etc.). Si on les exécute via `fork+exec`, le changement disparaît avec l'enfant. Toujours les exécuter directement, jamais dans un fork.

### `fflush(stdout)` après le prompt

stdout est line-buffered sur un terminal — il ne flushe que sur `\n`. Le prompt `"$ "` n'a pas de `\n`, donc il faut un `fflush` explicite sinon le prompt ne s'affiche pas.
