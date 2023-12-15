//
// Created by letewr on 09.12.23.
//

#include "loc.h"

int main() {
    const char *splitters = ".?;";
    int expression;
    int sentence_number = 0;
    printf("Course work for option 4.9, created by Savva Starkov.\n");
    scanf("%d\n",&expression);
    switch (expression) {
        case 0:
            print_Func(split_text(get_text_Input(), &sentence_number, splitters), &sentence_number);
            break;
        case 1:{
            char** text = split_text(get_text_Input(), &sentence_number, splitters);
            robin_to_imBatman(text,&sentence_number);
            print_Func(text, &sentence_number);
            break;
        }
        case 3:
            print_Func(sum_of_numbers_sort(split_text(get_text_Input(), &sentence_number, splitters), &sentence_number),
                       &sentence_number);
            break;
        case 2:
            print_Func(
                    split_to_number_Sort(split_text(get_text_Input(), &sentence_number, splitters), &sentence_number),
                    &sentence_number);
            break;
        case 4:
            print_Func(if_Vowel(split_text(get_text_Input(), &sentence_number, splitters), &sentence_number),
                       &sentence_number);
            break;
        case 5:
            printf("1 - Заменить в тексте подстроки “Robin” (могут быть внутри слова) на подстроку “I am Batman”.\n"
                   "2 - Отсортировать предложения по увеличению количества запятых в предложении.\n"
                   "3 - Удалить все предложения в которых сумма цифр в предложении равняется 13.\n"
                   "4 - Вывести все предложения в которых первое слово начинается с гласной буквы или цифры.\n"
                   "5 - Вывод справки о функциях, которые реализует программа.\n");
            break;
        default:
            fprintf(stderr,"Неправильный выбор функции!\n");
            break;
    }

    return 0;
}


char **split_text(char *text, int *num_sentences, const char *splitters) {
    int count_sentences = 0;
    int end_index = 0;
    char **splitted_text = malloc(sizeof(char *));

    for (int i = 0; i < (int) strlen(text); i++) {
        if (strchr(splitters, text[i]) != NULL) {
            count_sentences++;

            splitted_text = realloc(splitted_text, count_sentences * sizeof(char *));
            splitted_text[count_sentences - 1] = malloc((end_index + 2) * sizeof(char));

            int chr_counter = 0;
            for (int j = end_index; j >= 0; j--) {
                splitted_text[count_sentences - 1][chr_counter++] = text[i - j];
            }
            splitted_text[count_sentences - 1][chr_counter] = '\0';
            remove_lead_Spaces(splitted_text[count_sentences - 1]);
            end_index = 0;
            continue;
        }
        end_index++;
    }

    *num_sentences = count_sentences;
    return splitted_text;
}

char *get_text_Input() {
    char* text = malloc(sizeof(char));
    int size = 0;
    char ch;
    while (strstr(text, "\n\n") == NULL) {
        ch = getchar();
        text[size++] = ch;
        text = (char *) realloc(text, (sizeof(char) * (size+2)));

    }
    text[size - 2] = '\0';
    return text;
}

void remove_lead_Spaces(char *str) {
    char *start = str;
    while (*start && (*start == ' ' || *start == '\t' || *start == '\n')) {
        start++;
    }
    memmove(str, start, strlen(start) + 1);
}


void print_Func(char **text, int *sentence_number) {
    for (int i = 0; i < (*sentence_number); i++) {
        printf("%s", text[i]);
        free(text[i]);
    }
    printf("\n");
}

char **if_Vowel(char **text, int *sentence_number) {
    int index = 0;
    char **new_text = malloc(sizeof(text));
    char *vowel = "aeouyAEOUY1234567890";

    for (int i = 0; i <= (*sentence_number) - 2; i++) {
        remove_lead_Spaces(text[i]);
        if (strchr(vowel, text[i][0]) != NULL) {
            new_text[index] = text[i];
            index++;
        }
    }
    *sentence_number = index;
    return new_text;
}


int comp_num_sort (const void *a, const void *b){
    char* *sentenceA = (char**)(a);
    char* *sentenceB = (char**) b;
    int counterA = 0;
    int counterB = 0;
    for(int i = 0; i < strlen(*sentenceA);i++){
        if ((*sentenceA)[i]== ','){
            counterA++;
        }
    }
    for(int i = 0; i < strlen(*sentenceB);i++){
        if ((*sentenceB)[i]== ','){
            counterB++;
        }
    }
    return counterA - counterB;
}

char **split_to_number_Sort(char **text, int *sentence_number){
    qsort(text,*sentence_number,sizeof(char*), comp_num_sort);
    return text;
}



char** sum_of_numbers_sort(char** text, int* sentence_number){
    for(int i=0;i<*sentence_number;i++){
        char* temp = text[i];
        int sum=0;
        for(int j=0;j<strlen(temp);j++){
            if(isdigit(temp[j])){
                sum+=temp[j]-'0';
            }
        }
        if(sum==13){
            free(text[i]);
            for(int k=i;k<(*sentence_number);k++){
                text[k]=text[k+1];
            }
            (*sentence_number)--;
        }
    }
    return text;


}

void robin_to_imBatman(char** text,int* sentence_number){

    for(int i = 0;i < (*sentence_number);i++){
        char* temp = text[i];
        char* findindex = strstr(temp, ROBIN);;
        size_t index = 0;
        while(findindex!= NULL ){
            char* new_char = calloc((strlen(temp) + SIZEBATMAN),sizeof(char));
            index = findindex-temp;
            size_t iterator = 0;
            while(iterator < index){
                new_char[iterator] = temp[iterator];
                iterator++;
            }
            strcat(new_char,BATMAN);
            iterator = SIZEBATMAN + iterator;
            index  = index  + SIZEROBIN-1;
            while(index < strlen(temp)){
                new_char[iterator] = temp[index];
                iterator++;
                index++;
            }
            text[i] = new_char;
            temp = text[i];
            findindex = strstr(temp, ROBIN);;
        }
    }

}



//char** sum_of_numbers_sort(char** text, int* sentence_number){
//    int sen_num = *sentence_number;
//    int num_to_del = 0;
//    for(int i = 0; i < (*sentence_number);i++){
//        int sum = 0;
//        char* temp_string = text[i];
//        for( int j = 0 ; j < strlen(temp_string);j++){
//            if((isdigit((int)(temp_string[j]))) != NULL){
//                sum = sum + ((int)(temp_string[j]));
//            }
//            if ((sum == 13)&&((strlen(temp_string)) == j+1)){
//                free(text[i]);
//                text[i] = calloc(sizeof(text[i]), strlen(text[i]));
//                text[i][0] ='D';
//                text[i][1] ='E';
//                text[i][2] ='L';
//                num_to_del++;
//            }
//        }
//
//    }
//    int i = 0;
//    while (num_to_del != 0){
//        if(strstr(text[i],"DEL")!=NULL){
//            int index_to_move= i;
//            sen_num--;
//            num_to_del--;
//            while(index_to_move<sen_num){
//                text[index_to_move] = text[index_to_move+1];
//                index_to_move++;
//            }
//
//        }
//        i++;
//    }
//    (*sentence_number) = (*sentence_number) - num_to_del;
//    return text;
//}

