#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int forcut = 0;
int findforreplace[1000];
int isundo = 0;
char outputarman[90000];
int witharman = 0;

int forreplace = 0;
createfile(int ldastoor, char dastoor[ldastoor]){
    int slashnum = 0;
    int slash[slashnum];
    for(int i = 23; i < ldastoor; i++){
        if(dastoor[i] == '/'){
            slash[slashnum] = i;
            slashnum++;
        }
    }
    int lpath = ldastoor - 18;
    char path[lpath];
    for(int i = 0; i < lpath + 1; i++){
        path[i] = '\0';
    }
    for(int i = 0; i < lpath; i++){
        path[i] = dastoor[i + 18];
    }
    int exist;
    FILE *fp;
    fp = fopen(path,"r");
    if (!fp)
        exist = 0;
    else{
        fclose(fp);
        exist = 1;
    }
    char strdir[slashnum][100];
    for(int i = 0; i < slashnum; i++){
        for(int j = 0; j < 100; j++){
            strdir[i][j] = '\0';
        }
    }
    for(int i = 0; i < slashnum; i++){
        for(int j = 18; j < slash[i]; j++){
            strdir[i][j - 18] = dastoor[j];
        }
    }
    if(exist == 1){
        printf("This file is already been.\n");
        return 0;
    }
    else{
        for(int i = 0; i < slashnum; i++){
            mkdir(strdir[i]);
        }
        FILE *fp2;
        fp2 = fopen(path,"w");
    }
}


insertstr(int ldastoor, char dastoor[ldastoor]){
    char path[ldastoor - 17];
    int lpath = 0;
    for(int i = 0; i < ldastoor - 17; i++){
        path[i] = '\0';
    }
    for(int i = 0; i < ldastoor - 17; i++){
        if(dastoor[i + 17] == '-'){
            break;
        }
        path[i] = dastoor[i + 17];
        lpath++;
    }
    char mystring[100];
    for(int i = 0; i < 100; i++){
        mystring[i] = '\0';
    }
    char chpath[lpath];
    for(int i = 0; i < lpath; i++){
        chpath[i] = path[i];
    }
    chpath[lpath] = '\0';
    //printf("%d %s %d", lpath, chpath, sizeof(chpath));
    int exist;
    FILE *fp;
    fp = fopen(chpath,"r");
    if (!fp)
        exist = 0;
    else{
        fclose(fp);
        exist = 1;
    }
    if(exist == 0){
        printf("File not found!\n");
        return 0;
    }

    //b undo
    fp = fopen(chpath, "r");
    char myundo[900000];
    for(int i = 0; i < 900000; i++){
        myundo[i] = '\0';
    }
    int myycounter = 0;
    while(!feof(fp)){
        char pch = fgetc(fp);
        myundo[myycounter] = pch;
        myycounter++;
    }
    myundo[myycounter - 1] = '\0';
    fclose(fp);
    fp = fopen("attachment/undo/a.txt", "w");
    for(int i = 0; i < strlen(myundo); i++){
        fputc(myundo[i], fp);
    }
    fclose(fp);

    //e undo


    for(int i = lpath + 23; i < ldastoor; i++){
        if(dastoor[i] == '-' && dastoor[i + 1] == '-'){
            break;
        }
        mystring[i - 23 - lpath] = dastoor[i];
    }
    int line = 0;
    int character = 0;
    int dono = 0;
    for(int i = 0; i < ldastoor; i++){
        if(dastoor[ldastoor - 1 - i] == ':'){
            dono = ldastoor - 1 - i;
            break;
        }
        character += (((int)dastoor[ldastoor - 1 - i]) - 48) * pow(10,i);
    }
    for(int i = 0; i < ldastoor; i++){
        if(dastoor[dono - 1 - i] == ' '){
            break;
        }
        line += (((int)dastoor[dono - 1 - i]) - 48) * pow(10,i);
    }
    //printf("%d %d\n", line, character);
    fclose(fp);
    fp = fopen(chpath,"r");
    char ch;
    int fileline = 0;
    while(!feof(fp)){
        ch = fgetc(fp);
        //printf("%c",ch);
        if(ch == '\n'){
            fileline++;
        }
    }
    fclose(fp);
    fileline++;
    char part1[100000];
    char part2[100000];
    for(int i = 0; i < 100000; i++){
        part1[i] = '\0';
        part2[i] = '\0';
    }
    //printf("%d\n", fileline);
    FILE *fp2;
    fp2 = fopen(chpath,"r");
    int countline = 0;
    int counter1 = 0;
    int counter2 = 0;
    int lcounter = 0;
    while(!feof(fp2)){
        if(countline + 1 < line){
            ch = fgetc(fp2);
            part1[counter1] = ch;
            //printf("%c", ch);
            if(ch == '\n'){
                countline++;
            }
            counter1++;
        }
        else if(countline + 1 == line){
            ch = fgetc(fp2);
            if(lcounter < character){
                part1[counter1] = ch;
                counter1++;
            }
            if(lcounter >= character){
                part2[counter2] = ch;
                counter2++;
            }
            lcounter++;
            if(ch == '\n'){
                countline++;
            }
        }
        else{
            ch = fgetc(fp2);
            part2[counter2] = ch;
            //printf("%c", ch);
            if(ch == '\n'){
                countline++;
            }
            counter2++;
        }
    }
    fclose(fp2);
    FILE *fp3;
    fp3 = fopen(chpath,"w");
    //printf("%s------%s\n", part1, part2);
    //printf("%d %d", strlen(part1), strlen(part2));
    int lmystring = strlen(mystring);
    //printf("%d %c\n", lmystring, mystring[lmystring]);
    fputs(part1, fp3);
    for(int i = 0; i < lmystring; i++){
        if(mystring[i] == '\\' && mystring[i + 1] == 'n' && mystring[i - 1] != '\\'){
            //fputc(mystring[i], fp);
            fputs("\n", fp);
            if(i + 2 < lmystring){
                i += 2;
            }
            else{
                break;
            }
        }

        else if(mystring[i + 1] == '\\' && mystring[i + 2] == 'n' && mystring[i] == '\\'){
            fputs("\\n", fp);
            i += 3;
        }
        fputc(mystring[i], fp);
    }
    part2[strlen(part2) - 1] = '\0';
    for(int i = 0; i < strlen(part2); i++){
        fputc(part2[i], fp3);
    }
    fclose(fp3);
}


int cat(int ldastoor, char dastoor[ldastoor]){
    char path[ldastoor - 11];
    int lpath = 0;
    for(int i = 0; i < ldastoor - 11; i++){
        path[i] = '\0';
    }
    for(int i = 0; i < ldastoor - 11; i++){
        if(dastoor[i + 11] == '-'){
            break;
        }
        path[i] = dastoor[i + 11];
        lpath++;
    }
    path[lpath] = '\0';
    //printf("%d %s\n", lpath, path);
    int exist;
    FILE *fp;
    fp = fopen(path,"r");
    if (!fp)
        exist = 0;
    else{
        fclose(fp);
        exist = 1;
    }
    if(exist == 0){
        printf("File not found!\n");
        return 0;
    }
    FILE *fp2;
    char ch;
    if(witharman == 0){
        fp2 = fopen(path,"r");
        while(!feof(fp2)){
            ch = fgetc(fp2);
            printf("%c", ch);
        }
        printf("\n");
        fclose(fp2);
    }
    int armancounter = 0;
    if(witharman){
        fp2 = fopen(path,"r");
        while(!feof(fp2)){
            ch = fgetc(fp2);
            outputarman[armancounter] = ch;
            armancounter++;
        }
        fclose(fp2);
    }
    return 0;
}


int mremove(int ldastoor,char dastoor[ldastoor]){
    char path[ldastoor - 17];
    int lpath = 0;
    for(int i = 0; i < ldastoor - 17; i++){
        path[i] = '\0';
    }
    for(int i = 0; i < ldastoor - 17; i++){
        if(dastoor[i + 17] == '-'){
            break;
        }
        path[i] = dastoor[i + 17];
        lpath++;
    }
    path[lpath] = '\0';
    int exist;
    FILE *fp;
    fp = fopen(path,"r");
    if (!fp)
        exist = 0;
    else{
        fclose(fp);
        exist = 1;
    }
    if(exist == 0){
        printf("File not found!\n");
        return 0;
    }


    //b undo
    fp = fopen(path, "r");
    char myundo[900000];
    for(int i = 0; i < 900000; i++){
        myundo[i] = '\0';
    }
    int myycounter = 0;
    while(!feof(fp)){
        char pch = fgetc(fp);
        myundo[myycounter] = pch;
        myycounter++;
    }
    myundo[myycounter - 1] = '\0';
    fclose(fp);
    fp = fopen("attachment/undo/a.txt", "w");
    for(int i = 0; i < strlen(myundo); i++){
        fputc(myundo[i], fp);
    }
    fclose(fp);

    //e undo


    int cmdpos = 0;
    int pospos;
    for(int i = 0; i < ldastoor; i++){
        if(dastoor[i] == '-' && dastoor[i + 1] == '-'){
            cmdpos++;
        }
        if(cmdpos == 2){
            pospos = i + 6;
            break;
        }
    }
    int line = 0;
    int character = 0;
    for(int i = pospos; i < ldastoor; i++){
        if(dastoor[i] == ':'){
            pospos = i + 1;
            break;
        }
        line = (line * 10) + ((int)dastoor[i] - 48);
    }
    for(int i = pospos; i < ldastoor; i++){
        if(dastoor[i] == ' '){
            pospos = i + 7;
            break;
        }
        character = (character * 10) + ((int)dastoor[i] - 48);
    }
    int msize = 0;
    for(int i = pospos; i < ldastoor; i++){
        if(dastoor[i] == ' '){
            //pospos = i + 7;
            break;
        }
        msize = (msize * 10) + ((int)dastoor[i] - 48);
    }
    char action = dastoor[ldastoor - 1];
    //printf("%d %d %d %c\n",line, character, msize, action);
    fp = fopen(path,"r");
    char ch;
    int fileline = 0;
    while(!feof(fp)){
        ch = fgetc(fp);
        //printf("%c",ch);
        if(ch == '\n'){
            fileline++;
        }
    }
    fclose(fp);
    fileline++;
    char part1[100000];
    char part2[100000];
    for(int i = 0; i < 100000; i++){
        part1[i] = '\0';
        part2[i] = '\0';
    }
    FILE *fp2;
    fp2 = fopen(path,"r");
    int countline = 0;
    int counter1 = 0;
    int counter2 = 0;
    int lcounter = 0;
    while(!feof(fp2)){
        if(countline + 1 < line){
            ch = fgetc(fp2);
            part1[counter1] = ch;
            //printf("%c", ch);
            if(ch == '\n'){
                countline++;
            }
            counter1++;
        }
        else if(countline + 1 == line){
            ch = fgetc(fp2);
            if(lcounter < character){
                part1[counter1] = ch;
                counter1++;
            }
            if(lcounter >= character){
                part2[counter2] = ch;
                counter2++;
            }
            lcounter++;
            if(ch == '\n'){
                countline++;
            }
        }
        else{
            ch = fgetc(fp2);
            part2[counter2] = ch;
            //printf("%c", ch);
            if(ch == '\n'){
                countline++;
            }
            counter2++;
        }
    }
    fclose(fp2);
    FILE *fp3;
    fp3 = fopen(path,"w");
    part2[strlen(part2) - 1] = '\0';
    if(action == 'b'){
        for(int i = 0; i < strlen(part1) - msize; i++){
            fputc(part1[i], fp3);
        }
        fputs(part2, fp3);
    }
    if(action == 'f'){
        fputs(part1, fp3);
        for(int i = msize; i < strlen(part2); i++){
            fputc(part2[i], fp3);
        }
    }

    fclose(fp3);
    return 0;
}



int mcopy(int ldastoor, char dastoor[ldastoor]){
    char path[ldastoor - 15];
    int lpath = 0;
    for(int i = 0; i < ldastoor - 15; i++){
        path[i] = '\0';
    }
    for(int i = 0; i < ldastoor - 15; i++){
        if(dastoor[i + 15] == '-'){
            break;
        }
        path[i] = dastoor[i + 15];
        lpath++;
    }
    path[lpath] = '\0';
    int exist;
    FILE *fp;
    fp = fopen(path,"r");
    if (!fp)
        exist = 0;
    else{
        fclose(fp);
        exist = 1;
    }
    if(exist == 0){
        if(forcut == 0){
            printf("File not found!\n");
        }
        return 0;
    }
    int cmdpos = 0;
    int pospos;
    for(int i = 0; i < ldastoor; i++){
        if(dastoor[i] == '-' && dastoor[i + 1] == '-'){
            cmdpos++;
        }
        if(cmdpos == 2){
            pospos = i + 6;
            break;
        }
    }
    int line = 0;
    int character = 0;
    for(int i = pospos; i < ldastoor; i++){
        if(dastoor[i] == ':'){
            pospos = i + 1;
            break;
        }
        line = (line * 10) + ((int)dastoor[i] - 48);
    }
    for(int i = pospos; i < ldastoor; i++){
        if(dastoor[i] == ' '){
            pospos = i + 7;
            break;
        }
        character = (character * 10) + ((int)dastoor[i] - 48);
    }
    int msize = 0;
    for(int i = pospos; i < ldastoor; i++){
        if(dastoor[i] == ' '){
            //pospos = i + 7;
            break;
        }
        msize = (msize * 10) + ((int)dastoor[i] - 48);
    }
    char action = dastoor[ldastoor - 1];
    //printf("%d %d %d %c\n",line, character, msize, action);
    fp = fopen(path,"r");
    char ch;
    int fileline = 0;
    while(!feof(fp)){
        ch = fgetc(fp);
        //printf("%c",ch);
        if(ch == '\n'){
            fileline++;
        }
    }
    fclose(fp);
    fileline++;
    char part1[100000];
    char part2[100000];
    for(int i = 0; i < 100000; i++){
        part1[i] = '\0';
        part2[i] = '\0';
    }
    FILE *fp2;
    fp2 = fopen(path,"r");
    int countline = 0;
    int counter1 = 0;
    int counter2 = 0;
    int lcounter = 0;
    while(!feof(fp2)){
        if(countline + 1 < line){
            ch = fgetc(fp2);
            part1[counter1] = ch;
            //printf("%c", ch);
            if(ch == '\n'){
                countline++;
            }
            counter1++;
        }
        else if(countline + 1 == line){
            ch = fgetc(fp2);
            if(lcounter < character){
                part1[counter1] = ch;
                counter1++;
            }
            if(lcounter >= character){
                part2[counter2] = ch;
                counter2++;
            }
            lcounter++;
            if(ch == '\n'){
                countline++;
            }
        }
        else{
            ch = fgetc(fp2);
            part2[counter2] = ch;
            //printf("%c", ch);
            if(ch == '\n'){
                countline++;
            }
            counter2++;
        }
    }
    fclose(fp2);
    FILE *fp3;
    fp3 = fopen("attachment/copy/a.txt","w");
    if(action == 'b'){
        for(int i = 0; i < msize; i++){
            fputc(part1[strlen(part1) - msize + i], fp3);
        }
    }
    else if(action == 'f'){
        for(int i = 0; i < msize; i++){
            fputc(part2[i], fp3);
        }
    }
    else{

    }
    //fprintf(fp3,"aaa");
    fclose(fp3);
    return 0;
}


int mcut(int ldastoor, char dastoor[ldastoor]){
    forcut = 1;
    char ch1dastoor[ldastoor + 3];
    char ch2dastoor[ldastoor + 1];
    ch1dastoor[0] = ' ';
    ch1dastoor[1] = ' ';
    ch1dastoor[2] = ' ';
    ch2dastoor[0] = ' ';
    for(int i = 0; i < ldastoor; i++){
        ch1dastoor[i + 3] = dastoor[i];
        ch2dastoor[i + 1] = dastoor[i];
    }
    mcopy(ldastoor + 1, ch2dastoor);
    mremove(ldastoor + 3, ch1dastoor);
    return 0;
}



int mpaste(int ldastoor, char dastoor[ldastoor]){
    FILE *fp;
    fp = fopen("attachment/copy/a.txt","r");
    int counter = 0;
    while(!feof(fp)){
        char ch = fgetc(fp);
        //printf("%c", ch);
        counter++;
    }
    //printf("%d", counter);
    int lchdastoor = 5 + counter;
    char chdastoor[lchdastoor + ldastoor + 1];
    int dcount = 0;
    for(int i = 0; i < ldastoor; i++){
        if(dastoor[i] == '-' && dastoor[i + 1] == '-'){
            dcount++;
        }
        if(dcount == 2){
            dcount = i;
            break;
        }
    }
    fclose(fp);
    FILE *fp2;
    fp2 = fopen("attachment/copy/a.txt","r");
    char mych[lchdastoor];
    mych[0] = 's';
    mych[1] = 't';
    mych[2] = 'r';
    mych[3] = ' ';
    mych[lchdastoor - 2] = '-';
    mych[lchdastoor - 1] = '-';
    char mych2;
    for(int i = 0; i < lchdastoor - 6; i++){
        mych2 = fgetc(fp);
        mych[i + 4] = mych2;
    }
    //printf("%d", dcount);
    for(int i = 1; i < lchdastoor + ldastoor + 1; i++){
        if(i < dcount + 3){
            chdastoor[i] = dastoor[i - 1];
        }
        else if(i >= dcount + 3 && i < dcount + 3 + lchdastoor){
            chdastoor[i] = mych[i - dcount - 3];
        }
        else{
            chdastoor[i] = dastoor[i - lchdastoor - 1];
        }
    }
    chdastoor[0] = ' ';
    fclose(fp2);
    //printf("%s", chdastoor);
    insertstr(lchdastoor + ldastoor + 1, chdastoor);
}



int mfind(int ldastoor, char dastoor[ldastoor]){
    char path[ldastoor - 12];
    int lpath = 0;
    for(int i = 0; i < ldastoor - 12; i++){
        path[i] = '\0';
    }
    for(int i = 0; i < ldastoor - 12; i++){
        if(dastoor[i + 12] == '-'){
            break;
        }
        path[i] = dastoor[i + 12];
        lpath++;
    }
    path[lpath] = '\0';
    int exist;
    FILE *fp;
    fp = fopen(path,"r");
    if (!fp)
        exist = 0;
    else{
        fclose(fp);
        exist = 1;
    }
    if(exist == 0){
        if(forcut == 0){
            printf("File not found!\n");
        }

        return 0;
    }
    char mystring[ldastoor];
    for(int i = 0; i < ldastoor; i++){
        mystring[i] = '\0';
    }
    //printf("%c", dastoor[18 + lpath]);
    int amountposat = 0;
    char atr[5][7];
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 7; j++){
            atr[i][j] = '\0';
        }
    }
    dastoor[ldastoor] = '\0';
    //printf("%s", dastoor);
    int backstar = 0;
    int counterlstr = 0;
    for(int i = 18 + lpath; i < ldastoor; i++){
        if((dastoor[i] == ' ' && dastoor[i + 1] == '-')){
            for(int j = i; j < ldastoor; j++){
                mystring[j] = '\0';
            }
            break;
        }
        if(dastoor[i] == '\\' && dastoor[i + 1] == '*'){
            mystring[counterlstr] = '*';
            counterlstr++;
            backstar++;
            i++;
            continue;
        }
        mystring[counterlstr] = dastoor[i];
        counterlstr++;
    }
    //printf("%s", mystring);
    int space = 0;
    int star = 0;
    for(int i = 0; i < strlen(mystring); i++){
        if(mystring[i] == ' '){
            space++;
        }
        if(mystring[i] == '*' && mystring[i - 1] != '\\'){
            star++;
        }
    }
    //printf("%s", mystring);
    for(int i = 18 + lpath; i < ldastoor; i++){
        for(int j = 0; j < 7; j++){
            if((dastoor[i + j] == ' ' && dastoor[i + j + 1] == '-') || (i + j == ldastoor)){
                amountposat++;
                i += j + 1;
                break;
            }
            atr[amountposat][j] = dastoor[i + j];
        }
    }
    int lmystring = strlen(mystring);
    fp = fopen(path, "r");
    char part[1000000];
    int chcounter = 0;
    while(!feof(fp)){
        part[chcounter] = fgetc(fp);
        chcounter++;
    }
    fclose(fp);
    if(star - backstar == 0){
        int spacecounter = 0;
        int counter = 0;
        part[chcounter - 1] = '\0';
        int poschars[10000] = {0};
        int posword[10000] = {0};
        char finding[lmystring];
        for(int i = 0; i < strlen(mystring); i++){
            finding[i] = '\0';
        }

        for(int i = 0; i < strlen(part); i++){
            for(int j = i; j < strlen(mystring) + i; j++){
                finding[j - i] = part[j];
            }
            finding[lmystring] = '\0';
            //printf("%s %s\n",mystring,finding);
            if((strcmp(finding, mystring) == 0 && part[i - 1] == ' ' && part[i + strlen(mystring)] == ' ') || (strcmp(finding, mystring) == 0 && part[i - 1] == '\n' && part[i + strlen(mystring)] == ' ') || (strcmp(finding, mystring) == 0 && part[i - 1] == ' ' && part[i + strlen(mystring)] == '\n') || (strcmp(finding, mystring) == 0 && i == 0 && part[i + strlen(mystring)] == ' ') || (strcmp(finding, mystring) == 0 && i == 0 && part[i + strlen(mystring)] == '\n') || (strcmp(finding, mystring) == 0 && i == 0 && part[i + strlen(mystring)] == '0')  || (strcmp(finding, mystring) == 0 && part[i - 1] == ' ' && part[i + strlen(mystring)] == '\0') || (strcmp(finding, mystring) == 0 && part[i - 1] == '\n' && part[i + strlen(mystring)] == '\n')){
                poschars[counter] = i;
                posword[counter] = spacecounter;
                counter++;
            }
            if(part[i] == ' ' || part[i] == '\n'){
                spacecounter++;
            }
        }
        if(counter == 0 && amountposat == 1){
            printf("%d\n", -1);
            return -1;
        }
        //printf("%d\n", counter); // تعداد پیداشده ها
        //printf("%d %d", poschars[1], posword[1] + 1);
        int atrat = 0;
        int atrall = 0;
        int atrbyword = 0;
        int atrcount = 0;
        int posat = -1;
        for(int i = 1; i < amountposat; i++){
            if(strcasecmp(atr[i], "all") == 0){
                atrall = i;
            }
            if(atr[i][0] == 'a' && atr[i][1] == 't'){
                atrat = i;
                posat = 0;
                for(int j = 3; j < strlen(atr[i]); j++){
                    posat = (posat * 10) + (int)atr[i][j] - 48;
                }
            }
            if(strcasecmp(atr[i], "byword") == 0){
                atrbyword = i;
            }
            if(strcasecmp(atr[i], "count") == 0){
                atrcount = i;
            }
        }
        //printf("%d %d %d %d", atrall, atrat, atrbyword, atrcount);
        if(atrall != 0 && atrat != 0){
            printf("your input isn't correct\n");
            return 0;
        }
        if(atrcount + atrall + atrat + atrbyword > atrcount && atrcount != 0){
            printf("your input isn't correct\n");
            return 0;
        }
        if(atrcount != 0){
            printf("%d\n", counter);
            return 0;
        }
        if(posat > counter){
            printf("%d\n", -1);
            return -1;
        }
        if(atrall != 0 && atrbyword != 0){
            for(int i = 0; i < counter; i++){
                printf("%d", posword[i] + 1);
                if(i != counter - 1){
                    printf(", ");
                }
            }
            printf("\n");
            return 0;
        }
        if(atrat != 0 && atrbyword != 0){
            printf("%d\n", posword[posat - 1] + 1);
            return 0;
        }
        if(atrat != 0){
            printf("%d\n", poschars[posat - 1]);
            return 0;
        }
        if(atrbyword != 0){
            printf("%d\n", posword[0] + 1);
            return 0;
        }
        if(atrall != 0 && forreplace == 0){
            for(int i = 0; i < counter; i++){
                printf("%d", poschars[i]);
                if(i != counter - 1){
                    printf(", ");
                }
            }
            printf("\n");
            return 0;
        }
        if(forreplace){
            for(int i = 0; i < counter; i++){
                findforreplace[i] = poschars[i];
            }
            return 0;
        }
        printf("%d\n", poschars[0]);
    }
    else{
        char chmystring[lmystring - 1];
        for(int i = 0; i < lmystring - 1; i++){
            chmystring[i] = '\0';
        }
        if(space == 0){
            if(mystring[0] == '*'){
                for(int i = 0; i < lmystring - 1; i++){
                    chmystring[i] = mystring[i + 1];
                }
                int spacecounter = 0;
                int counter = 0;
                part[chcounter - 1] = '\0';
                int poschars[10000] = {-1};
                int posword[10000] = {0};
                char finding[lmystring - 1];
                for(int i = 0; i < strlen(chmystring); i++){
                    finding[i] = '\0';
                }
                int posspace = 0;
                for(int i = 0; i < strlen(part); i++){
                    for(int j = i; j < strlen(chmystring) + i; j++){
                        finding[j - i] = part[j];
                        posspace = j;
                    }
                    finding[lmystring - 1] = '\0';
                    //printf("%s %s\n",mystring,finding);
                    if((strcmp(finding, chmystring) == 0 && part[posspace + 1] == ' ') || (strcmp(finding, chmystring) == 0 && part[posspace + 1] == '\n') || (strcmp(finding, chmystring) == 0 && posspace == strlen(part) - 1)){
                        poschars[counter] = i;
                        /*for(int k = 0; k < strlen(part); k++){
                            if(part[i - k] == ' '){
                                break;
                            }
                            poschars[counter] = i - k;
                        }*/
                        posword[counter] = spacecounter;
                        counter++;
                    }
                    if(part[i] == ' ' || part[i] == '\n'){
                        spacecounter++;
                    }
                }
                if(forreplace){
                    for(int i = 0; i < counter; i++){
                        findforreplace[i] = poschars[i];
                    }
                    return 0;
                }
                printf("%d\n", poschars[0]);
            }
            else{
                for(int i = 0; i < lmystring - 1; i++){
                    chmystring[i] = mystring[i];
                }
                int spacecounter = 0;
                int counter = 0;
                part[chcounter - 1] = '\0';
                int poschars[10000] = {-1};
                int posword[10000] = {0};
                char finding[lmystring - 1];
                for(int i = 0; i < strlen(chmystring); i++){
                    finding[i] = '\0';
                }
                int posspace = 0;
                for(int i = 0; i < strlen(part); i++){
                    for(int j = i; j < strlen(chmystring) + i; j++){
                        finding[j - i] = part[j];
                        posspace = j;
                    }
                    finding[lmystring - 1] = '\0';
                    //printf("%s %s\n",mystring,finding);
                    if((strcmp(finding, chmystring) == 0 && part[i - 1] == ' ') || (strcmp(finding, chmystring) == 0 && part[i - 1] == '\n') || (strcmp(finding, chmystring) == 0 && i == 0)){
                        poschars[counter] = i;
                        /*for(int k = 0; k < strlen(part); k++){
                            if(part[i - k] == ' '){
                                break;
                            }
                            poschars[counter] = i - k;
                        }*/
                        posword[counter] = spacecounter;
                        counter++;
                    }
                    if(part[i] == ' ' || part[i] == '\n'){
                        spacecounter++;
                    }
                }
                if(forreplace){
                    for(int i = 0; i < counter; i++){
                        findforreplace[i] = poschars[i];
                    }
                    return 0;
                }
                printf("%d\n", poschars[0]);
            }
        }
        else{
            int countsp = 0;
            for(int i = 0; i < lmystring; i++){
                if(mystring[i] == ' '){
                    countsp = 1;
                    break;
                }
                if(mystring[i] == '*'){
                    break;
                }
            }

            if(countsp){
                int posst = 0;
                for(int i = 0; i < lmystring; i++){
                    if(mystring[i] == '*'){
                        posst = i;
                    }
                }
                for(int i = posst; i < lmystring - 1; i++){
                    chmystring[i - posst] = mystring[i + 1];
                }
                chmystring[lmystring - posst - 1] = '\0';
                //printf("%s", chmystring);
                int spacecounter = 0;
                int counter = 0;
                part[chcounter - 1] = '\0';
                int poschars[10000] = {-1};
                int posword[10000] = {0};
                char finding[lmystring  - posst - 1];
                for(int i = 0; i < strlen(chmystring); i++){
                    finding[i] = '\0';
                }
                int posspace = 0;
                for(int i = 0; i < strlen(part); i++){
                    for(int j = i; j < strlen(chmystring) + i; j++){
                        finding[j - i] = part[j];
                        posspace = j;
                    }
                    finding[lmystring  - posst - 1] = '\0';
                    //printf("%s %s\n",mystring,finding);
                    if((strcmp(finding, chmystring) == 0 && part[posspace + 1] == ' ') || (strcmp(finding, chmystring) == 0 && part[posspace + 1] == '\n') || (strcmp(finding, chmystring) == 0 && posspace == strlen(part) - 1)){
                        poschars[counter] = i;
                        /*for(int k = 0; k < strlen(part); k++){
                            if(part[i - k] == ' '){
                                break;
                            }
                            poschars[counter] = i - k;
                        }*/
                        posword[counter] = spacecounter;
                        counter++;
                    }
                    if(part[i] == ' ' || part[i] == '\n'){
                        spacecounter++;
                    }
                }
                int cs = 0;
                int poss = 0;
                for(int i = 0; i < strlen(part); i++){
                    if(part[poschars[0] - i] == ' '){
                        poss = poschars[0] - i - 1;
                        break;
                    }
                }
                for(int i = 0; i < lmystring - posst -1; i++){
                    //printf("%c %c\n", mystring[posst - 2 - i], part[poss - i]);
                    if(mystring[posst - 2 - i] != part[poss - i]){
                        printf("%d\n", -1);
                        return -1;
                    }
                }
                if(forreplace){
                    for(int i = 0; i < counter; i++){
                        findforreplace[i] = poschars[i];
                    }
                    return 0;
                }
                printf("%d\n", poschars[0] - lmystring);
            }
            else{
                int posst = 0;
                for(int i = 0; i < lmystring; i++){
                    if(mystring[i] == '*'){
                        posst = i;
                    }
                }
                for(int i = 0; i < posst; i++){
                    chmystring[i] = mystring[i];
                }
                chmystring[posst - 1] = '\0';
                //printf("%s\n", chmystring);
                int spacecounter = 0;
                int counter = 0;
                part[chcounter - 1] = '\0';
                int poschars[10000] = {-1};
                int posword[10000] = {0};
                char finding[posst - 1];
                for(int i = 0; i < strlen(chmystring); i++){
                    finding[i] = '\0';
                }
                int posspace = 0;
                for(int i = 0; i < strlen(part); i++){
                    for(int j = i; j < strlen(chmystring) + i; j++){
                        finding[j - i] = part[j];
                        posspace = j;
                    }
                    finding[posst - 1] = '\0';
                    //printf("%s %s\n",mystring,finding);
                    if((strcmp(finding, chmystring) == 0 && part[i - 1] == ' ') || (strcmp(finding, chmystring) == 0 && part[i - 1] == '\n') || (strcmp(finding, chmystring) == 0 && i == 0)){
                        poschars[counter] = i;
                        /*for(int k = 0; k < strlen(part); k++){
                            if(part[i - k] == ' '){
                                break;
                            }
                            poschars[counter] = i - k;
                        }*/
                        posword[counter] = spacecounter;
                        counter++;
                    }
                    if(part[i] == ' ' || part[i] == '\n'){
                        spacecounter++;
                    }
                }
                int cs = 0;
                int poss = 0;
                for(int i = poschars[0] + 1; i < strlen(part); i++){
                    if(part[i] == ' '){
                        poss = i + 1;
                        break;
                    }
                }
                for(int i = 0; i < lmystring - posst - 3; i++){
                    //printf("%c %c\n", mystring[posst + 2 + i], part[poss + i]);
                    if(mystring[posst + 2 + i] != part[poss + i]){
                        printf("%d\n", -1);
                        return -1;
                    }
                }
                if(forreplace){
                    for(int i = 0; i < counter; i++){
                        findforreplace[i] = poschars[i];
                    }
                    return 0;
                }
                printf("%d\n", poschars[0]);
            }
        }
    }
}



int mreplace(int ldastoor, char dastoor[ldastoor]){
    char path[ldastoor - 15];
    int lpath = 0;
    for(int i = 0; i < ldastoor - 15; i++){
        path[i] = '\0';
    }
    for(int i = 0; i < ldastoor - 15; i++){
        if(dastoor[i + 15] == '-'){
            break;
        }
        path[i] = dastoor[i + 15];
        lpath++;
    }
    path[lpath] = '\0';
    int exist;
    FILE *fp;
    fp = fopen(path,"r");
    if (!fp)
        exist = 0;
    else{
        fclose(fp);
        exist = 1;
    }
    if(exist == 0){
        if(forcut == 0){
            printf("File not found!\n");
        }
        return 0;
    }


    //b undo
    fp = fopen(path, "r");
    char myundo[900000];
    for(int i = 0; i < 900000; i++){
        myundo[i] = '\0';
    }
    int myycounter = 0;
    while(!feof(fp)){
        char pch = fgetc(fp);
        myundo[myycounter] = pch;
        myycounter++;
    }
    myundo[myycounter - 1] = '\0';
    fclose(fp);
    fp = fopen("attachment/undo/a.txt", "w");
    for(int i = 0; i < strlen(myundo); i++){
        fputc(myundo[i], fp);
    }
    fclose(fp);

    //e undo


    char mystring1[ldastoor];
    char mystring2[ldastoor];
    char atr[4];
    atr[0] = '\0';
    atr[1] = '\0';
    atr[2] = '\0';
    atr[3] = '\0';
    for(int i = 0; i < ldastoor; i++){
        mystring1[i] = '\0';
        mystring2[i] = '\0';
    }
    int counter = 0;
    int posstr[3] = {0};
    for(int i = 0; i < ldastoor; i++){
        if(dastoor[i] == '-' && dastoor[i + 1] == '-'){
            posstr[counter] = i + 6;
            counter++;
        }
    }
    //printf("%d %d",posstr[1], posstr[2]);
    for(int i = posstr[1]; i < ldastoor; i++){
        if(dastoor[i] == '-' && dastoor[i + 1] == '-'){
            break;
        }
        mystring1[i - posstr[1]] = dastoor[i];
    }
    int posat = ldastoor;
    for(int i = posstr[2]; i < ldastoor; i++){
        if(dastoor[i] == ' ' && dastoor[i + 1] == '-'){
            posat = i + 2;
            break;
        }
        mystring2[i - posstr[2]] = dastoor[i];
    }
    for(int i = posat; i < ldastoor; i++){
        atr[i - posat] = dastoor[i];
    }
    //printf("%s\n", atr);
    //printf("%s %s", mystring1, mystring2);
    char chdastoor[ldastoor];

    for(int i = 0; i < ldastoor; i++){
        chdastoor[i] = '\0';

    }
    for(int i = 3; i < posstr[2] - 6; i++){
        chdastoor[i - 3] = dastoor[i];
    }

    chdastoor[posstr[2] - 9] = ' ';
    chdastoor[posstr[2] - 8] = '-';
    chdastoor[posstr[2] - 7] = 'a';
    chdastoor[posstr[2] - 6] = 'l';
    chdastoor[posstr[2] - 5] = 'l';
    mfind(strlen(chdastoor), chdastoor);
    int kcounter = 0;
    for(int k = 0; k < 1000; k++){
        if(findforreplace[k] != -1){
            kcounter++;
        }
    }
    //printf("%d\n", kcounter);
    if(strlen(atr) == 0){
        int k = 0;
        char part[100000];
        for(int i = 0; i < 100000; i++){
            part[i] = '\0';
        }
        fp = fopen(path, "r");
        counter = 0;
        while(!feof(fp)){
            char ch = fgetc(fp);
            part[counter] = ch;
            counter++;
        }
        //printf("%s\n\n", part);
        fclose(fp);
        char part1[strlen(part) - strlen(mystring1) + strlen(mystring2)];
        for(int i = 0; i < strlen(part) - strlen(mystring1) + strlen(mystring2); i++){
            part1[i] = '\0';
        }
        counter = 0;
        //printf("%d\n", findforreplace[k] + (k * (strlen(mystring2) - strlen(mystring1))));
        for(int i = 0; i < strlen(part); i++){
            if(i == findforreplace[k] + (k * (strlen(mystring2) - strlen(mystring1)))){
                for(int j = i; j < strlen(mystring2) + i; j++){
                    //printf("%d %c\n", j - i, mystring2[j - i]);
                    part1[counter] = mystring2[j - i];
                    counter++;
                }
                i += strlen(mystring1);
            }
            part1[counter] = part[i];
            counter++;
        }
        part1[strlen(part) - strlen(mystring1) + strlen(mystring2)] = '\0';
        part1[strlen(part) - strlen(mystring1) - 1 + strlen(mystring2)] = '\0';
        //printf("%s\n", part1);
        //printf("%s\n\n\n", part2);
        fp = fopen(path, "w");
        for(int i = 0; i < strlen(part1); i++){
            fputc(part1[i], fp);
        }
        fclose(fp);
    }
    else if(atr[0] == 'a' && atr[1] == 't'){
        int k = 0;
        for(int i = posat + 3; i < ldastoor; i++){
            k = k * 10 + ((int)dastoor[i] - 48);
        }
        k--;
        char part[100000];
        for(int i = 0; i < 100000; i++){
            part[i] = '\0';
        }
        fp = fopen(path, "r");
        counter = 0;
        while(!feof(fp)){
            char ch = fgetc(fp);
            part[counter] = ch;
            counter++;
        }
        //printf("%s\n\n", part);
        fclose(fp);
        char part1[strlen(part) - strlen(mystring1) + strlen(mystring2)];
        for(int i = 0; i < strlen(part) - strlen(mystring1) + strlen(mystring2); i++){
            part1[i] = '\0';
        }
        counter = 0;
        //printf("%d\n", findforreplace[k] + (k * (strlen(mystring2) - strlen(mystring1))));
        for(int i = 0; i < strlen(part); i++){
            if(i == findforreplace[k]){
                for(int j = i; j < strlen(mystring2) + i; j++){
                    //printf("%d %c\n", j - i, mystring2[j - i]);
                    part1[counter] = mystring2[j - i];
                    counter++;
                }
                i += strlen(mystring1);
            }
            part1[counter] = part[i];
            counter++;
        }
        part1[strlen(part) - strlen(mystring1) + strlen(mystring2)] = '\0';
        part1[strlen(part) - strlen(mystring1) - 1 + strlen(mystring2)] = '\0';
        //printf("%s\n", part1);
        //printf("%s\n\n\n", part2);
        fp = fopen(path, "w");
        for(int i = 0; i < strlen(part1); i++){
            fputc(part1[i], fp);
        }
        fclose(fp);
    }
    else if(atr[0] == 'a' && atr[1] == 'l' && atr[2] == 'l'){
        for(int k = 0; k < kcounter; k++){
            char part[100000];
            for(int i = 0; i < 100000; i++){
                part[i] = '\0';
            }
            fp = fopen(path, "r");
            counter = 0;
            while(!feof(fp)){
                char ch = fgetc(fp);
                part[counter] = ch;
                counter++;
            }
            //printf("%s\n\n", part);
            fclose(fp);
            char part1[strlen(part) - strlen(mystring1) + strlen(mystring2)];
            for(int i = 0; i < strlen(part) - strlen(mystring1) + strlen(mystring2); i++){
                part1[i] = '\0';
            }
            counter = 0;
            //printf("%d\n", findforreplace[k] + (k * (strlen(mystring2) - strlen(mystring1))));
            for(int i = 0; i < strlen(part); i++){
                if(i == findforreplace[k] + (k * (strlen(mystring2) - strlen(mystring1)))){
                    for(int j = i; j < strlen(mystring2) + i; j++){
                        //printf("%d %c\n", j - i, mystring2[j - i]);
                        part1[counter] = mystring2[j - i];
                        counter++;
                    }
                    i += strlen(mystring1);
                }
                part1[counter] = part[i];
                counter++;
            }
            part1[strlen(part) - strlen(mystring1) + strlen(mystring2)] = '\0';
            part1[strlen(part) - strlen(mystring1) - 1 + strlen(mystring2)] = '\0';
            //printf("%s\n", part1);
            //printf("%s\n\n\n", part2);
            fp = fopen(path, "w");
            for(int i = 0; i < strlen(part1); i++){
                fputc(part1[i], fp);
            }
            fclose(fp);
    }
    }

}


int grep(int ldastoor, char dastoor[ldastoor]){
    int posfilepos[100] = {0};
    int amountoffile = 0;
    for(int i = 0; i < ldastoor; i++){
        if(dastoor[i] == '-' && dastoor[i + 1] == '-'){
            posfilepos[amountoffile] = i + 8;
            amountoffile++;
        }
    }
    //printf("%d", amountoffile);
    char posfile[amountoffile][100];
    for(int i = 0; i < amountoffile; i++){
        for(int j = 0; j < 100; j++){
            posfile[i][j] = '\0';
        }
    }
    int counter = 0;
    for(int i = 0; i < amountoffile; i++){
        for(int j = 0; j < 100; j++){
            if(dastoor[posfilepos[i] + j] == '-' && dastoor[posfilepos[i] + j + 1] == '-'){
                break;
            }
            posfile[i][j] = dastoor[posfilepos[i] + j];
        }
    }





    char mystring[100];
    for(int i = 0; i < 100; i++){
        mystring[i] ='\0';
    }
    char atr = 'p';
    for(int i = 0; i < 100; i++){
        if(dastoor[posfilepos[amountoffile - 1] + i - 2] == ' ' && dastoor[posfilepos[amountoffile - 1] + 1 + i - 2] == '-'){
            atr = dastoor[posfilepos[amountoffile - 1] + i];
            break;
        }
        if(posfilepos[amountoffile - 1] + i - 2 == ldastoor){
            break;
        }
        mystring[i] = dastoor[posfilepos[amountoffile - 1] + i - 2];
    }
    //printf("%c", atr);
    int exist = 0;
    for(int i = 0; i < amountoffile - 1; i++){
        FILE *fp;
        fp = fopen(posfile[i],"r");
        if (!fp){

        }
        else{
            fclose(fp);
            exist++;
        }
    }
    if(exist != amountoffile - 1){
        printf("Some of your input files don't exist!\n");
        return 0;
    }
    char part[amountoffile - 1][900000];
    for(int i = 0; i < amountoffile - 1; i++){
        for(int j = 0; j < 900000; j++){
            part[i][j] = '\0';
        }
    }
    for(int i = 0; i < amountoffile - 1; i++){
        counter = 0;
        FILE *fp;
        fp = fopen(posfile[i], "r");
        while(!feof(fp)){
            char ch = fgetc(fp);
            part[i][counter] = ch;
            counter++;
        }
        fclose(fp);
        //printf("%s", part[i]);
    }
    int counter3 = 0;
    for(int k = 0; k < amountoffile - 1; k++){
        int counter2 = 0;
        int poschars[10000] = {-1};
        char finding[strlen(mystring)];
        for(int i = 0; i < strlen(mystring); i++){
            finding[i] = '\0';
        }
        for(int i = 0; i < strlen(part[k]); i++){
            for(int j = i; j < strlen(mystring) + i; j++){
                finding[j - i] = part[k][j];
            }
            finding[strlen(mystring)] = '\0';
            if(strcmp(finding, mystring) == 0){
                poschars[counter2] = i;
                counter2++;
                for(int q = 0; q < strlen(part[k]); q++){
                    if(part[k][i + q] == '\n'){
                        i = i + q;
                        break;
                    }
                }
            }
        }
        //printf("%d\n", counter2);
        counter3 += counter2;
    }
    char outputstring[counter3][100];
    char name[counter3][100];
    for(int i = 0; i < counter3; i++){
        for(int j = 0; j < 100; j++){
            outputstring[i][j] = '\0';
            name[i][j] = '\0';
        }
    }
    int counter4 = 0;
    for(int k = 0; k < amountoffile - 1; k++){
        int counter2 = 0;
        int poschars[10000] = {-1};
        char finding[strlen(mystring)];
        for(int i = 0; i < strlen(mystring); i++){
            finding[i] = '\0';
        }
        for(int i = 0; i < strlen(part[k]); i++){
            for(int j = i; j < strlen(mystring) + i; j++){
                finding[j - i] = part[k][j];
            }
            finding[strlen(mystring)] = '\0';
            if(strcmp(finding, mystring) == 0){
                int sar = 0;
                int tah = 0;
                poschars[counter2] = i;
                counter2++;
                for(int q = 0; q < strlen(part[k]); q++){
                    if(part[k][i - q] == '\n' || i + q == -1){
                        sar = i - q + 1;
                        break;
                    }
                }
                for(int q = 0; q < strlen(part[k]); q++){
                    if(part[k][i + q] == '\n' || i + q == strlen(part[k])){
                        tah = i + q - 1;
                        i = i + q;
                        break;
                    }
                }
                //printf("%d %d\n", sar, tah);
                int slash = 0;
                for(int q = 0; q < strlen(posfile[k]); q++){
                    if(posfile[k][q] == '/'){
                        slash++;
                    }
                }
                int slashcounter = 0;
                for(int q = 0; q < strlen(posfile[k]); q++){
                    if(posfile[k][q] == '/'){
                        slashcounter++;
                    }
                    if(slashcounter == slash){
                        for(int q1 = q + 1; q1 < strlen(posfile[k]); q1++){
                            name[counter4][q1 - q - 1] = posfile[k][q1];
                        }
                        break;
                    }
                }
                for(int q = sar; q <= tah; q++){
                    outputstring[counter4][q - sar] = part[k][q];
                }
                counter4++;
            }
        }
    }
    //printf("%d\n", counter4);
    if(witharman == 0){
        if(atr == 'p'){
            for(int i = 0; i < counter3; i++){
                printf("%s: ",name[i]);
                printf("%s\n", outputstring[i]);
            }
        }
        else if(atr == 'I'){
            for(int i = 0; i < counter3; i++){
                if(strcmp(name[i], name[i - 1]) != 0 || i == 0){
                    printf("%s\n", name[i]);
                }
            }
        }
        else if(atr == 'C'){
            printf("%d\n", counter3);
        }
    }
    int armancounter = 0;
    char result[10000];
    for(int i = 0; i < 10000; i++){
        result[i] = '\0';
    }
    int counterr = 0;
    if(witharman){
        if(atr == 'p'){
            for(int i = 0; i < counter3; i++){
                for(int j = 0; j < strlen(name[i]); j++){
                    result[counterr] = name[i][j];
                    counterr++;
                }
                result[counterr] = ':';
                counterr++;
                result[counterr] = ' ';
                counterr++;
                for(int j = 0; j < strlen(outputstring[i]); j++){
                    result[counterr] = outputstring[i][j];
                    counterr++;
                }
                result[counterr] = '\n';
                counterr++;
            }
        }
        else if(atr == 'I'){
            for(int i = 0; i < counter3; i++){
                if(strcmp(name[i], name[i - 1]) != 0 || i == 0){
                    for(int j = 0; j < strlen(name[i]); j++){
                        result[counterr] = name[i][j];
                        counterr++;
                    }
                    result[counterr] = '\n';
                    counterr++;
                }
            }
        }
        else if(atr == 'C'){
            printf("%d\n", counter3);
        }
    }
    for(int i = 0; i < strlen(result); i++){
        outputarman[i] = result[i];
    }
    return 0;
}








int compare(int ldastoor, char dastoor[ldastoor]){
    char posfile[2][100];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 100; j++){
            posfile[i][j] = '\0';
        }
    }
    int poskh = 15;
    for(int i = 0; i < 2; i++){
        for(int j = poskh; j < 100; j++){
            if(dastoor[j] == '-' && dastoor[j + 1] == '-' || j == ldastoor){
                poskh = j + 8;
                break;
            }
            posfile[i][j - poskh] = dastoor[j];
        }
    }
    //printf("%s", posfile[1]);
    int exist = 0;
    for(int i = 0; i < 2; i++){
        FILE *fp;
        fp = fopen(posfile[i],"r");
        if (!fp){

        }
        else{
            fclose(fp);
            exist++;
        }
    }
    if(exist != 2){
        printf("Some of your input files don't exist!\n");
        return 0;
    }
    char part1[900000];
    char part2[900000];
    for(int i = 0; i < 900000; i++){
        part1[i] = '\0';
        part2[i] = '\0';
    }
    char ch;
    int counter = 0;
    FILE *fp;
    fp = fopen(posfile[0], "r");
    while(!feof(fp)){
        ch = fgetc(fp);
        part1[counter] = ch;
        counter ++;
    }
    fclose(fp);
    counter = 0;
    fp = fopen(posfile[1], "r");
    while(!feof(fp)){
        ch = fgetc(fp);
        part2[counter] = ch;
        counter ++;
    }
    part1[strlen(part1) - 1] = '\0';
    part2[strlen(part2) - 1] = '\0';
    fclose(fp);
    //printf("%s\n%s\n", part1, part2);
    int line1 = 0;
    int line2 = 0;
    for(int i = 0; i < strlen(part1); i++){
        if(part1[i] == '\n'){
            line1++;
        }
    }
    for(int i = 0; i < strlen(part2); i++){
        if(part2[i] == '\n'){
            line2++;
        }
    }
    line1++;
    line2++;
    char p1[line1][1000];
    char p2[line2][1000];
    for(int i = 0; i < line1; i++){
        for(int j = 0; j < 1000; j++){
            p1[i][j] = '\0';
        }
    }
    for(int i = 0; i < line2; i++){
        for(int j = 0; j < 1000; j++){
            p2[i][j] = '\0';
        }
    }
    counter = 0;
    for(int i = 0; i < line1; i++){
        for(int j = 0; j < 1000; j++){
            if(part1[counter] == '\n'){
                counter++;
                break;
            }
            p1[i][j] = part1[counter];
            counter++;
        }
    }
    counter = 0;
    for(int i = 0; i < line2; i++){
        for(int j = 0; j < 1000; j++){
            if(part2[counter] == '\n'){
                counter++;
                break;
            }
            p2[i][j] = part2[counter];
            counter++;
        }
    }
    //printf("%s", p1[2]);
    //printf("%d %d", line1, line2);
    int bigger = line1;
    int smaller = line2;
    if(bigger < line2){
        bigger = line2;
        smaller = line1;
    }
    if(line1 == line2){
        for(int i = 0; i < line1; i++){
            if(strcmp(p1[i], p2[i]) != 0){
                printf("============ #%d ============\n", i + 1);
                printf("%s\n", p1[i]);
                printf("%s\n", p2[i]);
            }
        }
    }
    else{
        for(int i = 0; i < smaller; i++){
            if(strcmp(p1[i], p2[i]) != 0){
                printf("============ #%d ============\n", i + 1);
                printf("%s\n", p1[i]);
                printf("%s\n", p2[i]);
            }
        }
        if(line2 > line1){
                printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n", smaller + 1, bigger);
            }
            else{
                printf("<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n", smaller + 1, bigger);
            }
        for(int i = smaller; i < bigger; i++){
            if(line2 > line1){
                printf("%s\n", p2[i]);
            }
            else{
                printf("%s\n", p1[i]);
            }
        }
    }
    return 0;
}


int auto_indent(int ldastoor, char dastoor[ldastoor]){
    char path[ldastoor - 19];
    int lpath = 0;
    for(int i = 0; i < ldastoor - 19; i++){
        path[i] = '\0';
    }
    for(int i = 0; i < ldastoor - 19; i++){
        path[i] = dastoor[i + 19];
        lpath++;
    }
    path[lpath] = '\0';
    int exist;
    FILE *fp;
    fp = fopen(path,"r");
    if (!fp)
        exist = 0;
    else{
        fclose(fp);
        exist = 1;
    }
    if(exist == 0){
        printf("File not found!\n");
        return 0;
    }

    //b undo
    fp = fopen(path, "r");
    char myundo[90000];
    for(int i = 0; i < 90000; i++){
        myundo[i] = '\0';
    }
    int myycounter = 0;
    while(!feof(fp)){
        char pch = fgetc(fp);
        myundo[myycounter] = pch;
        myycounter++;
    }
    myundo[myycounter - 1] = '\0';
    fclose(fp);
    fp = fopen("attachment/undo/a.txt", "w");
    for(int i = 0; i < strlen(myundo); i++){
        fputc(myundo[i], fp);
    }
    fclose(fp);

    //e undo


    fp = fopen(path, "r");
    char ch;
    char part[900000];
    for(int i = 0; i < 900000; i++){
        part[i] = '\0';
    }
    int counter = 0;
    while(!feof(fp)){
        ch = fgetc(fp);
        part[counter] = ch;
        counter++;
    }
    part[strlen(part) - 1] = '\0';
    //printf("%s", part);
    int open = 0;
    int close = 0;
    for(int i = 0; i < strlen(part); i++){
        if(part[i] == '{'){
            open++;
        }
        if(part[i] == '}'){
            close++;
        }
    }
    //printf("%d %d", open, close);
    if(open != close){
        printf("%s\n", part);
        return 0;
    }

    char chpart[2 * open];
    for(int i = 0; i < 2 * open + 1; i++){
        chpart[i] = '\0';
    }
    counter = 0;
    for(int i = 0; i < strlen(part); i++){
        if(part[i] =='{' || part[i] == '}'){
            chpart[counter] = part[i];
            counter++;
        }
    }
    //printf("%s", chpart);
    int opencounter = 0;
    int exit = 0;
    for(int k = 0; k < close; k++){
        opencounter = 0;
        for(int i = 0; i < strlen(chpart); i++){
            //printf("%d\n", open);
            if(chpart[i] == '{'){
                opencounter++;
            }
            if(opencounter == open){
                for(int j = i + 1; j < strlen(chpart); j++){
                    if(chpart[j] == '}'){
                        chpart[i] = (char)1;
                        chpart[j] = (char)1;
                        open--;
                        i = 0;
                        opencounter = 0;
                        exit = 1;
                        //printf("%s\n", chpart);
                        break;
                    }
                }
            }
            if(exit){
                exit = 0;
                break;
            }
        }
    }
    counter = 0;
    for(int i = 0; i < strlen(chpart); i++){
        if(chpart[i] == (char)1){
            counter++;
        }
    }
    if(counter != strlen(chpart)){
        printf("%s\n", part);
        return 0;
    }
    char ch2part[strlen(part)];
    for(int i = 0; i <= strlen(part); i++){
        ch2part[i] = '\0';
    }
    counter = 0;
    for(int i = 0; i < strlen(part); i++){
        if(part[i] == '\n' || (part[i] == ' ' && part[i + 1] == ' ') || (part[i] == ' ' && part[i + 1] == '{') || (part[i] == ' ' && part[i + 1] == '}')){
            continue;
        }
        ch2part[counter] = part[i];
        counter++;
    }
    //printf("%s\n", ch2part);
    char chfpart[900000];
    for(int i = 0; i < 900000; i++){
        chfpart[i] = '\0';
    }
    counter = 0;
    int bar = 0;
    int bar1 = 0;
    for(int i = 0; i < strlen(ch2part); i++){
        if(ch2part[i] == '{'){
            int withoutspace = 0;
            for(int j = 0; j < strlen(ch2part); j++){
                if(ch2part[i - j - 1] == '\n' || i - j - 1 <= 0){
                    break;
                }
                if(ch2part[i - j] != ' ' && ch2part[i - j] != '{' && ch2part[i - j] != '}'){
                    withoutspace = 1;
                }
            }
            if(withoutspace == 1){
                chfpart[counter] = ' ';
                counter ++;
            }
            withoutspace = 0;
            for(int j = 0; j < strlen(ch2part); j++){
                if(ch2part[i - j - 1] != ' ' && ch2part[i - j - 1] != '{' && ch2part[i - j - 1] != '}'){
                    break;
                }
                if(ch2part[i - j - 1] == ' ' || ch2part[i - j - 1] == '{' || ch2part[i - j - 1] == '}'){
                    withoutspace = 1;
                }
            }
            if(withoutspace){
                for(int k = 0; k < 4 * bar; k++){
                    chfpart[counter] = ' ';
                    counter++;
                }
            }
            chfpart[counter] = ch2part[i];
            counter ++;
            chfpart[counter] = '\n';
            counter ++;
            bar++;
            bar1 = 1;
        }
        else if(ch2part[i] == '}'){
            bar--;
            int withoutclose = 0;
            for(int j = 0; j < strlen(ch2part); j++){
                //printf("%c\n", ch2part[counter - j]);
                if(ch2part[i - j] != ' ' && ch2part[i - j] != '}'){
                    withoutclose = 1;
                }
                if(ch2part[i - j - 1] == '}'){
                    break;
                }
            }
            if(withoutclose == 1){
                chfpart[counter] = '\n';
                counter ++;
            }
            for(int k = 0; k < 4 * bar; k++){
                chfpart[counter] = ' ';
                counter++;
            }
            chfpart[counter] = ch2part[i];
            counter ++;
            chfpart[counter] = '\n';
            counter ++;
            bar1 = 1;
        }
        else{
            if(bar1){
                for(int k = 0; k < 4 * bar; k++){
                    chfpart[counter] = ' ';
                    counter++;
                }
                bar1 = 0;
            }
            chfpart[counter] = ch2part[i];
            counter++;
        }
        //printf("%d", i);
    }
    //printf("%s", chfpart);
    fclose(fp);
    fp = fopen(path, "w");
    for(int i = 0; i < strlen(chfpart); i++){
        fputc(chfpart[i], fp);
    }
    fclose(fp);
    return 0;
}



int undo(int ldastoor, char dastoor[ldastoor]){
    char path[ldastoor - 12];
    int lpath = 0;
    for(int i = 0; i < ldastoor - 12; i++){
        path[i] = '\0';
    }
    for(int i = 0; i < ldastoor - 12; i++){
        path[i] = dastoor[i + 12];
        lpath++;
    }
    path[lpath] = '\0';
    int exist;
    FILE *fp;
    fp = fopen(path,"r");
    if (!fp)
        exist = 0;
    else{
        fclose(fp);
        exist = 1;
    }
    if(exist == 0){
        printf("File not found!\n");
        return 0;
    }

    //printf("%d\n", isundo);
    //b undo
    if(isundo == 0){
        fp = fopen(path, "r");
        char myundo[900000];
        for(int i = 0; i < 900000; i++){
            myundo[i] = '\0';
        }
        int myycounter = 0;
        while(!feof(fp)){
            char pch = fgetc(fp);
            myundo[myycounter] = pch;
            myycounter++;
        }
        myundo[myycounter - 1] = '\0';
        fclose(fp);
        fp = fopen("attachment/undo/b.txt", "w");
        for(int i = 0; i < strlen(myundo); i++){
            fputc(myundo[i], fp);
        }
        fclose(fp);
    }
    //e undo
    if(isundo){
        fp = fopen("attachment/undo/b.txt", "r");
    }
    else{
        fp = fopen("attachment/undo/a.txt", "r");
    }
    char myundo2[900000];
    for(int i = 0; i < 900000; i++){
        myundo2[i] = '\0';
    }
    int myycounter2 = 0;
    while(!feof(fp)){
        char pch2 = fgetc(fp);
        myundo2[myycounter2] = pch2;
        myycounter2++;
    }
    myundo2[myycounter2 - 1] = '\0';
    fclose(fp);
    fp = fopen(path, "w");
    for(int i = 0; i < strlen(myundo2); i++){
        fputc(myundo2[i], fp);
    }
    fclose(fp);




    return 0;
}


int farman(int ldastoor, char dastoor[ldastoor]){
    char dastoor1[ldastoor];
    char dastoor2[ldastoor];
    for(int i = 0; i < ldastoor; i++){
        dastoor1[i] = '\0';
        dastoor2[i] = '\0';
    }
    int posd2 = 0;
    for(int i = 0; i < ldastoor; i++){
        if(dastoor[i] == ' ' && dastoor[i + 1] == '=' && dastoor[i + 2] == 'D'){
            posd2 = i + 4;
            break;
        }
        dastoor1[i] = dastoor[i];
    }
    for(int i = posd2; i < ldastoor; i++){
        dastoor2[i - posd2] = dastoor[i];
    }
    //printf("%s\n%s\n", dastoor1, dastoor2);
    if(dastoor1[0] == 'c' && dastoor1[1] == 'a' && dastoor1[2] == 't'){
        cat(strlen(dastoor1), dastoor1);
    }
    else if(dastoor1[0] == 'f' && dastoor1[1] == 'i' && dastoor1[2] == 'n' && dastoor1[3] == 'd'){
        mfind(strlen(dastoor1), dastoor1);
    }
    else if(dastoor1[0] == 'g' && dastoor1[1] == 'r' && dastoor1[2] == 'e' && dastoor1[3] == 'p'){
        grep(strlen(dastoor1), dastoor1);
    }
    //printf("%s", outputarman);


    if(dastoor2[0] == 'i' && dastoor2[1] == 'n' && dastoor2[2] == 's' && dastoor2[3] == 'e' && dastoor2[4] == 'r' && dastoor2[5] == 't'){
        char chdastoor2[strlen(dastoor2) + strlen(outputarman) + 6];
        for(int i = 0; i < strlen(dastoor2) + strlen(outputarman) + 6; i++){
            chdastoor2[i] = '\0';
        }
        int chcounter = 0;
        int newpos = 0;
        for(int i = 0; i < strlen(dastoor2); i++){
            if(dastoor2[i] == '-' && dastoor2[i + 2] == 'p'){
                newpos = i;
                break;
            }
            chdastoor2[chcounter] = dastoor2[i];
            chcounter++;
        }
        chdastoor2[chcounter] = '-';
        chcounter++;
        chdastoor2[chcounter] = '-';
        chcounter++;
        chdastoor2[chcounter] = 's';
        chcounter++;
        chdastoor2[chcounter] = 't';
        chcounter++;
        chdastoor2[chcounter] = 'r';
        chcounter++;
        chdastoor2[chcounter] = ' ';
        chcounter++;
        for(int i = 0; i < strlen(outputarman) - 1; i++){
            chdastoor2[chcounter] = outputarman[i];
            chcounter++;
        }
        for(int i = newpos; i < strlen(dastoor2); i++){
            chdastoor2[chcounter] = dastoor2[i];
            chcounter++;
        }
        //printf("%s", chdastoor2);
        insertstr(strlen(chdastoor2), chdastoor2);
    }

}




int main(){
    mkdir("root");
    mkdir("attachment");
    mkdir("attachment/copy");
    mkdir("attachment/undo");
    FILE *FPP;
    FPP = fopen("attachment/copy/a.txt", "w");
    fclose(FPP);
    FPP = fopen("attachment/undo/a.txt", "w");
    fclose(FPP);
    FPP = fopen("attachment/undo/b.txt", "w");
    fclose(FPP);
    while(1){
        for(int i = 0; i < 90000; i++){
            outputarman[i] = '\0';
        }
        for(int i = 0; i < 1000; i++){
            findforreplace[i] = -1;
        }
        forcut = 0;
        witharman = 0;
        char dastoor[100];
        int ldastoor = 0;
        for(int i = 0; i < 100; i++){
            dastoor[i] = ' ';
        }
        for(int i = 0; i < 100; i++){
            scanf("%c", &dastoor[i]);
            if(dastoor[i] == '\n'){
                dastoor[i] = ' ';
                break;
            }
            ldastoor++;
        }
        int arman = 0;
        for(int i = 0; i < ldastoor; i++){
            if(dastoor[i] == '=' && dastoor[i + 1] == 'D'){
                arman = 1;
            }
        }
        if(dastoor[0] == 'c' && dastoor[1] == 'r' && dastoor[2] == 'e' && dastoor[3] == 'a' && dastoor[4] == 't' && dastoor[5] == 'e' && dastoor[6] == 'f' && dastoor[7] == 'i' && dastoor[8] == 'l' && dastoor[9] == 'e' && dastoor[10] == '-' && dastoor[11] == '-' && dastoor[12] == 'f' && dastoor[13] == 'i' && dastoor[14] == 'l' && dastoor[15] == 'e' && dastoor[16] == ' '){
            createfile(ldastoor, dastoor);
        }
        else if(arman){
            witharman = 1;
            farman(ldastoor, dastoor);
        }
        else if(dastoor[0] == 'i' && dastoor[1] == 'n' && dastoor[2] == 's' && dastoor[3] == 'e' && dastoor[4] == 'r' && dastoor[5] == 't' && dastoor[6] == 's' && dastoor[7] == 't' && dastoor[8] == 'r' && dastoor[9] == '-' && dastoor[10] == '-' && dastoor[11] == 'f' && dastoor[12] == 'i' && dastoor[13] == 'l' && dastoor[14] == 'e' && dastoor[15] == ' '){
            isundo = 0;
            insertstr(ldastoor, dastoor);
        }
        else if(dastoor[0] == 'c' && dastoor[1] == 'a' && dastoor[2] == 't' && dastoor[3] == '-' && dastoor[4] == '-' && dastoor[5] == 'f' && dastoor[6] == 'i' && dastoor[7] == 'l' && dastoor[8] == 'e' && dastoor[9] == ' '){
            cat(ldastoor, dastoor);
        }
        else if(dastoor[0] == 'r' && dastoor[1] == 'e' && dastoor[2] == 'm' && dastoor[3] == 'o' && dastoor[4] == 'v' && dastoor[5] == 'e' && dastoor[6] == 's' && dastoor[7] == 't' && dastoor[8] == 'r' && dastoor[9] == '-' && dastoor[10] == '-' && dastoor[11] == 'f' && dastoor[12] == 'i' && dastoor[13] == 'l' && dastoor[14] == 'e' && dastoor[15] == ' '){
            isundo = 0;
            mremove(ldastoor, dastoor);
        }
        else if(dastoor[0] == 'c' && dastoor[1] == 'o' && dastoor[2] == 'p' && dastoor[3] == 'y' && dastoor[4] == 's' && dastoor[5] == 't' && dastoor[6] == 'r' && dastoor[7] == '-' && dastoor[8] == '-' && dastoor[9] == 'f' && dastoor[10] == 'i' && dastoor[11] == 'l' && dastoor[12] == 'e' && dastoor[13] == ' '){
            mcopy(ldastoor, dastoor);
        }
        else if(dastoor[0] == 'c' && dastoor[1] == 'u' && dastoor[2] == 't' && dastoor[3] == 's' && dastoor[4] == 't' && dastoor[5] == 'r' && dastoor[6] == '-' && dastoor[7] == '-' && dastoor[8] == 'f' && dastoor[9] == 'i' && dastoor[10] == 'l' && dastoor[11] == 'e' && dastoor[12] == ' '){
            isundo = 0;
            mcut(ldastoor, dastoor);
        }
        else if(dastoor[0] == 'p' && dastoor[1] == 'a' && dastoor[2] == 's' && dastoor[3] == 't' && dastoor[4] == 'e' && dastoor[5] == 's' && dastoor[6] == 't' && dastoor[7] == 'r' && dastoor[8] == '-' && dastoor[9] == '-' && dastoor[10] == 'f' && dastoor[11] == 'i' && dastoor[12] == 'l' && dastoor[13] == 'e' && dastoor[14] == ' '){
            isundo = 0;
            mpaste(ldastoor, dastoor);
        }
        else if(dastoor[0] == 'f' && dastoor[1] == 'i' && dastoor[2] == 'n' && dastoor[3] == 'd' && dastoor[4] == '-' && dastoor[5] == '-' && dastoor[6] == 'f' && dastoor[7] == 'i' && dastoor[8] == 'l' && dastoor[9] == 'e' && dastoor[10] == ' '){
            forreplace = 0;
            mfind(ldastoor, dastoor);
        }
        else if(dastoor[0] == 'r' && dastoor[1] == 'e' && dastoor[2] == 'p' && dastoor[3] == 'l' && dastoor[4] == 'a' && dastoor[5] == 'c' && dastoor[6] == 'e' && dastoor[7] == '-' && dastoor[8] == '-' && dastoor[9] == 'f' && dastoor[10] == 'i' && dastoor[11] == 'l' && dastoor[12] == 'e' && dastoor[13] == ' '){
            isundo = 0;
            forreplace = 1;
            mreplace(ldastoor, dastoor);
        }
        else if(dastoor[0] == 'g' && dastoor[1] == 'r' && dastoor[2] == 'e' && dastoor[3] == 'p' && dastoor[4] == '-' && dastoor[5] == '-' && dastoor[6] == 'f' && dastoor[7] == 'i' && dastoor[8] == 'l' && dastoor[9] == 'e' && dastoor[10] == ' '){
            grep(ldastoor, dastoor);
        }
        else if(dastoor[0] == 'c' && dastoor[1] == 'o' && dastoor[2] == 'm' && dastoor[3] == 'p' && dastoor[4] == 'a' && dastoor[5] == 'r' && dastoor[6] == 'e' && dastoor[7] == '-' && dastoor[8] == '-' && dastoor[9] == 'f' && dastoor[10] == 'i' && dastoor[11] == 'l' && dastoor[12] == 'e' && dastoor[13] == ' '){
            compare(ldastoor, dastoor);
        }
        else if(dastoor[0] == 'a' && dastoor[1] == 'u' && dastoor[2] == 't' && dastoor[3] == 'o' && dastoor[4] == '-' && dastoor[5] == 'i' && dastoor[6] == 'n' && dastoor[7] == 'd' && dastoor[8] == 'e' && dastoor[9] == 'n' && dastoor[10] == 't' && dastoor[11] == '-' && dastoor[12] == '-' && dastoor[13] == 'f'  && dastoor[14] == 'i' && dastoor[15] == 'l' && dastoor[16] == 'e' && dastoor[17] == ' '){
            isundo = 0;
            auto_indent(ldastoor, dastoor);
        }
        else if(dastoor[0] == 'u' && dastoor[1] == 'n' && dastoor[2] == 'd' && dastoor[3] == 'o' && dastoor[4] == '-' && dastoor[5] == '-' && dastoor[6] == 'f' && dastoor[7] == 'i' && dastoor[8] == 'l' && dastoor[9] == 'e' && dastoor[10] == ' '){
            undo(ldastoor, dastoor);
            isundo = 1;
        }
        else{
            printf("invalid input\n");
        }

    }
    return 0;
}
