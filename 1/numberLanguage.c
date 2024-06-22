#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(){
    int n;
    scanf("%d", &n);

    int msgSize;
    char msgChar[msgSize];
    for(int i = 0; i < n; i++){
        scanf("%d", &msgSize);
        for(int j = 0; j < msgSize; j++){
            scanf("%c", msgChar[i]);
        }
    }


    return 0;
}