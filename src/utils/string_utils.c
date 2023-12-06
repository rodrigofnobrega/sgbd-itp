#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../includes/utils/string_utils.h"

void upperString(char *string) {
    while (*string) {
        *string = toupper(*string);
        string++;
    }
}
