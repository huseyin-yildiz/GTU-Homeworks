#include <stdio.h>
#include "hw9_lib.h"
#include "hw9_io.h"

int main() {
    sequence myseq;
    int i;
    for (i = 0; i < 5; ++i)
        myseq.userSizes[i] = 0;
    myseq.first = NULL;
    myseq.last = NULL;
    myseq.size=0;

    main_menu(&myseq);

    return 0;

}
