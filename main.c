//
//  main.m
//  parrot
//
//  Created by zhouliangfei on 16/5/5.
//  Copyright © 2016年 zhouliangfei. All rights reserved.
//

#include <stdio.h>

//词法分析
int scanner(FILE * file, char * token){
    int i = 0;
    char c = '\0';
    while((c = fgetc(file)) != EOF){
        //空白
        if ((c == ' ' || c == '\n' || c == '\r')) {
            continue;
        }
        //注释
        if (c == '/') {
            char n = '\0';
            if ((n = fgetc(file)) != EOF) {
                if (n == '/') {
                    while((n = fgetc(file)) != EOF){
                        if (n == '\n') {
                            break;
                        }
                    }
                    continue;
                }
                if (n == '*') {
                    char p = '\0';
                    while((n = fgetc(file)) != EOF){
                        if (p == '*' && n == '/') {
                            break;
                        }
                        p = n;
                    }
                    continue;
                }
            }
            fseek(file, -1, SEEK_CUR);
        }
        //标识
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')){
            token[i++] = c;
            while((c = fgetc(file)) != EOF){
                if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_')){
                    token[i++] = c;
                }else{
                    token[i++] = '\0';
                    fseek(file, -1, SEEK_CUR);
                    return 1;
                }
            }
            return 0;
        }
        //文本
        if(c == '\''){
            token[i++] = c;
            while((c = fgetc(file)) != EOF){
                token[i++] = c;
                if (c == '\\') {
                    int n = 0;
                    while (n < 2 && (c = fgetc(file)) != EOF) {
                        token[i++] = c;
                        n++;
                    }
                }
                if(c == '\''){
                    token[i++] = '\0';
                    return 2;
                }
            }
            return 0;
        }
        if(c == '"'){
            token[i++] = c;
            while((c = fgetc(file)) != EOF){
                token[i++] = c;
                if (c == '\\') {
                    int n = 0;
                    while (n < 2 && (c = fgetc(file)) != EOF) {
                        token[i++] = c;
                        n++;
                    }
                }
                if(c == '"'){
                    token[i++] = '\0';
                    return 2;
                }
            }
            return 0;
        }
        //数字
        if((c >= '0' && c <= '9')){
            token[i++] = c;
            //
            int isfloat = 0;
            while((c = fgetc(file)) != EOF){
                if((c >= '0' && c <= '9') || (isfloat == 0 && c == '.')){
                    token[i++] = c;
                    if ((isfloat == 0 && c == '.')) {
                        isfloat = 1;
                    }
                }else{
                    fseek(file, -1, SEEK_CUR);
                    break;
                }
            }
            token[i++] = '\0';
            return 3;
        }
        //分隔
        if(c == '('){
            token[i++] = c;
            token[i++] = '\0';
            return 4;
        }
        if(c == ')'){
            token[i++] = c;
            token[i++] = '\0';
            return 5;
        }
        if(c == '['){
            token[i++] = c;
            token[i++] = '\0';
            return 6;
        }
        if(c == ']'){
            token[i++] = c;
            token[i++] = '\0';
            return 7;
        }
        if(c == '{'){
            token[i++] = c;
            token[i++] = '\0';
            return 8;
        }
        if(c == '}'){
            token[i++] = c;
            token[i++] = '\0';
            return 9;
        }
        if(c == '?'){
            token[i++] = c;
            token[i++] = '\0';
            return 10;
        }
        if(c == ':'){
            token[i++] = c;
            token[i++] = '\0';
            return 11;
        }
        if(c == ','){
            token[i++] = c;
            token[i++] = '\0';
            return 12;
        }
        if(c == ';'){
            token[i++] = c;
            token[i++] = '\0';
            return 13;
        }
        if(c == '.'){
            token[i++] = c;
            token[i++] = '\0';
            return 14;
        }
        if(c == '~'){
            token[i++] = c;
            token[i++] = '\0';
            return 15;
        }
        if(c == '@'){
            token[i++] = c;
            token[i++] = '\0';
            return 16;
        }
        if(c == '#'){
            token[i++] = c;
            token[i++] = '\0';
            return 17;
        }
        if(c == '$'){
            token[i++] = c;
            token[i++] = '\0';
            return 18;
        }
        //运算
        if(c == '+'){
            token[i++] = c;
            if ((c = fgetc(file)) != EOF) {
                if (c == '=') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 31;
                }
                if (c == '+') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 43;
                }
                fseek(file, -1, SEEK_CUR);
            }
            token[i++] = '\0';
            return 19;
        }
        if(c == '-'){
            token[i++] = c;
            if ((c = fgetc(file)) != EOF) {
                if (c == '=') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 32;
                }
                if (c == '-') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 44;
                }
                fseek(file, -1, SEEK_CUR);
            }
            token[i++] = '\0';
            return 20;
        }
        if(c == '*'){
            token[i++] = c;
            if ((c = fgetc(file)) != EOF) {
                if (c == '=') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 33;
                }
                fseek(file, -1, SEEK_CUR);
            }
            token[i++] = '\0';
            return 21;
        }
        if(c == '/'){
            token[i++] = c;
            if ((c = fgetc(file)) != EOF) {
                if (c == '=') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 34;
                }
                fseek(file, -1, SEEK_CUR);
            }
            token[i++] = '\0';
            return 22;
        }
        if(c == '%'){
            token[i++] = c;
            if ((c = fgetc(file)) != EOF) {
                if (c == '=') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 35;
                }
                fseek(file, -1, SEEK_CUR);
            }
            token[i++] = '\0';
            return 23;
        }
        if(c == '^'){
            token[i++] = c;
            if ((c = fgetc(file)) != EOF) {
                if (c == '=') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 36;
                }
                fseek(file, -1, SEEK_CUR);
            }
            token[i++] = '\0';
            return 24;
        }
        if(c == '&'){
            token[i++] = c;
            if ((c = fgetc(file)) != EOF) {
                if (c == '=') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 37;
                }
                if (c == '&') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 45;
                }
                fseek(file, -1, SEEK_CUR);
            }
            token[i++] = '\0';
            return 25;
        }
        if(c == '|'){
            token[i++] = c;
            if ((c = fgetc(file)) != EOF) {
                if (c == '=') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 38;
                }
                if (c == '|') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 46;
                }
                fseek(file, -1, SEEK_CUR);
            }
            token[i++] = '\0';
            return 26;
        }
        if(c == '!'){
            token[i++] = c;
            if ((c = fgetc(file)) != EOF) {
                if (c == '=') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 39;
                }
                fseek(file, -1, SEEK_CUR);
            }
            token[i++] = '\0';
            return 27;
        }
        if(c == '<'){
            token[i++] = c;
            if ((c = fgetc(file)) != EOF) {
                if (c == '=') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 40;
                }
                if (c == '<') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 47;
                }
                fseek(file, -1, SEEK_CUR);
            }
            token[i++] = '\0';
            return 28;
        }
        if(c == '>'){
            token[i++] = c;
            if ((c = fgetc(file)) != EOF) {
                if (c == '=') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 41;
                }
                if (c == '>') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 48;
                }
                fseek(file, -1, SEEK_CUR);
            }
            token[i++] = '\0';
            return 29;
        }
        if(c == '='){
            token[i++] = c;
            if ((c = fgetc(file)) != EOF) {
                if (c == '=') {
                    token[i++] = c;
                    token[i++] = '\0';
                    return 42;
                }
                fseek(file, -1, SEEK_CUR);
            }
            token[i++] = '\0';
            return 30;
        }
    }
    return 0;
}
//语法分析[语法分析的任务是在词法分析的基础上将单词序列组合成各类语法短语]
int parser(char * token){
    
    return 0;
}
//
int main(int argc, char * argv[]) {
    FILE * file = fopen("main.c", "r");
    if(file){
        int type;
        char token[0xFFFF];
        while ((type = scanner(file, (char *)&token))) {
            printf("%s\t\t\t%d\n", token, type);
        };
        fclose(file);
    }
    return 0;
}
