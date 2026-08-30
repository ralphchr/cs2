#include <stdio.h>

typedef enum {
    CHAR,
    INT,
    FLOAT,
    DOUBLE
} VAR_TYPE;

void* log_variable(char* label, void* var_address, VAR_TYPE var_type){
    printf("%s: ", label);

    switch (var_type){
        case CHAR:
            printf("%c", *(char*)var_address);
            break;

        case INT:
            printf("%d", *(int*)var_address);
            break;

        case FLOAT:
            printf("%f", *(float*)var_address);
            break;

        case DOUBLE:
            printf("%lf", *(double*)var_address);
            break;
    }

    printf("\n");
}


void* log_array(char* label, void* arr_address, int array_size, VAR_TYPE var_type){
    printf("%s: ", label);

    switch (var_type){
        case CHAR:
            for (int i = 0; i < array_size; i++){
                if (*((char*)arr_address + i) != '\0')
                    printf("%c", *((char*)arr_address + i));
                else
                    break;
            }
            break;
        case INT:
            for (int i = 0; i < array_size - 1; i++){
                if (i < array_size - 1){
                    printf("%d ", *((int*)arr_address + i));
                }
                else
                    printf("%d", *((int*)arr_address + i));
            }
            break;
        case FLOAT:
            for (int i = 0; i < array_size; i++){
                if (i < array_size - 1){
                    printf("%f ", *((float*)arr_address + i));
                }
                else
                    printf("%f", *((float*)arr_address + i));
            }
            break;
        case DOUBLE:
            for (int i = 0; i < array_size; i++){
                if (i < array_size - 1){
                    printf("%lf ", *((double*)arr_address + i));
                }
                else
                    printf("%lf", *((double*)arr_address + i));
            }
            break;

    }

    printf("\n");

}