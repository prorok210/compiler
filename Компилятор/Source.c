#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

int main() {
    setlocale(LC_ALL, "");
    char command[100];
    char temp_command[100];
    FILE* file;

    // Открытие файла для записи
    file = fopen("C:\\Users\\Владислав\\Desktop\\Кибернетика\\процессор\\бинарник", "w");
    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    fprintf(file, "v2.0 raw\n0000\n");

    printf("Введите команды (для завершения введите 'stop'):\n");


    while (1) {
        char* first_part_command;
        char* second_part_command;
		char* alter_command;
        fgets(command, sizeof(command), stdin); // Чтение строки с консоли
        command[strcspn(command, "\n")] = 0;
        strcpy(temp_command, command);

        alter_command = strchr(temp_command, '*');
		if (alter_command == NULL) {
            first_part_command = strtok(temp_command, " ");
            if (first_part_command != NULL) {
                second_part_command = strtok(NULL, " ");
            }
            else {
                second_part_command = NULL;
            }
		}

        else {
            first_part_command = strtok(temp_command, "*");
            second_part_command = strtok(NULL, "*");
        }
		
		// остановка цикла
        if ((strcmp(first_part_command, "stop") == 0) || (strcmp(first_part_command, "STOP") == 0)) {
            break; 
        }

        // запись массива нулей через *
        if (alter_command != NULL) {
            int flag = 0;
            for (int i = 0; i < strlen(first_part_command); i++) {
				char ch = (first_part_command[i]);
				if (!(isdigit(ch))) {
					flag = 1;
				}
            }
            if (flag == 0) {
                if (strcmp(second_part_command, "0") == 0) {
                    fprintf(file, "%s*%s\n", first_part_command, second_part_command);
                }
                else {
					printf("Вторая часть команды должна быть 0\n");
                }
            }
            else {
                printf("Число нулей должно быть ЧИСЛОМ!\n");
            }
        }
        else if (second_part_command == NULL) {
            // запись данных
            int data_flag = 0;
            for (int i = 0; i < strlen(first_part_command); i++) {
                char ch = (first_part_command[i]);
                if (!(isdigit(ch) || (ch >= 'a' && ch <= 'f'))) {
                    data_flag = 1;
                }
            }
            if (data_flag == 0) {
                if (strlen(first_part_command) == 4){
                    fprintf(file, "%s\n", first_part_command);
                }
                else {
                    printf("недопустимая длинна данных\n");
                }  
                }
            else {
                printf("Недопустимые символы при вводе данных данных\n");
            }
        }


        else if (second_part_command != NULL){
            // проверки адреса 
            if (strlen(second_part_command) != 2) {
                printf("Неверная длинна адреса\n");
            }

            for (int i = 0; i < strlen(second_part_command); i++) {
                char ch = (second_part_command[i]);
                if (!(isdigit(ch) || ( ch >= 'a' && ch <= 'f'))) {
				    printf("Недопустимые символы в адресе\n");
			    }
		    }

            //запись команд в файл
            if ((strcmp(first_part_command, "nop") == 0) || (strcmp(first_part_command, "NOP") == 0)) {
                fprintf(file, "00%s\n", second_part_command); 
            }
            else if ((strcmp(first_part_command, "load") == 0) || ((strcmp(first_part_command, "LOAD") == 0))) {
                fprintf(file, "01%s\n", second_part_command); 
            }
            else if ((strcmp(first_part_command, "storeAX") == 0) || (strcmp(first_part_command, "STOREAX") == 0)) {
                fprintf(file, "02%s\n", second_part_command); 
            }
            else if ((strcmp(first_part_command, "storeML") == 0) || (strcmp(first_part_command, "STOREML") == 0)) {
                fprintf(file, "03%s\n", second_part_command); 
            }
            else if ((strcmp(first_part_command, "storeMH") == 0) || (strcmp(first_part_command, "STOREMH") == 0)) {
                fprintf(file, "04%s\n", second_part_command); 
            }
            else if ((strcmp(first_part_command, "add") == 0) || (strcmp(first_part_command, "ADD") == 0)) {
                fprintf(file, "05%s\n", second_part_command); 
            }
            else if ((strcmp(first_part_command, "sub") == 0) || (strcmp(first_part_command, "SUB") == 0)) {
                fprintf(file, "06%s\n", second_part_command); 
            }
            else if ((strcmp(first_part_command, "dec") == 0) || (strcmp(first_part_command, "DEC") == 0)) {
                fprintf(file, "07%s\n", second_part_command); 
            }
            else if ((strcmp(first_part_command, "inc") == 0) || (strcmp(first_part_command, "INC") == 0)) {
                fprintf(file, "08%s\n", second_part_command); 
            }
            else if ((strcmp(first_part_command, "mul") == 0) || (strcmp(first_part_command, "MUL") == 0)) {
                fprintf(file, "09%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "div") == 0) || (strcmp(first_part_command, "DIV") == 0)) {
                fprintf(file, "0a%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "not") == 0) || (strcmp(first_part_command, "NOT") == 0)) {
                fprintf(file, "0b%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "and") == 0) || (strcmp(first_part_command, "AND") == 0)) {
                fprintf(file, "0c%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "or") == 0) || (strcmp(first_part_command, "OR") == 0)) {
                fprintf(file, "0d%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "xor") == 0) || (strcmp(first_part_command, "XOR") == 0)) {
                fprintf(file, "0e%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "shl") == 0) || (strcmp(first_part_command, "SHL") == 0)) {
                fprintf(file, "0f%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "shr") == 0) || (strcmp(first_part_command, "SHR") == 0)) {
                fprintf(file, "10%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "sar") == 0) || (strcmp(first_part_command, "SAR") == 0)) {
                fprintf(file, "11%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "jmp") == 0) || (strcmp(first_part_command, "JMP") == 0)) {
                fprintf(file, "12%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "jz") == 0) || (strcmp(first_part_command, "JZ") == 0)) {
                fprintf(file, "13%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "jnz") == 0) || (strcmp(first_part_command, "JNZ") == 0)) {
                fprintf(file, "14%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "jc") == 0) || (strcmp(first_part_command, "JC") == 0)) {
                fprintf(file, "15%s\n", second_part_command);
            }
		    else if ((strcmp(first_part_command, "jnc") == 0) || (strcmp(first_part_command, "JNC") == 0)) {
			    fprintf(file, "16%s\n", second_part_command);
		    }
            else if ((strcmp(first_part_command, "jo") == 0) || (strcmp(first_part_command, "JO") == 0)) {
                fprintf(file, "17%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "jno") == 0) || (strcmp(first_part_command, "JNO") == 0)) {
                fprintf(file, "18%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "jg") == 0) || (strcmp(first_part_command, "JG") == 0)) {
                fprintf(file, "19%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "jl") == 0) || (strcmp(first_part_command, "JL") == 0)) {
                fprintf(file, "1a%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "je") == 0) || (strcmp(first_part_command, "JE") == 0)) {
                fprintf(file, "1b%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "jne") == 0) || (strcmp(first_part_command, "JNE") == 0)) {
                fprintf(file, "1c%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "call") == 0) || (strcmp(first_part_command, "CALL") == 0)) {
                fprintf(file, "1d%s\n", second_part_command);
            }
            else if ((strcmp(first_part_command, "ret") == 0) || (strcmp(first_part_command, "RET") == 0)) {
                fprintf(file, "1e%s\n", second_part_command);
            }
        }

        else {
            printf("Неверная команда\n");
        }
    }

    fclose(file); 
    return 0;
}
