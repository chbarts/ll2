#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ggets.h"
#include "ll.h"

static ll *dofile(FILE * inf, char *fname, char *pname, ll * head)
{
    ll *tmp;
    int res;
    char *line;

    while ((res = fggets(&line, inf)) == 0) {
        if ((tmp = new_node(strlen(line), line, head)) == NULL) {
            perror("tac: memory error");
            free_all_nodes(free_all_data(head));
            free(line);
            if (stdin != inf)
                fclose(inf);
            exit(EXIT_FAILURE);
        }

        head = tmp;
    }

    if (res > 0) {
        perror("tac: memory error");
        free_all_nodes(free_all_data(head));
        if (stdin != inf)
            fclose(inf);
        exit(EXIT_FAILURE);
    } else if (ferror(inf)) {
        fprintf(stderr, "tac: file error on %s: %s\n", fname,
                strerror(errno));
    }

    return head;
}

static void *print(int num, void *data)
{
    char *line = ((char *) data);

    puts(line);

    return data;
}

static void *nprint(int num, void *data)
{
    char *line = ((char *) data);

    printf("%d %s\n", num, line);

    return data;
}

int main(int argc, char *argv[])
{
    FILE *inf;
    ll *lst = NULL;
    int i = 1, n = 0;

    if (1 == argc) {
        lst = dofile(stdin, "stdin", argv[0], lst);
    } else if (!strcmp(argv[1], "-n")) {
        n = 1;
        i = 2;
    } else if (!strcmp(argv[1], "--")) {
        i = 2;
    }

    for (; i < argc; i++) {
        if ((inf = fopen(argv[i], "rb")) == NULL) {
            fprintf(stderr, "tac: file error on %s: %s\n", argv[i],
                    strerror(errno));
            continue;
        }

        lst = dofile(inf, argv[i], argv[0], lst);

        fclose(inf);
    }

    if (1 == n) {
        lst = map(lst, nprint);
    } else {
        lst = map(lst, print);
    }

    free_all_nodes(free_all_data(lst));

    return 0;
}
