#include <stdio.h>
#include <string.h>
#include <ctype.h>

char inp[100];
int curr = 0;

void skipWhitespace() {
    while (inp[curr] == ' ' || inp[curr] == '\t') {
        curr++;
    }
}

int factor() {
    skipWhitespace();
    
    if (inp[curr] == '(') {
        curr++;
        if (expression()) {
            skipWhitespace();
            if (inp[curr] == ')') {
                curr++;
                return 1;
            }
        }
        return 0;
    }
    else if (isalpha(inp[curr]) || inp[curr] == 'i') {  // Variables or identifiers
        curr++;
        return 1;
    }
    else if (isdigit(inp[curr])) {  // Numbers
        while (isdigit(inp[curr])) {
            curr++;
        }
        return 1;
    }
    return 0;
}

int term() {
    if (!factor()) {
        return 0;
    }
    
    skipWhitespace();
    while (inp[curr] == '*' || inp[curr] == '/') {
        curr++;
        if (!factor()) {
            return 0;
        }
        skipWhitespace();
    }
    return 1;
}

int expression() {
    if (!term()) {
        return 0;
    }
    
    skipWhitespace();
    while (inp[curr] == '+' || inp[curr] == '-') {
        curr++;
        if (!term()) {
            return 0;
        }
        skipWhitespace();
    }
    return 1;
}

int main() {
    printf("Enter input expression: ");
    fgets(inp, sizeof(inp), stdin);
    
    // Remove newline character
    inp[strcspn(inp, "\n")] = 0;
    
    int res = expression();
    
    skipWhitespace();
    if (res == 1 && inp[curr] == '\0') {
        printf("Input has been accepted.\n");
    } else {
        printf("Input has been rejected at position %d.\n", curr);
        printf("Error near: %s\n", &inp[curr]);
    }
    
    return 0;
}

// #include <stdio.h>
// #include <string.h>
// // Production rules:
// // E -> iZ
// // Z -> +iZ   |   ε
// char inp[100];
// int len = 0, curr = 0;
// int E();
// int Z();
// int E()
// {
//     int result;
//     if (inp[curr] == 'i')
//     {
//         curr++;
//         result = Z();
//         if (result == 1)
//             return 1;
//         else
//             return -1;
//     }
//     return -1;
// }
// int Z()
// {
//     int result;
//     if (inp[curr] == '+' && inp[curr + 1] == 'i')
//     {
//         curr += 2;
//         result = Z();
//         if (result == 1)
//             return 1;
//     }
//     return 1;
// }
// int main()
// {
//     printf("Enter input:\n");
//     scanf("%s", inp);
//     int res = E();
//     if (res == 1 && curr == strlen(inp))
//         printf("Input has been accepted.\n");
//     else
//         printf("Input has been rejected.\n");
// }

