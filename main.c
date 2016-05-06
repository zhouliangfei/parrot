//
//  main.m
//  parrot
//
//  Created by zhouliangfei on 16/5/5.
//  Copyright © 2016年 zhouliangfei. All rights reserved.
//



/*
 l(l|d)* 10
 dd* 11
 + 13
 - 14
 * 15
 / 16
 : 17
 := 18
 < 20
 <> 21
 <= 22
 > 23
 >= 24
 = 25
 ; 26
 ( 27
 ) 28
 //
 begin 1
 if 2
 then 3
 while 4
 do 5
 end 6
 */
#include <stdio.h>
#include <stdlib.h>

/*enum type{
 null,
 string,
 number,
 };*/
/*
 char * keyword[6]={"","","","","",""};*/

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
                    fseek(file, -1, SEEK_CUR);
                    token[i++] = '\0';
                    return 1;
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
                    token[i++] = '\0';
                    return 2;
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
                    return 3;
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
                    return 3;
                }
            }
            return 0;
        }
        //运算
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '&' || c == '|' || c == '!' || c == '<' || c == '=' || c == '>'){
            token[i++] = c;
            //
            char n = '\0';
            if ((n = fgetc(file)) != EOF) {
                if ((n == '=') || (c == '+' && n == '+') || (c == '-' && n == '-') || (c == '<' && (n == '<' || n == '>')) || (c == '>' && n == '>')) {
                    token[i++] = n;
                }else{
                    fseek(file, -1, SEEK_CUR);
                }
            }
            token[i++] = '\0';
            return 4;
        }
        //分隔
        if(c == ':' || c == '.' || c == ';' || c == ',' || c == '#' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}'){
            token[i++] = c;
            token[i++] = '\0';
            return 5;
        }
    }
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
