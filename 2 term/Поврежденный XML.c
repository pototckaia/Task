#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_MAX 1002

char alphaben[] = {'<', '>', '/', 'a', 'b', 'c', 'd', 'e', 'f',
                    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                    'p', 'q', 'r', 's', 't', 'u', 'v', 'x', 'w', 'y', 'z'};

int size_alphaben = 29;

char **stack;
char *teg;

int cmp(char *s1, char *s2) {

}

int check_xml(char *str, int str_len) {


    if (str[0] != '<' && str[str_len] != '>') {
        return 0;
    }

    int i = 0;
    int size_stack = 0;

    while (i < str_len) {
        if (str[i] == '<') {

            int len_teg = 0;
            for (int j = i + 1; j < str_len && str[j] != '>'; j++) {
                if (str[i] == '/' && str[i - 1] != '<')
                    return 0;
                teg[len_teg] = str[j];
                len_teg++;
            }
            if (len_teg == 0)
                return 0;

            teg[len_teg] = '\0';

            if (teg[0] != '/' ) {
                memcpy(stack[size_stack], teg, len_teg + 1);
                size_stack++;
            }else if (size_stack > 0 && len_teg > 1 && !strcmp(stack[size_stack - 1], teg + 1)) {
                size_stack--;
            }
            else {
                return 0;
            }

            i = i + len_teg;
        }
        else if (i + 1 < str_len && str[i] == '>' && str[i + 1] != '<')
            return 0;
        else
            i++;
    }

    return (size_stack == 0);
}

int main() {
    freopen("xml.in", "r", stdin); freopen("xml.out", "w",stdout);

    char *xml_text = (char *) malloc(LEN_MAX * sizeof(char));

    scanf("%s", xml_text);
    int xml_len =  strlen(xml_text);

    teg = (char *) malloc(xml_len * sizeof(char));
    stack = (char **) malloc(xml_len * sizeof(char *));
    for (int i = 0; i < xml_len; i++) {
        stack[i] = (char *) malloc(xml_len * sizeof(char));
    }

    int is_answer = 0;
    for (int i = 0; i < xml_len; i++) {
        char character = xml_text[i];

        for (int j = 0; j < size_alphaben; j++) {
            char c = alphaben[j];
            xml_text[i] = alphaben[j];

            is_answer = check_xml(xml_text, xml_len);

            if (is_answer) {
                break;
            }
        }

        if (is_answer) {
            break;
        }
        xml_text[i] = character;
    }

    printf("%s", xml_text);

    return 0;
}
